#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "graphic_widget/gauge.h"
#include "graphic_widget/textBox.h"
#include "graphic_widget/textInfo.h"
#include "graphic_widget/menuSelector.h"
#include "graphic_widget/gauge.h"
#include "graphic_widget/dropDown.h"
#include "graphic_widget/pictureButton.h"
//#include "gui/menu.h"

extern SDL_Texture *ground_texture[2500];
extern int ground_altitude[2500];
extern uint8_t ground_buffer[7500];
extern char *recv_order_string;
extern int recv_order_string_size;
extern struct img *img;
extern SDL_Renderer *renderer;
extern SDL_Window *window;
extern struct textInput  *text;
#define screensizex 1800
#define screensizey 900
extern int max_x;
extern int max_y;
extern struct lettres *lettres;
extern struct linked_list *list;
extern struct building *list_building;
extern struct to_disp *list_disp;
extern TTF_Font *littleFont;
extern TTF_Font *bigFont;
extern TTF_Font *font;
extern struct speak *speakBubble;
extern struct menu *main_menu;
extern struct cond_menu *menu_cond;
extern struct main_char_stats *my_stats_display;
extern struct personnages *moi;
extern int counter_use_item;
extern int *building_id;
extern int start_x; extern int start_y; extern int end_x; extern int end_y;
#define order_size 2000
