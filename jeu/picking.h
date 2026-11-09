#pragma once
#include "perso.h"

// Colour-ID picking: to know exactly what's under the mouse (a ground cell,
// a building, a personnage — later, other structs), we redraw the frame a
// second time into an off-screen texture using a solid colour that encodes
// the entity's identity instead of its real sprite, then read back the one
// pixel under the cursor. That pixel tells us exactly what's visible there,
// respecting real draw order and each sprite's actual (non-rectangular)
// shape, instead of guessing from an inverted isometric formula or testing
// bounding boxes.
//
// The 3 colour bytes (alpha is left alone, real transparency/blending needs
// it) pack a 24 bit value:
//   bit 23        : 1 = a ground cell, 0 = something else (an "entity")
//   bits 0-22     : if a cell, the cell index (x + y*max_x) directly —
//                   there are far more cells than entities, so cells get
//                   almost the whole budget (up to 8 388 608 of them)
//                   if not a cell, split further: bits 20-22 (3 bits) are
//                   the entity's subtype (see enum below), bits 0-19 are
//                   its own id (that struct's own id field) — 1 048 576
//                   ids per subtype, more than enough for anything that
//                   isn't a per-cell count
// All-zero (type=entity, subtype=0) is reserved for "nothing was clicked".
//
// PICK_BUILDING is not "which building": every drawn piece of every building
// (there can be several per tile — different floors, a floor and the roof
// above it, ...) gets registered, at the moment it's drawn, under its own
// sequential id — see pick_pieces in picking.c. That id doesn't mean
// anything on its own; pick_at() resolves it immediately and fills
// piece_x/piece_y/piece_altitude_ground/piece_height below with that specific
// piece's real data, mirroring struct to_disp's own altitude_ground/height
// split (see linked_display.h): piece_altitude_ground is the ground's own
// altitude under that piece, piece_height is how far above that this piece's
// own walkable surface sits (0 for every building today — no multi-storey
// building exists yet, but a piece higher up a future one would carry its
// own non-zero height the exact same way, no picking.c change needed when
// that's added). ordre.c adds the two together to get the piece's real
// altitude. Two pieces at the same tile therefore still resolve
// independently, by whichever is actually visible at the clicked pixel.
typedef enum
{
    PICK_NONE = 0, // reserved, never assigned to a real entity
    PICK_PERSO = 1,
    PICK_BUILDING = 2,
    // room for up to 5 more subtypes (3 bits) before this needs revisiting
} PickSubtype;

typedef struct
{
    char is_cell;      // 1: cell_index is what was clicked. 0: subtype/id is.
    int cell_index;    // valid if is_cell: x + y*max_x
    PickSubtype subtype; // valid if !is_cell: PICK_NONE if nothing was clicked
    int id;             // valid if !is_cell && subtype == PICK_PERSO: that personnage's own id
    float piece_x, piece_y; // valid if subtype == PICK_BUILDING: the clicked piece's real position
    int piece_altitude_ground; // valid if subtype == PICK_BUILDING: ground altitude under that piece
    int piece_height;          // valid if subtype == PICK_BUILDING: that piece's height above the ground
} PickResult;

// Redraws the current frame's visible ground/buildings/personnages into an
// off-screen colour-ID buffer (same positions, same draw order as
// display_ground(), just solid colours instead of textures) and reads back
// the single pixel under (screen_x, screen_y). Meant to be called on demand
// (a click, or while actively giving an order) — not every frame regardless
// of what's happening, it redraws the whole visible scene once per call.
PickResult pick_at(int screen_x, int screen_y);
