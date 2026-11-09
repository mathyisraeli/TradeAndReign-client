#include "parse_equipement.h"

static inline void insert(float x, float y, int height, int id, char floor, int offsetx, int offsety, struct personnages *p, struct building *b, SDL_Texture* img)
{
	struct to_disp *new = malloc(sizeof(struct to_disp));
	new->img = img;
	new->x = x;
	new->y = y;
	new->height = height;
	new->id = id;
	new->floor = floor;
	new->offset_x = offsetx;
	new->offset_y = offsety;
	new->next = NULL;
	new->p = p;
	new->b = b;
	sortedInsert(new);
}

void actualise_stat(struct personnages *p)
{
	struct personnages *overlord = find_perso_by_name(p->nom_superieur);
	if (overlord == NULL)
	{
		for (struct linked_enemie* l = p->e_list; l != NULL; l=l->next)
			if (l->rang>0)
				sprintf(ordre + strlen(ordre), "0 %d 15 %s ", p->id, l->nom);
	}
	else 
	{
		for (struct linked_enemie* l = p->e_list; l != NULL; l=l->next)
		{
			if (l->rang>0)
			{
				struct linked_enemie *test = exist_in_linked_enemie(overlord->e_list, l->nom);
				if (test == NULL || test->rang +1 != l->rang)
					sprintf(ordre + strlen(ordre), "0 %d 15 %s ", p->id, l->nom);
			}
		}
		for (struct linked_enemie* l = overlord->e_list; l != NULL; l=l->next)
		{
			if (exist_in_linked_enemie(p->e_list, l->nom) == NULL)
				sprintf(ordre + strlen(ordre), "0 %d 15 +%d %s ", p->id, l->rang+1, l->nom);
		}
	}
	if (p->skin[1] == '1')
	{
		list_disp = deleteKey_char(p->id);
		p->max_pv = 200;
		p->poid = 999;
		p->animation = 0;
		struct to_disp *new = malloc(sizeof(struct to_disp));
		new->offset_y = 454;
		if (p->pv > 25)
		{
			new->offset_x = 896;	
			new->img = img->s->tree1Standing;
		}
		else
		{
			new->offset_x = 990;
			new->img = img->s->tree1Felled;
		}
		new->x = p->x;
		new->y = p->y;
		new->id = p->id;
		new->b = NULL;
		new->p = p;
		new->floor = 1;
		new->height = 0;
		new->next = NULL;
		sortedInsert(new);
	}
	else if (p->skin[1] == '2')
	{
		insert(p->x, p->y, 0,p->id, 0, 0, 0, p, NULL, img->s->drapeauBlanc[p->angle - 'a']);
		p->max_pv = 99999;
		p->poid = 10000;
	}
	else if (p->skin[0] == '0' && (p->skin[1] == 0 || p->skin[1] == '0'))
	{
		list_disp = deleteKey_char(p->id);
		p->max_pv = 10;
		p->vitesse_dom = 100;
		p->poid = 65;
		struct to_disp *new = malloc(sizeof(struct to_disp));
		new->x = p->x;
		new->height = 0;
		new->y = p->y;
		new->b = NULL;
		new->id = p->id;
		new->next = NULL;
		new->p = p;
		new->floor = 1;
		new->img = 0;
		new->img = img->s->Man[p->physique[0]-'0'][p->physique[1]-'0'][p->animation_2][p->animation][p->angle - 'a'];
		new->offset_x = 900	;
		new->offset_y = 460;
		sortedInsert(new);
		if (strcmp(p->items[16], "breeches") == 0) 
		{
			struct to_disp *nnew = malloc(sizeof(struct to_disp));
			nnew->x = p->x;
			nnew->height = 0;
			nnew->y = p->y;
			nnew->b = NULL;
			nnew->id = p->id;
			nnew->next = new->next;
			nnew->p = p;
			nnew->floor = 1;
			nnew->img = img->s->clothes[0][0][p->animation_2][p->animation][p->angle - 'a'];
			nnew->offset_x = 900;
			nnew->offset_y = 460;
			new->next = nnew;
		}
		if (strcmp(p->items[16], "shift") == 0) 
		{
			struct to_disp *nnew = malloc(sizeof(struct to_disp));
			nnew->x = p->x;
			nnew->height = 0;
			nnew->y = p->y;
			nnew->b = NULL;
			nnew->id = p->id;
			nnew->next = new->next;
			nnew->p = p;
			nnew->floor = 1;
			nnew->img = img->s->clothes[1][0][p->animation_2][p->animation][p->angle - 'a'];
			nnew->offset_x = 900;
			nnew->offset_y = 460;
			new->next = nnew;
		}
	}
}

void actualise_stat_building(struct building *b)
{
	list_disp = deleteKey_build(b->id);
	if (b->skin[1] == '1')
	{
		if (b->skin[2] == '2')
		{
			insert(b->x, b->y, 76, b->id, 0, 866, 475, NULL, b,img->s->wooden_house_3x3_faceline[2]);
			insert(b->x, b->y-1,76, b->id, 0, 891, 441, NULL, b,img->s->wooden_house_3x3_faceline[1]);
			insert(b->x, b->y-2,76,b->id, 0, 891, 478, NULL, b,img->s->wooden_house_3x3_faceline[0]);
		}
		else if (b->skin[2] == '1')
		{
			if (moi != NULL && b->id == moi->inside)
			{
				insert(b->x-1, b->y,0,b->id, 0, 900, 485, NULL, b,img->s->terracotta_house_3x3_inside[0]);
				insert(b->x-2, b->y,0,b->id, 0, 900, 485, NULL, b,img->s->terracotta_house_3x3_inside[1]);
				insert(b->x-1, b->y-1,0, b->id, 0, 900, 485, NULL, b,img->s->terracotta_house_3x3_inside[2]);
				insert(b->x-2, b->y-1,0,b->id, 0, 900, 485, NULL, b,img->s->terracotta_house_3x3_inside[3]);
				insert(b->x-1, b->y-2,0, b->id, 0, 900, 485, NULL, b,img->s->terracotta_house_3x3_inside[4]);
				insert(b->x-2, b->y-2,0, b->id, 0, 900, 476, NULL, b,img->s->terracotta_house_3x3_inside[5]);
			}
			else
			{
				insert(b->x, b->y, 19,b->id, 0, 900, 484, NULL, b,img->s->terracotta_house_3x3[0]);
				insert(b->x, b->y-1,38,b->id, 0, 900, 484, NULL, b,img->s->terracotta_house_3x3[1]);
				insert(b->x, b->y-2,57,b->id, 0, 900, 484, NULL, b,img->s->terracotta_house_3x3[2]);
				insert(b->x-1, b->y, 95,b->id, 0, 900, 484, NULL, b,img->s->terracotta_house_3x3[3]);
				insert(b->x-1, b->y-1,76, b->id, 0, 909, 446, NULL, b,img->s->terracotta_house_3x3[4]);
				insert(b->x-1, b->y-2,76, b->id, 0, 900, 427, NULL, b,img->s->terracotta_house_3x3[5]);
				insert(b->x-2, b->y, 76,b->id, 0, 891, 484, NULL, b,img->s->terracotta_house_3x3[6]);
				insert(b->x-2, b->y-1, 76,b->id, 0, 900, 399, NULL, b,img->s->terracotta_house_3x3[7]);
				insert(b->x-2, b->y-2, 76,b->id, 0, 900, 408, NULL, b,img->s->terracotta_house_3x3[8]);	
			}
		}
		else if (b->skin[2] == '3')
		{
			if (moi != NULL && b->id == moi->inside)
				insert(b->x-5, b->y-5, 0, b->id, 0, 900, 650, NULL, b,img->s->wooden_house_6x6[10]);
			else
			{
				insert(b->x, b->y, 76, b->id, 0, 900, 409, NULL, b,img->s->wooden_house_6x6[1]);
				insert(b->x-1, b->y,76, b->id, 0, 900, 484, NULL, b,img->s->wooden_house_6x6[4]);
				insert(b->x-2, b->y, 76, b->id, 0, 900, 484, NULL, b,img->s->wooden_house_6x6[3]);
				insert(b->x-3, b->y, 76, b->id, 0, 900, 484, NULL, b,img->s->wooden_house_6x6[3]);
				insert(b->x-4, b->y, 76, b->id, 0, 900, 484, NULL, b,img->s->wooden_house_6x6[3]);
				insert(b->x-5, b->y, 76, b->id, 0, 900, 484, NULL, b,img->s->wooden_house_6x6[5]);
				insert(b->x, b->y-1, 76, b->id, 0, 900, 484, NULL, b,img->s->wooden_house_6x6[8]);
				insert(b->x-1, b->y-1, 76, b->id, 0, 900, 389, NULL, b,img->s->wooden_house_6x6[1]);
				insert(b->x-2, b->y-1, 76, b->id, 0, 900, 389, NULL, b,img->s->wooden_house_6x6[1]);
				insert(b->x-3, b->y-1, 76, b->id, 0, 900, 389, NULL, b,img->s->wooden_house_6x6[1]);
				insert(b->x-4, b->y-1, 76, b->id, 0, 900, 389, NULL, b,img->s->wooden_house_6x6[1]);
				insert(b->x-5, b->y-1, 76, b->id, 0, 900, 389, NULL, b,img->s->wooden_house_6x6[1]);
				insert(b->x, b->y-2, 76, b->id, 0, 900, 484, NULL, b,img->s->wooden_house_6x6[9]);
				insert(b->x-1, b->y-2,76, b->id, 0, 900, 371, NULL, b,img->s->wooden_house_6x6[1]);
				insert(b->x-2, b->y-2, 76, b->id, 0, 900, 371, NULL, b,img->s->wooden_house_6x6[1]);
				insert(b->x-3, b->y-2, 76, b->id, 0, 900, 371, NULL, b,img->s->wooden_house_6x6[1]);
				insert(b->x-4, b->y-2, 76, b->id, 0, 900, 371, NULL, b,img->s->wooden_house_6x6[1]);
				insert(b->x-5, b->y-2, 76, b->id, 0, 900, 371, NULL, b,img->s->wooden_house_6x6[1]);
				insert(b->x, b->y-3, 76, b->id, 0, 900, 484, NULL, b,img->s->wooden_house_6x6[6]);
				insert(b->x-1, b->y-3, 76, b->id, 0, 900, 357, NULL, b,img->s->wooden_house_6x6[0]);
				insert(b->x-2, b->y-3, 76, b->id, 0, 900, 357, NULL, b,img->s->wooden_house_6x6[0]);
				insert(b->x-3, b->y-3, 76, b->id, 0, 900, 357, NULL, b,img->s->wooden_house_6x6[0]);
				insert(b->x-4, b->y-3, 76, b->id, 0, 900, 357, NULL, b,img->s->wooden_house_6x6[0]);
				insert(b->x-5, b->y-3, 76, b->id, 0, 900, 357, NULL, b,img->s->wooden_house_6x6[0]);
				insert(b->x, b->y-4, 76, b->id, 0, 900, 484, NULL, b,img->s->wooden_house_6x6[7]);
				insert(b->x-1, b->y-4, 76, b->id, 0, 900, 376, NULL, b,img->s->wooden_house_6x6[0]);
				insert(b->x-2, b->y-4, 76, b->id, 0, 900, 376, NULL, b,img->s->wooden_house_6x6[0]);
				insert(b->x-3, b->y-4, 76, b->id, 0, 900, 376, NULL, b,img->s->wooden_house_6x6[0]);
				insert(b->x-4, b->y-4, 76, b->id, 0, 900, 376, NULL, b,img->s->wooden_house_6x6[0]);
				insert(b->x-5, b->y-4, 76, b->id, 0, 900, 376, NULL, b,img->s->wooden_house_6x6[0]);
				insert(b->x, b->y-5, 76, b->id, 0, 900, 484, NULL, b,img->s->wooden_house_6x6[2]);
				insert(b->x-1, b->y-5, 76, b->id, 0, 900, 399, NULL, b,img->s->wooden_house_6x6[0]);
				insert(b->x-2, b->y-5, 76, b->id, 0, 900, 399, NULL, b,img->s->wooden_house_6x6[0]);
				insert(b->x-3, b->y-5, 76, b->id, 0, 900, 399, NULL, b,img->s->wooden_house_6x6[0]);
				insert(b->x-4, b->y-5, 76, b->id, 0, 900, 399, NULL, b,img->s->wooden_house_6x6[0]);
				insert(b->x-5, b->y-5, 76, b->id, 0, 900, 399, NULL, b,img->s->wooden_house_6x6[0]);
			}
	
		}

	}
	else if (strcmp(b->skin, "125") == 0)
	{
		insert(b->x, b->y, 0,b->id, 0, 900, 484, NULL, b,img->s->bridgePillar);
		insert(b->x+4, b->y,0,b->id, 0, 900, 484, NULL, b,img->s->bridgePillar);
		insert(b->x+1, b->y,0,b->id, 0, 900, 408, NULL, b,img->s->bridgeSlab);
		insert(b->x+2, b->y,0,b->id, 0, 900, 408, NULL, b,img->s->bridgeSlab);
		insert(b->x+3, b->y,0,b->id, 0, 900, 408, NULL, b,img->s->bridgeSlab);
	}
		
	else if (strcmp(b->skin, "131") == 0)
	{
		if (moi != NULL && b->id == moi->inside)
		//if (1 == 1)
		{
			if (b->angle =='h')
			{
				insert(b->x-2, b->y-3,0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x-1, b->y-3,0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x, b->y-3, 0,b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x+1, b->y-3,0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x+2, b->y-3, 0,b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x-2, b->y-2,0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x-1, b->y-2,0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x+1, b->y-2,0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x+2, b->y-2,0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);	
				insert(b->x-2, b->y-1,0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x-1, b->y-1,0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x+1, b->y-1, 0,b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x+2, b->y-1,0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x-2, b->y,0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x-1, b->y,0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x+1, b->y,0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x+2, b->y, 0,b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x-2, b->y+1,0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x-1, b->y+1,0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x+1, b->y+1,0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x+2, b->y+1,0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x-2, b->y+2,0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x-1, b->y+2,0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x-0, b->y+2,0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x+1, b->y+2,0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x+2, b->y+2,0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x+1, b->y+3,0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x, b->y+3, 0,b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x-1, b->y+3,0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x+1, b->y-4, 0,b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x, b->y-4, 0,b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x-1, b->y-4,0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x, b->y+4,0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x, b->y-2, 0,b->id, 0, 900, 484, NULL, b, img->s->ship1_50cm_wood);
				insert(b->x, b->y-1,0, b->id, 0, 900, 484, NULL, b, img->s->ship1_100cm_wood);
				insert(b->x, b->y, 0,b->id, 0, 900, 484, NULL, b, img->s->ship1_150cm_wood);
				insert(b->x, b->y+1, 0,b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x+2, b->y+3,0, b->id, 0, 900, 468, NULL, b, img->s->ship1_flat_wood_up_triangle);
				insert(b->x+1, b->y+4,0, b->id, 0, 900, 468, NULL, b, img->s->ship1_flat_wood_up_triangle);
				insert(b->x-2, b->y-4,0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood_down_triangle);
				insert(b->x+2, b->y-4,0, b->id, 0, 883, 484, NULL, b, img->s->ship1_flat_wood_left_triangle);
				insert(b->x-1, b->y+4,0, b->id, 0, 917, 484, NULL, b, img->s->ship1_flat_wood_right_triangle);
				insert(b->x-2, b->y+3,0, b->id, 0, 917, 484, NULL, b, img->s->ship1_flat_wood_right_triangle);		
			}
			else if (b->angle =='d')
			{
				insert(b->x-2, b->y-2,0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x-1, b->y-2,0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x+1, b->y-2, 0,b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x+2, b->y-2,0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x-2, b->y-1,0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x-1, b->y-1,0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x+1, b->y-1,0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x+2, b->y-1,0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x-2, b->y, 0,b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x-1, b->y, 0,b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x+1, b->y, 0,b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x+2, b->y, 0,b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x-2, b->y+1, 0,b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x-1, b->y+1, 0,b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x+1, b->y+1, 0,b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x+2, b->y+1, 0,b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x-2, b->y+2, 0,b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x-1, b->y+2, 0,b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x+1, b->y+2, 0,b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x+2, b->y+2, 0,b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x-2, b->y+3, 0,b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x-1, b->y+3, 0,b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x, b->y+3, 0,b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x+1, b->y+3, 0,b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x+2, b->y+3,0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x, b->y-2, 0,b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x+1, b->y+4, 0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x, b->y+4, 0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x-1, b->y+4, 0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x+1, b->y-3, 0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x, b->y-3, 0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x-1, b->y-3, 0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x, b->y-4, 0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x, b->y+2, 0, b->id, 0, 900, 484, NULL, b, img->s->ship1_50cm_wood);
				insert(b->x, b->y+1, 0, b->id, 0, 900, 484, NULL, b, img->s->ship1_100cm_wood);
				insert(b->x, b->y, 0, b->id, 0, 900, 484, NULL, b, img->s->ship1_150cm_wood);
				insert(b->x, b->y-1, 0, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x+2, b->y+4, 0, b->id, 0, 900, 468, NULL, b, img->s->ship1_flat_wood_up_triangle);
				insert(b->x-1, b->y-4, 0, b->id, 0,  900, 484, NULL, b, img->s->ship1_flat_wood_down_triangle);
				insert(b->x+2, b->y-3, 0, b->id, 0, 883, 484, NULL, b, img->s->ship1_flat_wood_left_triangle);
				insert(b->x+1, b->y-4, 0, b->id, 0, 883, 484, NULL, b, img->s->ship1_flat_wood_left_triangle);
				insert(b->x-2, b->y+4, 0, b->id, 0, 917, 484, NULL, b, img->s->ship1_flat_wood_right_triangle);
				insert(b->x-2, b->y-3, 0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood_down_triangle);
			}
			else if (b->angle =='f')
			{
				insert(b->x-3, b->y-2, 0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x-2, b->y-2, 0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x-1, b->y-2, 0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x, b->y-2, 0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x+1, b->y-2, 0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x+2, b->y-2, 0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x-3, b->y-1, 0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x-2, b->y-1, 0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x-1, b->y-1, 0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x, b->y-1, 0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x+1, b->y-1, 0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x+2, b->y-1, 0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x-3, b->y, 0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x+2, b->y, 0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x-3, b->y+1, 0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x-2, b->y+1, 0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x-1, b->y+1, 0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x, b->y+1, 0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x+1, b->y+1, 0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x+2, b->y+1, 0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x-3, b->y+2, 0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x-2, b->y+2, 0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x-1, b->y+2, 0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x, b->y+2, 0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x+1, b->y+2, 0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x+2, b->y+2, 0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x-4, b->y+1, 0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x-4, b->y, 0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x-4, b->y-1, 0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x+3, b->y-1, 0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x+3, b->y+1, 0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x+3, b->y, 0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x+4, b->y, 0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x-2, b->y, 0, b->id, 0, 900, 484, NULL, b, img->s->ship1_50cm_wood);
				insert(b->x-1, b->y, 0, b->id, 0, 900, 484, NULL, b, img->s->ship1_100cm_wood);
				insert(b->x, b->y, 0, b->id, 0, 900, 484, NULL, b, img->s->ship1_150cm_wood);
				insert(b->x+1, b->y, 0, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x+4, b->y+1, 0, b->id, 0, 900, 468, NULL, b, img->s->ship1_flat_wood_up_triangle);
				insert(b->x+3, b->y+2, 0, b->id, 0, 900, 468, NULL, b, img->s->ship1_flat_wood_up_triangle);
				insert(b->x-4, b->y-2, 0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood_down_triangle);
				insert(b->x+4, b->y-1, 0, b->id, 0,883, 484, NULL, b, img->s->ship1_flat_wood_left_triangle);
				insert(b->x+3, b->y-2, 0, b->id, 0, 883, 484, NULL, b, img->s->ship1_flat_wood_left_triangle);
				insert(b->x-4, b->y+2, 0, b->id, 0,917, 484, NULL, b, img->s->ship1_flat_wood_right_triangle);
			}
			else if (b->angle =='b')
			{
				insert(b->x+3, b->y-2, 0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x-2, b->y-2, 0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x-1, b->y-2, 0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x, b->y-2, 0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x+1, b->y-2, 0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x+2, b->y-2, 0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x+3, b->y-1, 0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x-2, b->y-1, 0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x-1, b->y-1, 0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x, b->y-1, 0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x+1, b->y-1, 0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x+2, b->y-1, 0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x+3, b->y, 0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x-2, b->y, 0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x+3, b->y+1, 0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x-2, b->y+1, 0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x-1, b->y+1, 0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x, b->y+1, 0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x+1, b->y+1, 0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x+2, b->y+1, 0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x+3, b->y+2, 0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x-2, b->y+2, 0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x-1, b->y+2, 0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x, b->y+2, 0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x+1, b->y+2, 0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x+2, b->y+2, 0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x-3, b->y+1, 0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x-3, b->y, 0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x-3, b->y-1, 0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x+4, b->y+1, 0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x+4, b->y, 0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x+4, b->y-1, 0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x-4, b->y, 0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood);
				insert(b->x+2, b->y, 0, b->id, 0, 900, 484, NULL, b, img->s->ship1_50cm_wood);
				insert(b->x+1, b->y, 0, b->id, 0, 900, 484, NULL, b, img->s->ship1_100cm_wood);
				insert(b->x, b->y, 0, b->id, 0, 900, 484, NULL, b, img->s->ship1_150cm_wood);
				insert(b->x-1, b->y, 0, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x+4, b->y+2, 0, b->id, 0,900, 468, NULL, b, img->s->ship1_flat_wood_up_triangle);
				insert(b->x-4, b->y-1, 0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood_down_triangle);
				insert(b->x-3, b->y-2, 0, b->id, 0, 900, 484, NULL, b, img->s->ship1_flat_wood_down_triangle);
				insert(b->x+4, b->y-2, 0, b->id, 0, 883, 484, NULL, b, img->s->ship1_flat_wood_left_triangle);
				insert(b->x-4, b->y+1, 0, b->id, 0, 917, 484, NULL, b, img->s->ship1_flat_wood_right_triangle);
				insert(b->x-3, b->y+2, 0, b->id, 0, 917, 484, NULL, b, img->s->ship1_flat_wood_right_triangle);
			}
		}
		else
		{
			if (b->angle =='h')
			{
				insert(b->x-2, b->y-3, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x-1, b->y-3, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x+1, b->y-3, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x+2, b->y-3, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x-2, b->y-2, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x-1, b->y-2, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x+1, b->y-2, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x+2, b->y-2, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x-2, b->y-1, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x-1, b->y-1, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x+1, b->y-1, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x+2, b->y-1, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x-2, b->y, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x-1, b->y, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x+1, b->y, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x+2, b->y, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x-2, b->y+1, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x-1, b->y+1, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x+1, b->y+1, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x+2, b->y+1, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x-2, b->y+2, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x-1, b->y+2, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x+1, b->y+2, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x+2, b->y+2, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x+1, b->y+3, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x, b->y+3, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x-1, b->y+3, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x+1, b->y-4, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x, b->y-4, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x-1, b->y-4, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x, b->y+4, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x+2, b->y+3, 114, b->id, 0, 900, 467, NULL, b, img->s->ship1_200cm_wood_triangle);
				insert(b->x+1, b->y+4, 114, b->id, 0, 900, 467, NULL, b, img->s->ship1_200cm_wood_triangle);
				insert(b->x-2, b->y-4, 114, b->id, 0, 900, 409, NULL, b, img->s->ship1_flat_wood_down_triangle);
				insert(b->x+2, b->y-4, 114, b->id, 0,  883, 409, NULL, b, img->s->ship1_flat_wood_left_triangle);
				insert(b->x-1, b->y+4, 114, b->id, 0, 917, 409, NULL, b, img->s->ship1_flat_wood_right_triangle);
				insert(b->x-2, b->y+3, 114, b->id, 0, 917, 409, NULL, b, img->s->ship1_flat_wood_right_triangle);
				if (b->state != '0')
				{
					insert(b->x, b->y-3, 114, b->id, 0, 882, 409	, NULL, b, img->s->ship1_bigSail);
					insert(b->x, b->y+2, 114, b->id, 0, 882, 409, NULL, b, img->s->ship1_bigSail);
				}
				else
				{
					insert(b->x, b->y-3, 114, b->id, 0, 882, 409	, NULL, b, img->s->ship1_bigSailFolded);
					insert(b->x, b->y+2, 114, b->id, 0, 882, 409, NULL, b, img->s->ship1_bigSailFolded);
				}
			}

			else if (b->angle =='d')
			{
				insert(b->x-2, b->y-2, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x-1, b->y-2, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x+1, b->y-2, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x+2, b->y-2, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x-2, b->y-1, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x-1, b->y-1, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x+1, b->y-1, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x+2, b->y-1, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x-2, b->y, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x-1, b->y, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x+1, b->y, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x+2, b->y, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x-2, b->y+1, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x-1, b->y+1, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x+1, b->y+1, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x+2, b->y+1, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x-2, b->y+2, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x-1, b->y+2, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x+1, b->y+2, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x+2, b->y+2, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x-2, b->y+3, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x-1, b->y+3, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x+1, b->y+3, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x+2, b->y+3, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x+1, b->y+4, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x, b->y+4, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x-1, b->y+4, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x+1, b->y-3, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x, b->y-3, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x-1, b->y-3, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x, b->y-4, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x+2, b->y+4, 114, b->id, 0, 900, 467, NULL, b, img->s->ship1_200cm_wood_triangle);
				insert(b->x-1, b->y-4, 114, b->id, 0, 900, 409, NULL, b, img->s->ship1_flat_wood_down_triangle);
				insert(b->x+2, b->y-3, 114, b->id, 0, 883, 409, NULL, b, img->s->ship1_flat_wood_left_triangle);
				insert(b->x+1, b->y-4, 114, b->id, 0, 883, 409, NULL, b, img->s->ship1_flat_wood_left_triangle);
				insert(b->x-2, b->y+4, 114, b->id, 0, 917, 409, NULL, b, img->s->ship1_flat_wood_right_triangle);
				insert(b->x-2, b->y-3, 114, b->id, 0, 900, 409, NULL, b, img->s->ship1_flat_wood_down_triangle);
				if (b->state != '0')
				{
					insert(b->x, b->y+3, 114, b->id, 0, 882, 409	, NULL, b, img->s->ship1_bigSail);
					insert(b->x, b->y-2, 114, b->id, 0, 882, 409, NULL, b, img->s->ship1_bigSail);
				}
				else
				{
					insert(b->x, b->y+3, 114, b->id, 0, 882, 409	, NULL, b, img->s->ship1_bigSailFolded);
					insert(b->x, b->y-2, 114, b->id, 0, 882, 409, NULL, b, img->s->ship1_bigSailFolded);
				}
			}
			else if (b->angle =='f')
			{
				insert(b->x-3, b->y-2, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x-2, b->y-2, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x-1, b->y-2, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x, b->y-2, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x+1, b->y-2, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x+2, b->y-2, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x-3, b->y-1, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x-2, b->y-1, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x-1, b->y-1, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x, b->y-1, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x+1, b->y-1, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x+2, b->y-1, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x-3, b->y+1, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x-2, b->y+1, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x-1, b->y+1, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x, b->y+1, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x+1, b->y+1, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x+2, b->y+1, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x-3, b->y+2, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x-2, b->y+2, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x-1, b->y+2, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x, b->y+2, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x+1, b->y+2, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x+2, b->y+2, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x-4, b->y+1, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x-4, b->y, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x-4, b->y-1, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x+3, b->y-1, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x+3, b->y+1, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x+3, b->y, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x+4, b->y, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x+4, b->y+1, 114, b->id, 0, 900, 467, NULL, b, img->s->ship1_200cm_wood_triangle);
				insert(b->x+3, b->y+2, 114, b->id, 0, 900, 467, NULL, b, img->s->ship1_200cm_wood_triangle);
				insert(b->x-4, b->y-2, 114, b->id, 0, 900, 409, NULL, b, img->s->ship1_flat_wood_down_triangle);
				insert(b->x+4, b->y-1, 114, b->id, 0, 883, 409, NULL, b, img->s->ship1_flat_wood_left_triangle);
				insert(b->x+3, b->y-2, 114, b->id, 0, 883, 409, NULL, b, img->s->ship1_flat_wood_left_triangle);
				insert(b->x-4, b->y+2, 114, b->id, 0, 917, 409, NULL, b, img->s->ship1_flat_wood_right_triangle);
				if (b->state != '0')
				{
					insert(b->x-3, b->y, 114, b->id, 0, 882, 409	, NULL, b, img->s->ship1_bigSail);
					insert(b->x+2, b->y, 114, b->id, 0, 882, 409, NULL, b, img->s->ship1_bigSail);
				}
				else
				{
					insert(b->x-3, b->y, 114, b->id, 0, 882, 409	, NULL, b, img->s->ship1_bigSailFolded);
					insert(b->x+2, b->y, 114, b->id, 0, 882, 409, NULL, b, img->s->ship1_bigSailFolded);
				}
			}
			else if (b->angle =='b')
			{
				insert(b->x+3, b->y-2, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x-2, b->y-2, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x-1, b->y-2, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x, b->y-2, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x+1, b->y-2, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x+2, b->y-2, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x+3, b->y-1, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x-2, b->y-1, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x-1, b->y-1, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x, b->y-1, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x+1, b->y-1, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x+2, b->y-1, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x+3, b->y+1, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x-2, b->y+1, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x-1, b->y+1, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x, b->y+1, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x+1, b->y+1, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x+2, b->y+1, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x+3, b->y+2, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x-2, b->y+2, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x-1, b->y+2, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x, b->y+2, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x+1, b->y+2, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x+2, b->y+2, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x-3, b->y+1, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x-3, b->y, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x-3, b->y-1, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x+4, b->y+1, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x+4, b->y, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x+4, b->y-1, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x-4, b->y, 114, b->id, 0, 900, 484, NULL, b, img->s->ship1_200cm_wood);
				insert(b->x+4, b->y+2, 114, b->id, 0, 900, 467, NULL, b, img->s->ship1_200cm_wood_triangle);
				insert(b->x-4, b->y-1, 114, b->id, 0, 900, 409, NULL, b, img->s->ship1_flat_wood_down_triangle);
				insert(b->x-3, b->y-2, 114, b->id, 0, 900, 409, NULL, b, img->s->ship1_flat_wood_down_triangle);
				insert(b->x+4, b->y-2, 114, b->id, 0, 883, 409, NULL, b, img->s->ship1_flat_wood_left_triangle);
				insert(b->x-4, b->y+1, 114, b->id, 0, 917, 409, NULL, b, img->s->ship1_flat_wood_right_triangle);
				insert(b->x-3, b->y+2, 114, b->id, 0, 917, 409, NULL, b, img->s->ship1_flat_wood_right_triangle);
				if (b->state != '0')
				{
					insert(b->x+3, b->y, 114, b->id, 0, 882, 409	, NULL, b, img->s->ship1_bigSail);
					insert(b->x-2, b->y, 114, b->id, 0, 882, 409, NULL, b, img->s->ship1_bigSail);
				}
				else
				{
					insert(b->x+3, b->y, 114, b->id, 0, 882, 409	, NULL, b, img->s->ship1_bigSailFolded);
					insert(b->x-2, b->y, 114, b->id, 0, 882, 409, NULL, b, img->s->ship1_bigSailFolded);
				}
			}
		}
	}
	else if (b->skin[1] == '4') // fondation
	{
		if (b->skin[2] == '1') // bois
		{
			insert(b->x, b->y, 76,b->id, 0, 900, 483, NULL, b,img->s->wood_pillar);
		}
	}
}

void init_stat(struct personnages *p)
{
	list_disp = deleteKey_char(p->id);
	actualise_stat(p);
}