#include "init_sprite.h"


void initTextureObject(SDL_Texture** textureObject, char* bmpPath)
{
    SDL_Surface *a = SDL_LoadBMP(bmpPath);
    SDL_SetColorKey(a, SDL_SCANCODE_Y, SDL_MapRGB(a->format,255,255,255));
    a = SDL_ConvertSurfaceFormat(a, SDL_GetWindowPixelFormat(window), 0);
    *textureObject = SDL_CreateTextureFromSurface(renderer, a);
    SDL_FreeSurface(a);
}


struct skin *init_skin()
{
    struct skin *to_return = malloc(sizeof(struct skin));
    initTextureObject(&(to_return->drapeauBlanc[0]), "img/batiments/drapeau/face_dos.bmp");//
    initTextureObject(&(to_return->drapeauBlanc[1]), "img/batiments/drapeau/dosDroite.bmp");//
    initTextureObject(&(to_return->drapeauBlanc[2]), "img/batiments/drapeau/droiteDos.bmp");//
    initTextureObject(&(to_return->drapeauBlanc[3]), "img/batiments/drapeau/droite.bmp");//
    initTextureObject(&(to_return->drapeauBlanc[4]), "img/batiments/drapeau/droiteFace.bmp");//
    initTextureObject(&(to_return->drapeauBlanc[5]), "img/batiments/drapeau/faceDroite.bmp");//
    initTextureObject(&(to_return->drapeauBlanc[6]), "img/batiments/drapeau/face_dos.bmp");//
    initTextureObject(&(to_return->drapeauBlanc[7]), "img/batiments/drapeau/faceGauche.bmp");//
    initTextureObject(&(to_return->drapeauBlanc[8]), "img/batiments/drapeau/gaucheFace.bmp");//
    initTextureObject(&(to_return->drapeauBlanc[9]), "img/batiments/drapeau/gauche.bmp");//
    initTextureObject(&(to_return->drapeauBlanc[10]), "img/batiments/drapeau/gaucheDos.bmp");//
    initTextureObject(&(to_return->drapeauBlanc[11]), "img/batiments/drapeau/dosGauche.bmp");//
    

    
    initTextureObject(&(to_return->ship1_50cm_wood), "img/ship/ship1/50cm_wood.bmp");
    initTextureObject(&(to_return->ship1_100cm_wood), "img/ship/ship1/100cm_wood.bmp");
    initTextureObject(&(to_return->ship1_150cm_wood), "img/ship/ship1/150cm_wood.bmp");
    initTextureObject(&(to_return->ship1_200cm_wood), "img/ship/ship1/200cm_wood.bmp");
    initTextureObject(&(to_return->ship1_200cm_wood_triangle), "img/ship/ship1/200cm_wood_triangle.bmp");
    initTextureObject(&(to_return->ship1_flat_wood), "img/ship/ship1/flat_wood.bmp");
    initTextureObject(&(to_return->ship1_flat_black), "img/ship/ship1/flat_black.bmp");
    initTextureObject(&(to_return->ship1_flat_wood_down_triangle), "img/ship/ship1/flat_wood_down_triangle.bmp");
    initTextureObject(&(to_return->ship1_flat_wood_right_triangle), "img/ship/ship1/flat_wood_right_triangle.bmp");
    initTextureObject(&(to_return->ship1_flat_wood_left_triangle), "img/ship/ship1/flat_wood_left_triangle.bmp");
    initTextureObject(&(to_return->ship1_flat_wood_up_triangle), "img/ship/ship1/flat_wood_up_triangle.bmp");
    initTextureObject(&(to_return->ship1_bigSail), "img/ship/ship1/bigSail.bmp");
    initTextureObject(&(to_return->ship1_bigSailFolded), "img/ship/ship1/bigSailFolded.bmp");


    //initTextureObject(&(to_return->fruit), "img/nature/nouriture/fruit.bmp");
    //initTextureObject(&(to_return->legume), "img/nature/nouriture/legume.bmp");
    initTextureObject(&(to_return->tree1Standing), "img/nature/tree1Standing.bmp");
    initTextureObject(&(to_return->tree1Felled), "img/nature/tree1Felled.bmp");

    
    initTextureObject(&(to_return->wooden_house_3x3_faceline[0]), "img/batiments/3x3_wooden_house/faceline1.bmp");
    initTextureObject(&(to_return->wooden_house_3x3_faceline[1]), "img/batiments/3x3_wooden_house/faceline2.bmp");
    initTextureObject(&(to_return->wooden_house_3x3_faceline[2]), "img/batiments/3x3_wooden_house/faceline3.bmp");

    initTextureObject(&(to_return->wooden_house_6x6[0]), "img/batiments/6x6_wooden_house/0.bmp");
    initTextureObject(&(to_return->wooden_house_6x6[1]), "img/batiments/6x6_wooden_house/1.bmp");
    initTextureObject(&(to_return->wooden_house_6x6[2]), "img/batiments/6x6_wooden_house/2.bmp");
    initTextureObject(&(to_return->wooden_house_6x6[3]), "img/batiments/6x6_wooden_house/3.bmp");
    initTextureObject(&(to_return->wooden_house_6x6[4]), "img/batiments/6x6_wooden_house/4.bmp");
    initTextureObject(&(to_return->wooden_house_6x6[5]), "img/batiments/6x6_wooden_house/5.bmp");
    initTextureObject(&(to_return->wooden_house_6x6[6]), "img/batiments/6x6_wooden_house/6.bmp");
    initTextureObject(&(to_return->wooden_house_6x6[7]), "img/batiments/6x6_wooden_house/7.bmp");
    initTextureObject(&(to_return->wooden_house_6x6[8]), "img/batiments/6x6_wooden_house/8.bmp");
    initTextureObject(&(to_return->wooden_house_6x6[9]), "img/batiments/6x6_wooden_house/9.bmp");
    initTextureObject(&(to_return->wooden_house_6x6[10]), "img/batiments/6x6_wooden_house/inside.bmp");

    

    initTextureObject(&(to_return->terracotta_house_3x3[0]), "img/batiments/3x3_terracotta_house/1.bmp");
    initTextureObject(&(to_return->terracotta_house_3x3[1]), "img/batiments/3x3_terracotta_house/2.bmp");
    initTextureObject(&(to_return->terracotta_house_3x3[2]), "img/batiments/3x3_terracotta_house/3.bmp");
    initTextureObject(&(to_return->terracotta_house_3x3[3]), "img/batiments/3x3_terracotta_house/4.bmp");
    initTextureObject(&(to_return->terracotta_house_3x3[4]), "img/batiments/3x3_terracotta_house/5.bmp");
    initTextureObject(&(to_return->terracotta_house_3x3[5]), "img/batiments/3x3_terracotta_house/6.bmp");
    initTextureObject(&(to_return->terracotta_house_3x3[6]), "img/batiments/3x3_terracotta_house/7.bmp");
    initTextureObject(&(to_return->terracotta_house_3x3[7]), "img/batiments/3x3_terracotta_house/8.bmp");
    initTextureObject(&(to_return->terracotta_house_3x3[8]), "img/batiments/3x3_terracotta_house/9.bmp");

    initTextureObject(&(to_return->terracotta_house_3x3_inside[0]), "img/batiments/3x3_terracotta_house/inside1.bmp");
    initTextureObject(&(to_return->terracotta_house_3x3_inside[1]), "img/batiments/3x3_terracotta_house/inside2.bmp");
    initTextureObject(&(to_return->terracotta_house_3x3_inside[2]), "img/batiments/3x3_terracotta_house/inside3.bmp");
    initTextureObject(&(to_return->terracotta_house_3x3_inside[3]), "img/batiments/3x3_terracotta_house/inside4.bmp");
    initTextureObject(&(to_return->terracotta_house_3x3_inside[4]), "img/batiments/3x3_terracotta_house/inside5.bmp");
    initTextureObject(&(to_return->terracotta_house_3x3_inside[5]), "img/batiments/3x3_terracotta_house/inside6.bmp");

    initTextureObject(&(to_return->wood_pillar), "img/batiments/pillar/wood.bmp");

    initTextureObject(&(to_return->bridgePillar), "img/batiments/bridges/pillar.bmp");
    initTextureObject(&(to_return->bridgeSlab), "img/batiments/bridges/slab.bmp");

    char filepath[100];
    char sexe[2][6] = {"man", "woman"};
    char couleur[10][10] = {"ivory", "marble", "sand", "gold", "leather", "oak", "bronze", "coffee", "chocolate", "ebony"};
    char animation2[4][12] = {"walk", "punch", "gather", "GroundBreak"};

    for (int i = 0; i < 2   ; i++) // sexe
    {
        for (int j = 0; j < 10; j++) // couleur de peau
        {
            for (int k = 0; k < 4; k++) // animation2
            {
                for (int l = 0; l < 8; l++) // animation
                {
                    for (int m = 0; m < 8; m++) // angle
                    {
                        sprintf (filepath, "img/%s/%s/%s/%d_%d.bmp", sexe[i], couleur[j], animation2[k],m, l);
                        initTextureObject(&(to_return->Man[i][j][k][l][m]), filepath);
                    }
                }
            }
        }
    }

    char clothes_man[1][10] = {"breeches"};

    for (int j = 0; j < 1; j++) // habit
    {
        for (int k = 0; k < 4; k++) // animation2
        {
            for (int l = 0; l < 8; l++) // animation
            {
                for (int m = 0; m < 8; m++) // angle
                {
                    sprintf (filepath, "img/man/%s/%s/%d_%d.bmp", clothes_man[j], animation2[k],m, l);
                    initTextureObject(&(to_return->clothes[0][j][k][l][m]), filepath);
                }
            }
        }
    }

    char clothes_woman[1][10] = {"shift"};

    for (int j = 0; j < 1; j++) // habit
    {
        for (int k = 0; k < 4; k++) // animation2
        {
            for (int l = 0; l < 8; l++) // animation
            {
                for (int m = 0; m < 8; m++) // angle
                {
                    sprintf (filepath, "img/woman/%s/%s/%d_%d.bmp", clothes_woman[j], animation2[k],m, l);
                    initTextureObject(&(to_return->clothes[1][j][k][l][m]), filepath);
                }
            }
        }
    }

    return to_return;
}

struct textures *init_textures()
{
    struct textures *to_return = malloc(sizeof(struct textures));
    initTextureObject(&(to_return->lim), "img/textures/lim.bmp");
    initTextureObject(&(to_return->lii), "img/textures/lii.bmp");
    initTextureObject(&(to_return->lis), "img/textures/lis.bmp");
    initTextureObject(&(to_return->qua), "img/textures/qua.bmp");
    initTextureObject(&(to_return->qui), "img/textures/qui.bmp");
    initTextureObject(&(to_return->qug), "img/textures/qug.bmp");
    initTextureObject(&(to_return->qus), "img/textures/qus.bmp");
    initTextureObject(&(to_return->quz), "img/textures/quz.bmp");
    initTextureObject(&(to_return->qzc), "img/textures/qzc.bmp");
    initTextureObject(&(to_return->qzg), "img/textures/qzg.bmp");
    initTextureObject(&(to_return->qzs), "img/textures/qzs.bmp");
    initTextureObject(&(to_return->bas), "img/textures/bas.bmp");
    initTextureObject(&(to_return->bai), "img/textures/bai.bmp");
    initTextureObject(&(to_return->bac), "img/textures/bac.bmp");
    initTextureObject(&(to_return->bal), "img/textures/bal.bmp");
    initTextureObject(&(to_return->gra), "img/textures/gra.bmp");
    initTextureObject(&(to_return->gri), "img/textures/gri.bmp");
    initTextureObject(&(to_return->grc), "img/textures/grc.bmp");
    initTextureObject(&(to_return->grt), "img/textures/grt.bmp");
    initTextureObject(&(to_return->grd), "img/textures/grd.bmp");
    initTextureObject(&(to_return->grs), "img/textures/grs.bmp");
    initTextureObject(&(to_return->san), "img/textures/san.bmp");
    initTextureObject(&(to_return->sai), "img/textures/sai.bmp");
    initTextureObject(&(to_return->sag), "img/textures/sag.bmp");
    initTextureObject(&(to_return->sha), "img/textures/sha.bmp");
    initTextureObject(&(to_return->shv), "img/textures/shv.bmp");
    initTextureObject(&(to_return->shs), "img/textures/shs.bmp");
    initTextureObject(&(to_return->shg), "img/textures/shg.bmp");
    initTextureObject(&(to_return->sht), "img/textures/sht.bmp");
    initTextureObject(&(to_return->shl), "img/textures/shl.bmp");
    initTextureObject(&(to_return->shc), "img/textures/shc.bmp");
    initTextureObject(&(to_return->shi), "img/textures/shi.bmp");
    initTextureObject(&(to_return->shz), "img/textures/shz.bmp");
    initTextureObject(&(to_return->mar), "img/textures/mar.bmp");
    initTextureObject(&(to_return->mai), "img/textures/mai.bmp");
    initTextureObject(&(to_return->gys), "img/textures/gys.bmp");
    initTextureObject(&(to_return->gyp), "img/textures/gyp.bmp");
    initTextureObject(&(to_return->wat), "img/textures/wat1.bmp");
    initTextureObject(&(to_return->soi), "img/textures/soi1.bmp");
    initTextureObject(&(to_return->coa), "img/textures/coa.bmp");
    initTextureObject(&(to_return->sal), "img/textures/sal.bmp");
    initTextureObject(&(to_return->snd), "img/textures/snd1.bmp");
    initTextureObject(&(to_return->dus), "img/textures/dus.bmp");
    initTextureObject(&(to_return->sno), "img/textures/sno1.bmp");
    initTextureObject(&(to_return->gli), "img/textures/gli.bmp");
    initTextureObject(&(to_return->gqa), "img/textures/gqa.bmp");
    initTextureObject(&(to_return->gqz), "img/textures/gqz.bmp");
    initTextureObject(&(to_return->gba), "img/textures/gba.bmp");
    initTextureObject(&(to_return->ggr), "img/textures/ggr.bmp");
    initTextureObject(&(to_return->gsa), "img/textures/gsa.bmp");
    initTextureObject(&(to_return->gsh), "img/textures/gsh.bmp");
    initTextureObject(&(to_return->gma), "img/textures/gma.bmp");
    initTextureObject(&(to_return->ggy), "img/textures/ggy.bmp");

    initTextureObject(&(to_return->gst), "img/textures/gst.bmp");
    initTextureObject(&(to_return->gco), "img/textures/gco.bmp");
    initTextureObject(&(to_return->iro), "img/textures/iro.bmp");
    initTextureObject(&(to_return->cop), "img/textures/cop.bmp");
    initTextureObject(&(to_return->lea), "img/textures/lea.bmp");
    initTextureObject(&(to_return->zin), "img/textures/zin.bmp");
    initTextureObject(&(to_return->tin), "img/textures/tin.bmp");
    initTextureObject(&(to_return->gol), "img/textures/gol.bmp");
    initTextureObject(&(to_return->sul), "img/textures/sul.bmp");
    initTextureObject(&(to_return->sil), "img/textures/sil.bmp");

    initTextureObject(&(to_return->w1), "img/textures/wall.bmp");
    initTextureObject(&(to_return->fond), "img/textures/fond.bmp");

    return to_return;
}

struct gui_sprite *init_gui_sprite()
{
    struct gui_sprite *to_return = malloc(sizeof(struct gui_sprite));
    initTextureObject(&(to_return->croix), "img/gui/croix.bmp");
    initTextureObject(&(to_return->croix_inverse), "img/gui/croix2.bmp");
    initTextureObject(&(to_return->demarcation), "img/gui/demarcation.bmp");
    initTextureObject(&(to_return->plus), "img/gui/buttons/plus.bmp");
    initTextureObject(&(to_return->moins), "img/gui/buttons/moins.bmp");
    initTextureObject(&(to_return->elipse), "img/gui/elipse.bmp");
    initTextureObject(&(to_return->selecteur), "img/gui/selected.bmp");
    initTextureObject(&(to_return->main_menu_button), "img/gui/buttons/main_menu.bmp");
    initTextureObject(&(to_return->pressed_main_menu_button), "img/gui/buttons/pressed_main_menu.bmp");
    initTextureObject(&(to_return->pressed_sound_button), "img/gui/buttons/no_sound.bmp");
    initTextureObject(&(to_return->sound_button), "img/gui/buttons/sound.bmp");
    initTextureObject(&(to_return->lines), "img/gui/buttons/lines.bmp");
    initTextureObject(&(to_return->square), "img/gui/buttons/square.bmp");
    initTextureObject(&(to_return->triangle), "img/gui/buttons/triangle.bmp");
    initTextureObject(&(to_return->splited_lines), "img/gui/buttons/splitted.bmp");
    initTextureObject(&(to_return->pressed_lines), "img/gui/buttons/pressed_lines.bmp");
    initTextureObject(&(to_return->pressed_square), "img/gui/buttons/pressed_square.bmp");
    initTextureObject(&(to_return->pressed_triangle), "img/gui/buttons/pressed_triangle.bmp");
    initTextureObject(&(to_return->pressed_splited_lines), "img/gui/buttons/pressed_splitted.bmp");
    return to_return;
}

struct img *init_img()
{
    struct img *ret = malloc(sizeof(struct img));
    ret->t = init_textures();
    ret->s = init_skin();
    ret->g = init_gui_sprite();
    return ret;
}
