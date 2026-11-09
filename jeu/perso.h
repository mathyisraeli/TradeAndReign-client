#pragma once
#include <stdio.h>
#include <err.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <math.h>
#include "sys/types.h"
#include "sys/socket.h"
#include "netinet/in.h"
#include "arpa/inet.h"
#include "linked_display.h"

struct personnages
{
    int id;                         // 1
    int pv;                         // 2
    int nb_vassaux;                 // 3
    int faim;                       // 4
    int inside;                     // 5
    float porte_dom;                // network (computed by the server)
    int dom;                        // network (computed by the server)
    int poid;                       // local
    int house_id;                   // 6
    int animation;                  // 7
    int animation_2;                // 8
    int max_pv;                     // local
    int vitesse_dom;                // local
    int echange_player;             // 14
    int items_cnt[12];              // 15 bis               10 premiers item // echange //
    int altitude;                   // raw couches (1m = 38)    18
    char angle;                     // 9
    char skin[4];                   // 0
    char physique[6];               // 10                  sexe/taille/couleur_de_peau/couleur_de_cheuveu/coifure
    char nom_de_compte[50];         // 11
    char nom[50];                   // 12
    char nom_superieur[50];         // 13 
    char items[18][50];             // 15 bis               10 premiers item // echange //  left hand right hand headgear tunic pant shoes
    char speak[90];                 // 23
    char skill[62];                 // 22
    float x;                        // 16
    float y;                        // 17
    float ordrex;                   // 19
    float ordrey;                   // 20
    float ordrea;                   // target altitude of the current x/y order
                                     // (raw couches, same unit as altitude) —
                                     // lets the order marker be drawn at the
                                     // right height (e.g. on a roof) instead
                                     // of always assuming flat ground
    float screenx;                  // local, only for display_selected()'s highlight box now
    float screeny;                  // local, only for display_selected()'s highlight box now
    float sizescreenx;              // local, only for display_selected()'s highlight box now
    float sizescreeny;              // local, only for display_selected()'s highlight box now
    struct linked_enemie *e_list;   // 21
};

struct linked_list
{
    struct personnages *p;
    struct linked_list *next;
};

#include "network/net.h"
#include "init_sprite.h"
#include "inventory/parse_equipement.h"
#include "network/parseur.h"
#include "select_sprite.h"


char exist_in_linked(struct linked_list *list, struct personnages *to_test);
struct linked_list *copy_linked(struct linked_list *list);
struct linked_list *append_in_linked(struct linked_list *list,struct personnages *p);
int append_perso(char *line);
//struct personnages *find_perso(struct linked_list *list ,char *name);
//void buble_sort_perso(struct linked_list *list, struct personnages *moi);
void free_linked(struct linked_list *list, char free_content);
struct linked_list *death(void);
struct linked_list *remove_from_linked_list(struct linked_list *list, struct personnages *to_rem);
struct personnages *find_perso_by_name(char *name);
struct personnages *find_perso_by_id(int id);
struct linked_list *clean_selected(struct linked_list *list);
int getSizeLinkedList(struct linked_list *list);
