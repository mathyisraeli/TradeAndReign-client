#include "picking.h"
#include "shared_var.h"

#define PICK_IS_CELL_BIT (1u << 23)
#define PICK_CELL_MASK   0x7FFFFFu
#define PICK_SUBTYPE_SHIFT 20
#define PICK_SUBTYPE_MASK  0x7u
#define PICK_ID_MASK       0xFFFFFu

static void pick_pack_cell(int cell_index, Uint8 *r, Uint8 *g, Uint8 *b)
{
    unsigned int packed = PICK_IS_CELL_BIT | ((unsigned int)cell_index & PICK_CELL_MASK);
    *r = (packed >> 16) & 0xFF;
    *g = (packed >> 8) & 0xFF;
    *b = packed & 0xFF;
}

static void pick_pack_entity(PickSubtype subtype, int id, Uint8 *r, Uint8 *g, Uint8 *b)
{
    unsigned int packed = (((unsigned int)subtype & PICK_SUBTYPE_MASK) << PICK_SUBTYPE_SHIFT) | ((unsigned int)id & PICK_ID_MASK);
    *r = (packed >> 16) & 0xFF;
    *g = (packed >> 8) & 0xFF;
    *b = packed & 0xFF;
}

static PickResult pick_unpack(Uint8 r, Uint8 g, Uint8 b)
{
    unsigned int packed = ((unsigned int)r << 16) | ((unsigned int)g << 8) | b;
    PickResult res = {0};

    if (packed & PICK_IS_CELL_BIT)
    {
        res.is_cell = 1;
        res.cell_index = packed & PICK_CELL_MASK;
    }
    else
    {
        res.subtype = (packed >> PICK_SUBTYPE_SHIFT) & PICK_SUBTYPE_MASK;
        res.id = packed & PICK_ID_MASK;
    }
    return res;
}

// A "stencil" is a copy of a sprite texture with every visible pixel forced
// to pure white, real alpha kept as-is. SDL_SetTextureColorMod multiplies a
// texture's colour, so colour-modding a white pixel gives exactly the
// requested colour, and the untouched alpha still blends correctly against
// whatever was drawn before it — meaning a transparent corner (e.g. the
// corner of a roof sprite) correctly lets the cell/entity behind it show
// through in the pick buffer too, not just in the real one.
typedef struct
{
    SDL_Texture *src;
    SDL_Texture *stencil;
} StencilEntry;

static StencilEntry *stencil_cache = NULL;
static int stencil_cache_size = 0;
static int stencil_cache_capacity = 0;

static SDL_Texture *make_stencil(SDL_Texture *src)
{
    int w, h;
    SDL_QueryTexture(src, NULL, NULL, &w, &h);

    SDL_Texture *prev_target = SDL_GetRenderTarget(renderer);
    SDL_Texture *tmp = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w, h);
    SDL_SetTextureBlendMode(tmp, SDL_BLENDMODE_BLEND);
    SDL_SetRenderTarget(renderer, tmp);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, src, NULL, NULL);

    Uint32 *pixels = malloc((size_t)w * h * sizeof(Uint32));
    SDL_RenderReadPixels(renderer, NULL, SDL_PIXELFORMAT_RGBA8888, pixels, w * (int)sizeof(Uint32));
    SDL_SetRenderTarget(renderer, prev_target);
    SDL_DestroyTexture(tmp);

    SDL_PixelFormat *fmt = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);
    for (int i = 0; i < w * h; i++)
    {
        Uint8 r, g, b, a;
        SDL_GetRGBA(pixels[i], fmt, &r, &g, &b, &a);
        // Alpha must land on a hard 0 or 255, not whatever the source had.
        // A softly anti-aliased edge pixel (say a=128, e.g. a roof's
        // outline) would otherwise blend its ID colour 50/50 with whatever
        // was drawn underneath it (the ground cell behind it) when this
        // stencil is later colour-modded and copied onto the pick buffer —
        // producing a colour that's neither ID, and that can easily decode
        // back as the wrong one (that's why roofs/angled edges mispicked
        // as the cell behind them: they have the most anti-aliased pixels).
        if (a > 127)
        {
            r = 255;
            g = 255;
            b = 255;
            a = 255;
        }
        else
        {
            a = 0;
        }
        pixels[i] = SDL_MapRGBA(fmt, r, g, b, a);
    }
    SDL_FreeFormat(fmt);

    SDL_Texture *stencil = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, w, h);
    SDL_SetTextureBlendMode(stencil, SDL_BLENDMODE_BLEND);
    SDL_UpdateTexture(stencil, NULL, pixels, w * (int)sizeof(Uint32));
    free(pixels);
    return stencil;
}

static SDL_Texture *get_stencil(SDL_Texture *src)
{
    for (int i = 0; i < stencil_cache_size; i++)
        if (stencil_cache[i].src == src)
            return stencil_cache[i].stencil;

    SDL_Texture *stencil = make_stencil(src);
    if (stencil_cache_size == stencil_cache_capacity)
    {
        stencil_cache_capacity = stencil_cache_capacity == 0 ? 64 : stencil_cache_capacity * 2;
        stencil_cache = realloc(stencil_cache, stencil_cache_capacity * sizeof(StencilEntry));
    }
    stencil_cache[stencil_cache_size].src = src;
    stencil_cache[stencil_cache_size].stencil = stencil;
    stencil_cache_size++;
    return stencil;
}

static void draw_cell(SDL_Texture *img, SDL_Rect *position, int cell_index)
{
    Uint8 r, g, b;
    pick_pack_cell(cell_index, &r, &g, &b);
    SDL_Texture *stencil = get_stencil(img);
    SDL_SetTextureColorMod(stencil, r, g, b);
    SDL_RenderCopy(renderer, stencil, NULL, position);
}

static void draw_entity(SDL_Texture *img, SDL_Rect *position, PickSubtype subtype, int id)
{
    Uint8 r, g, b;
    pick_pack_entity(subtype, id, &r, &g, &b);
    SDL_Texture *stencil = get_stencil(img);
    SDL_SetTextureColorMod(stencil, r, g, b);
    SDL_RenderCopy(renderer, stencil, NULL, position);
}

// One entry per building piece drawn so far *this pick_at() call* (reset at
// the start of each one, see pick_at()) — a piece's PICK_BUILDING id is
// simply its index here. Looked back up once, after the clicked pixel is
// known, to hand back that specific piece's real (x, y, altitude) without
// having to fit any of that into the pick colour itself.
typedef struct
{
    float x, y;
    int altitude_ground;
    int height;
} PickPiece;

static PickPiece *pick_pieces = NULL;
static int pick_pieces_size = 0;
static int pick_pieces_capacity = 0;

static void draw_building_piece(SDL_Texture *img, SDL_Rect *position, float x, float y, int altitude_ground, int height)
{
    if (pick_pieces_size == pick_pieces_capacity)
    {
        pick_pieces_capacity = pick_pieces_capacity == 0 ? 64 : pick_pieces_capacity * 2;
        pick_pieces = realloc(pick_pieces, pick_pieces_capacity * sizeof(PickPiece));
    }
    int piece_id = pick_pieces_size++;
    pick_pieces[piece_id].x = x;
    pick_pieces[piece_id].y = y;
    pick_pieces[piece_id].altitude_ground = altitude_ground;
    pick_pieces[piece_id].height = height;

    Uint8 r, g, b;
    pick_pack_entity(PICK_BUILDING, piece_id, &r, &g, &b);
    SDL_Texture *stencil = get_stencil(img);
    SDL_SetTextureColorMod(stencil, r, g, b);
    SDL_RenderCopy(renderer, stencil, NULL, position);
}

static SDL_Texture *pick_target = NULL;

// Mirrors display_ground()'s two branches (inside a building / outside), at
// the exact same screen positions — what changes is *what* gets drawn (an ID
// colour instead of the real texture) and, in the outside branch, the order:
// all ground cells are drawn before any entity instead of interleaved tile
// by tile, so a tall building/personnage sprite that visually spills onto a
// neighbouring cell can't be painted over by that cell (see the comment
// above the outside branch below). Known gap: the "w1" side-wall filler
// display_ground() draws under every outside ground tile isn't reproduced
// here, so a click landing only on that sliver (not the main tile diamond,
// and not on any entity) resolves to "nothing" instead of that cell.
static void draw_pick_scene(void)
{
    SDL_Rect position;

    if (moi->inside != -1)
    {
        for (struct to_disp *parcour = list_disp; parcour != NULL; parcour = parcour->next)
        {
            if (parcour->p && parcour->p->inside == moi->inside && ((int)parcour->x - moi->x) * ((int)parcour->x - moi->x) + ((int)parcour->y - moi->y) * ((int)parcour->y - moi->y) <= 441)
            {
                SDL_QueryTexture(parcour->img, NULL, NULL, &position.w, &position.h);
                position.x = (parcour->x - moi->x - parcour->y + moi->y) * 34 + parcour->offset_x - position.w / 2;
                position.y = (parcour->x - moi->x + parcour->y - moi->y) * 17 + parcour->offset_y - position.h - parcour->p->altitude + moi->altitude;
                draw_entity(parcour->img, &position, PICK_PERSO, parcour->p->id);
            }
            else if (parcour->b && parcour->b->id == moi->inside && parcour->x - (int)moi->x * parcour->x - (int)moi->x + parcour->y - (int)moi->y * parcour->y - (int)moi->y <= 441)
            {
                SDL_QueryTexture(parcour->img, NULL, NULL, &position.w, &position.h);
                position.x = (parcour->x - moi->x - parcour->y + moi->y) * 34 + parcour->offset_x - position.w / 2;
                int inside_ground_alt = ground_altitude[((int)parcour->y - start_y) * (end_x - start_x) + (int)parcour->x - start_x];
                position.y = (parcour->x - moi->x + parcour->y - moi->y) * 17 + parcour->offset_y - position.h - inside_ground_alt + moi->altitude;
                // Ground altitude is looked up live here (matching
                // display.c's own real-render position.y just above), not
                // cached anywhere on the piece: a value captured once, at
                // whatever moment actualise_stat_building() last (re)inserted
                // this piece, can go stale (e.g. a building registered before
                // its corner of the world had streamed in) — the real render
                // self-corrects every frame by re-reading ground_altitude[],
                // so picking has to do the same or it can disagree with what
                // the player is actually looking at. parcour->height, by
                // contrast, isn't terrain — there's no "live" source to
                // re-read it from, so it's read straight off the piece.
                draw_building_piece(parcour->img, &position, parcour->x, parcour->y, inside_ground_alt, parcour->height);
            }
        }
        return;
    }

    // Pass 1: every visible ground cell, nothing else. Drawn in full before
    // any entity so a cell can never end up on top of (and stealing the
    // click from) a building/personnage that visually overlaps it — which
    // is what interleaving cell-then-its-own-entities, the way
    // display_ground() does it, allowed: a building's sprite is taller than
    // one tile and spills onto neighbouring cells, and those cells were
    // drawn *after* it whenever they came later in the (x,y) sweep.
    int ii = 0;
    for (int y = start_y; y < end_y; y++)
    {
        for (int x = start_x; x < end_x; x++)
        {
            float dx = x - moi->x;
            float dy = y - moi->y;

            if (dx * dx + dy * dy <= 441)
            {
                position.x = (dx - dy) * 34 + 866;
                position.y = (dx + dy) * 17 + 450 - ground_altitude[ii] + moi->altitude;
                position.w = 68;
                position.h = 34;
                draw_cell(ground_texture[ii], &position, x + y * max_x);
            }
            ii++;
        }
    }

    // Pass 2: every entity, still in list_disp's own (already depth-sorted)
    // order, so occlusion between entities themselves is unaffected — only
    // ground-vs-entity ordering changes.
    for (struct to_disp *parcour = list_disp; parcour != NULL; parcour = parcour->next)
    {
        if (((int)parcour->x - moi->x) * ((int)parcour->x - moi->x) + ((int)parcour->y - moi->y) * ((int)parcour->y - moi->y) > 441)
            continue;

        int cell_ii = ((int)parcour->y - start_y) * (end_x - start_x) + (int)parcour->x - start_x;
        int watter = 38 * (ground_texture[cell_ii] == img->t->wat);

        if (parcour->p && parcour->p->inside == -1)
        {
            SDL_QueryTexture(parcour->img, NULL, NULL, &position.w, &position.h);
            position.x = (parcour->x - moi->x - parcour->y + moi->y) * 34 + parcour->offset_x - position.w / 2;
            position.y = (parcour->x - moi->x + parcour->y - moi->y) * 17 + parcour->offset_y - position.h - parcour->p->altitude + moi->altitude + watter;
            draw_entity(parcour->img, &position, PICK_PERSO, parcour->p->id);
        }
        else if (parcour->b)
        {
            SDL_QueryTexture(parcour->img, NULL, NULL, &position.w, &position.h);
            position.x = (parcour->x - moi->x - parcour->y + moi->y) * 34 + parcour->offset_x - position.w / 2;
            position.y = (parcour->x - moi->x + parcour->y - moi->y) * 17 + parcour->offset_y - position.h - ground_altitude[cell_ii] + moi->altitude + watter;
            // See the comment on the other draw_building_piece(...) call
            // above: ground_altitude[cell_ii] is looked up live to avoid the
            // same staleness bug a cached value would have.
            draw_building_piece(parcour->img, &position, parcour->x, parcour->y, ground_altitude[cell_ii], parcour->height);
        }
    }
}

PickResult pick_at(int screen_x, int screen_y)
{
    if (pick_target == NULL)
        pick_target = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, screensizex, screensizey);

    pick_pieces_size = 0; // reused across calls, capacity kept — see PickPiece

    SDL_Texture *prev_target = SDL_GetRenderTarget(renderer);
    SDL_SetRenderTarget(renderer, pick_target);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    draw_pick_scene();

    Uint32 pixel = 0;
    SDL_Rect px = {screen_x, screen_y, 1, 1};
    SDL_RenderReadPixels(renderer, &px, SDL_PIXELFORMAT_RGBA8888, &pixel, sizeof(Uint32));
    SDL_SetRenderTarget(renderer, prev_target);

    SDL_PixelFormat *fmt = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);
    Uint8 r, g, b, a;
    SDL_GetRGBA(pixel, fmt, &r, &g, &b, &a);
    SDL_FreeFormat(fmt);

    PickResult res = pick_unpack(r, g, b);
    if (!res.is_cell && res.subtype == PICK_BUILDING && res.id >= 0 && res.id < pick_pieces_size)
    {
        res.piece_x = pick_pieces[res.id].x;
        res.piece_y = pick_pieces[res.id].y;
        res.piece_altitude_ground = pick_pieces[res.id].altitude_ground;
        res.piece_height = pick_pieces[res.id].height;
    }
    return res;
}
