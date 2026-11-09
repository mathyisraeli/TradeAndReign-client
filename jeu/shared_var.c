#include "shared_var.h"

SDL_Texture *ground_texture[2500];
int ground_altitude[2500];
uint8_t ground_buffer[7500];
char *recv_order_string;
int recv_order_string_size = 10;
int max_x;
int max_y;
struct img *img;
SDL_Renderer *renderer;
SDL_Window *window;
struct lettres *lettres;
struct linked_list *list;
struct building *list_building;
struct to_disp *list_disp;
TTF_Font *littleFont;
TTF_Font *bigFont;
TTF_Font *font;
struct speak *speakBubble;
struct menu *main_menu;
struct cond_menu *menu_cond;
struct main_char_stats *my_stats_display;
struct textInput  *text;
struct personnages *moi;
int *building_id;
int counter_use_item;
int *building_id;
int start_x; int start_y; int end_x; int end_y;