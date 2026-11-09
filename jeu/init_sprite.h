#pragma once
#include <SDL2/SDL.h>
#include <stdlib.h>
#include "shared_var.h"

struct img
{
    struct textures *t;
    struct skin *s;
    struct gui_sprite *g;
};

struct textures
{
    SDL_Texture *lim;
    SDL_Texture *lii;
    SDL_Texture *lis;
    SDL_Texture *qua;
    SDL_Texture *qui;
    SDL_Texture *qug;
    SDL_Texture *qus;
    SDL_Texture *quz;
    SDL_Texture *qzc;
    SDL_Texture *qzg;
    SDL_Texture *qzs;
    SDL_Texture *bas;
    SDL_Texture *bai;
    SDL_Texture *bac; 
    SDL_Texture *bal; 
    SDL_Texture *gra;
    SDL_Texture *gri;
    SDL_Texture *grc;
    SDL_Texture *grt;
    SDL_Texture *grd;
    SDL_Texture *grs;
    SDL_Texture *san;
    SDL_Texture *sai;
    SDL_Texture *sag;
    SDL_Texture *sha;
    SDL_Texture *shv;
    SDL_Texture *shs;
    SDL_Texture *shg;
    SDL_Texture *sht;
    SDL_Texture *shl;
    SDL_Texture *shc;
    SDL_Texture *shi;
    SDL_Texture *shz;
    SDL_Texture *mar;
    SDL_Texture *mai;
    SDL_Texture *gys;
    SDL_Texture *gyp;
    SDL_Texture *wat;
    SDL_Texture *soi;
    SDL_Texture *coa;
    SDL_Texture *sal;
    SDL_Texture *snd;
    SDL_Texture *dus;
    SDL_Texture *sno;
    SDL_Texture *gli;
    SDL_Texture *gqa;
    SDL_Texture *gqz;
    SDL_Texture *gba;
    SDL_Texture *ggr;
    SDL_Texture *gsa;
    SDL_Texture *gsh;
    SDL_Texture *gma;
    SDL_Texture *ggy;
    SDL_Texture *gst;
    SDL_Texture *gco;
    SDL_Texture *iro;
    SDL_Texture *cop;
    SDL_Texture *lea;
    SDL_Texture *zin;
    SDL_Texture *tin;
    SDL_Texture *gol;
    SDL_Texture *sul;
    SDL_Texture *sil;
    SDL_Texture *w1;

    SDL_Texture *fond;
};

struct skin
{
    // Homme qui marche
    SDL_Texture *Man[2][10][30][8][8]; //sexe /  couleur de peau / animation2 / animation / angle

    
    SDL_Texture *clothes[2][20][30][8][8]; //sexe /habit / animation 2 / animation / angle


    SDL_Texture *ship1_50cm_wood;
    SDL_Texture *ship1_100cm_wood;
    SDL_Texture *ship1_150cm_wood;
    SDL_Texture *ship1_200cm_wood;
    SDL_Texture *ship1_200cm_wood_triangle;
    SDL_Texture *ship1_flat_wood;
    SDL_Texture *ship1_flat_black;
    SDL_Texture *ship1_flat_wood_down_triangle;
    SDL_Texture *ship1_flat_wood_right_triangle;
    SDL_Texture *ship1_flat_wood_left_triangle;
    SDL_Texture *ship1_flat_wood_up_triangle;
    SDL_Texture *ship1_bigSail;
    SDL_Texture *ship1_bigSailFolded;

    SDL_Texture *fruit;
    SDL_Texture *legume;
    SDL_Texture *tree1Standing;
    SDL_Texture *tree1Felled;

    SDL_Texture *terracotta_house_3x3[9];
    SDL_Texture *terracotta_house_3x3_inside[6];
    SDL_Texture *wooden_house_6x6[11];
    SDL_Texture *wooden_house_3x3_faceline[3];

    SDL_Texture *wood_pillar;

    SDL_Texture *bridgeSlab;
    SDL_Texture *bridgePillar;

    // Drapeaux
    SDL_Texture *drapeauBlanc[12]; // 11 directions

    // Standing textures for littleManEmptyStuff
    SDL_Texture *littleManEmptyStuff_standing[12]; // 8 directions

    // Punching textures for littleManEmptyStuff
    SDL_Texture *littleManEmptyStuff_punching[4][12]; // 8 directions, 4 frames each

    // Walking textures for littleManEmptyStuff
    SDL_Texture *littleManEmptyStuff_walking[6][12]; // 8 directions, 6 frames each

};

struct gui_sprite
{
    SDL_Texture *croix;
    SDL_Texture *croix_inverse;
    SDL_Texture *demarcation;
    SDL_Texture *plus;
    SDL_Texture *moins;
    SDL_Texture *elipse;
    SDL_Texture *selecteur;
    SDL_Texture *main_menu_button;
    SDL_Texture *pressed_main_menu_button;
    SDL_Texture *sound_button;
    SDL_Texture *pressed_sound_button;
    SDL_Texture *square;
    SDL_Texture *triangle;
    SDL_Texture *lines;
    SDL_Texture *splited_lines;
    SDL_Texture *pressed_square;
    SDL_Texture *pressed_triangle;
    SDL_Texture *pressed_lines;
    SDL_Texture *pressed_splited_lines;
};


struct img *init_img();
struct textures *init_textures();
struct skin *init_skin();
struct gui_sprite *init_gui_sprite();
void initTextureObject(SDL_Texture** textureObject, char* bmpPath);
