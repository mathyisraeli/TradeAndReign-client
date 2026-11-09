#include "control.h"
extern struct lettres *lettres;

void deplacement(struct personnages *moi)
{
	if (moi->faim < 0)
	{
		sprintf (ordre + strlen(ordre), "0 %d 00 -1 ", moi->id); // bug #42: a stray capital 'O' here (instead of the digit '0' parse_order's tmpC[0] switch actually checks) left the server unable to recognize this starvation-damage tag at all - parse_order's shared id/idaction header still consumed, but no case body ran to skip the "-1 " value, so the next loop iteration resumed mid-value instead of at the next tag, desyncing every order field after it for the rest of that tick's batch until it crashed (confirmed live: a connected player's own character going hungry below zero segfaulted the server inside the unrelated building branch, on a garbage id picked up from the desynced bytes)
	}
	if (moi->animation > 6)
		sprintf (ordre + strlen(ordre), "0 %d 22 0 0 %d 21 0 ", moi->id, moi->id);
	else if (moi->animation_2 > 0)
		sprintf(ordre + strlen(ordre), "0 %d 21 %d ",moi->id, moi->animation +1 );
	else if (lettres->Mouse_Lclick == 1 && lettres->Mouse_Rclick == 1)
	{
		sprintf (ordre + strlen(ordre), "0 %d 22 1 0 %d 21 0 ", moi->id, moi->id);
		struct personnages *closestt = NULL;
		struct building *closest_building = NULL;
		float reach_sq = moi->porte_dom > 0 ? moi->porte_dom * moi->porte_dom : 4.0f;
		float closest = reach_sq;
		float closest_building_dist = reach_sq;
		for (struct linked_list *parcour = list; parcour != NULL; parcour = parcour->next)
		{
			if (parcour->p == moi)
				continue;
			float distx = parcour->p->x - moi->x;
			float disty = parcour->p->y - moi->y;
			float dist = distx * distx + disty * disty;	
			int in_cone = 0;
			/* same tile or adjacent: allow hit regardless of facing (continuous positions) */
			if (dist < 2.5f)
				in_cone = 1;
			else if (moi->angle == 'e') /* +0.7x -0.7y */
				in_cone = (distx > 0 && fabs(disty) <= distx * 1.5f);
			else if (moi->angle == 'a') /* -0.7x +0.7y */
				in_cone = (distx < 0 && fabs(disty) <= -distx * 1.5f);
			else if (moi->angle == 'c') /* -0.7x -0.7y */
				in_cone = (distx < 0 && disty < 0 && distx / (disty + 0.001f) > 0.4f && disty / (distx + 0.001f) > 0.4f);
			else if (moi->angle == 'g') /* +0.7x +0.7y */
				in_cone = (distx > 0 && disty > 0 && distx / (disty + 0.001f) > 0.4f && disty / (distx + 0.001f) > 0.4f);
			else if (moi->angle == 'b') /* -speed in x */
				in_cone = (distx < 0 && fabs(disty) <= -distx * 1.5f);
			else if (moi->angle == 'd') /* -speed in y */
				in_cone = (disty < 0 && fabs(distx) <= -disty * 1.5f);
			else if (moi->angle == 'f') /* +speed in x */
				in_cone = (distx > 0 && fabs(disty) <= distx * 1.5f);
			else if (moi->angle == 'h') /* +speed in y */
				in_cone = (disty > 0 && fabs(distx) <= disty * 1.5f);
			if (in_cone && dist < closest)
			{
				closest = dist;
				closestt = parcour->p;
			}
		}
		/* also check buildings (use continuous moi->x/y, buildings are tile-based) */
		for (struct building *b = list_building; b != NULL; b = b->next)
		{
			/* building center: use tile center (b->x+0.5, b->y+0.5) for same-tile fairness */
			float bx = (float)b->x + 0.5f, by = (float)b->y + 0.5f;
			float distx = bx - moi->x;
			float disty = by - moi->y;
			float dist = distx * distx + disty * disty;
			if (dist > reach_sq)
				continue;
			int in_cone = 0;
			if (dist < 2.5f) /* same tile or adjacent */
				in_cone = 1;
			else if (moi->angle == 'e')
				in_cone = (distx > 0 && fabs(disty) <= distx * 1.5f);
			else if (moi->angle == 'b')
				in_cone = (distx < 0 && fabs(disty) <= -distx * 1.5f);
			else if (moi->angle == 'h')
				in_cone = (disty > 0 && fabs(distx) <= disty * 1.5f);
			else if (moi->angle == 'g')
				in_cone = (distx > 0 && disty > 0 && distx / (disty + 0.001f) > 0.4f && disty / (distx + 0.001f) > 0.4f);
			else if (moi->angle == 'a' || moi->angle == 'c')
				in_cone = (distx < 0 && disty < 0 && distx / (disty + 0.001f) > 0.4f && disty / (distx + 0.001f) > 0.4f);
			else if (moi->angle == 'd')
				in_cone = (disty < 0 && fabs(distx) <= -disty * 1.5f);
			else if (moi->angle == 'f')
				in_cone = (distx > 0 && fabs(disty) <= distx * 1.5f);
			if (in_cone && dist < closest_building_dist)
			{
				closest_building_dist = dist;
				closest_building = b;
			}
		}

		/* choose closest target among personnages and buildings */
		if (closestt || closest_building)
		{
			if (closestt && (!closest_building || closest <= closest_building_dist))
			{
				/* hit personnage (including trees, skin[1]=='1') */
				if (closestt->skin[1] == '1')
				{
					if (closestt->pv -  moi->dom >= 4)
						sprintf(ordre + strlen(ordre), "0 %d 00 -%d ", closestt->id, moi->dom);
					else if (can_add("wooden-board", 1, moi->items, moi->items_cnt) == 1)
						sprintf(ordre + strlen(ordre), "0 %d 00 -1 0 %d 16 +1 wooden-board ", closestt->id, moi->id);
				}
				else
					sprintf(ordre + strlen(ordre), "0 %d 00 -%d ", closestt->id, moi->dom);
			}
			else if (closest_building)
			{
				/* hit building */
				sprintf(ordre + strlen(ordre), "1 %d 00 -%d ", closest_building->id, moi->dom);
			}
		}
	}
	else
	{
		if(lettres->keystates[SDL_SCANCODE_D])//droite
			sprintf (ordre + strlen(ordre), "0 %d 01 +%f 0 %d 02 -%f 0 %d 05 e 0 %d 21 %d ", moi->id, 0.707, moi->id, 0.707, moi->id, moi->id, moi->animation+1);
		if(lettres->keystates[SDL_SCANCODE_A])
			sprintf (ordre + strlen(ordre), "0 %d 01 -%f 0 %d 02 +%f 0 %d 05 a 0 %d 21 %d ", moi->id, 0.707, moi->id, 0.707, moi->id, moi->id, moi->animation+1);
		if(lettres->keystates[SDL_SCANCODE_W])
			sprintf (ordre + strlen(ordre), "0 %d 01 -%f 0 %d 02 -%f 0 %d 05 c 0 %d 21 %d ", moi->id, 0.707, moi->id, 0.707, moi->id, moi->id, moi->animation+1);
		if(lettres->keystates[SDL_SCANCODE_X])
			sprintf (ordre + strlen(ordre), "0 %d 01 +%f 0 %d 02 +%f 0 %d 05 g 0 %d 21 %d ", moi->id, 0.707, moi->id, 0.707, moi->id, moi->id, moi->animation+1);
		if(lettres->keystates[SDL_SCANCODE_Q])
			sprintf (ordre + strlen(ordre), "0 %d 01 -%f 0 %d 05 b 0 %d 21 %d ", moi->id, 1.0, moi->id, moi->id, moi->animation+1); 
		if(lettres->keystates[SDL_SCANCODE_E])
			sprintf (ordre + strlen(ordre), "0 %d 02 -%f 0 %d 05 d 0 %d 21 %d ", moi->id, 1.0, moi->id, moi->id, moi->animation+1);
		if(lettres->keystates[SDL_SCANCODE_C])
			sprintf (ordre + strlen(ordre), "0 %d 01 +%f 0 %d 05 f 0 %d 21 %d ", moi->id, 1.0, moi->id, moi->id, moi->animation+1);
		if(lettres->keystates[SDL_SCANCODE_Z])
			sprintf (ordre + strlen(ordre), "0 %d 02 +%f 0 %d 05 h 0 %d 21 %d ", moi->id, 1.0, moi->id, moi->id, moi->animation+1);
		if(lettres->keystates[SDL_SCANCODE_SPACE])
			sprintf (ordre + strlen(ordre), "0 %d 31 +3 0 %d 21 %d ", moi->id, moi->id, moi->animation+1);
		if(lettres->keystates[SDL_SCANCODE_V])
		{
			struct building *b = find_building_by_id(building_id[(int)moi->x + (int)moi->y*max_x]);
			if (b != NULL)
			{
				if (b->state == '0')
					sprintf (ordre + strlen(ordre), "1 %d 04 1 ", b->id);
				else
					sprintf (ordre + strlen(ordre), "1 %d 04 0 ", b->id);
			}
		}
		if(lettres->keystates[SDL_SCANCODE_F])
		{
			struct building *b = find_building_by_id(building_id[(int)moi->x + (int)moi->y*max_x]);
			if (b != NULL)
				sprintf (ordre + strlen(ordre), "1 %d 04 2 ", b->id);
		}
		if(lettres->keystates[SDL_SCANCODE_R])
		{
			struct building *b = find_building_by_id(building_id[(int)moi->x + (int)moi->y*max_x]);
			if (b != NULL)
				sprintf (ordre + strlen(ordre), "1 %d 04 3 ", b->id);
		}
		if(lettres->keystates[SDL_SCANCODE_S])
		{
			if (ground_altitude[((int)moi->y - start_y) * (end_x - start_x) + (int)moi->x - start_x] > 0 && find_building_by_id(building_id[(int)moi->x + ((int)moi->y)*max_x]) == NULL)
			{
				SDL_Texture *t = ground_texture[((int)moi->y - start_y) * (end_x - start_x) + (int)moi->x - start_x];
				if (10 > n_item(moi->items))
				{
					if (t == img->t->soi)
						sprintf (ordre + strlen(ordre), "0 %d 16 +1 soil 0 %d 08 %d 0 %d 22 2 0 %d 21 0 ", moi->id, moi->id, (int)moi->x + ((int)moi->y)*max_x, moi->id, moi->id);		
					else if (t == img->t->snd)
						sprintf (ordre + strlen(ordre), "0 %d 16 +1 sand 0 %d 08 %d 0 %d 22 2 0 %d 21 0 ", moi->id, moi->id, (int)moi->x + ((int)moi->y)*max_x, moi->id, moi->id);
					else if (t == img->t->gco)
						sprintf (ordre + strlen(ordre), "0 %d 16 +1 coal 0 %d 08 %d 0 %d 22 2 0 %d 21 0 ", moi->id, moi->id, (int)moi->x + ((int)moi->y)*max_x, moi->id, moi->id);
					else if (t == img->t->gst)
						sprintf (ordre + strlen(ordre), "0 %d 16 +1 salt 0 %d 08 %d 0 %d 22 2 0 %d 21 0 ", moi->id, moi->id, (int)moi->x + ((int)moi->y)*max_x, moi->id, moi->id);
					else if (t == img->t->gli)
						sprintf (ordre + strlen(ordre), "0 %d 16 +1 limestone 0 %d 08 %d 0 %d 22 2 0 %d 21 0 ", moi->id, moi->id, (int)moi->x + ((int)moi->y)*max_x, moi->id, moi->id);
					else if (t == img->t->gqa)
						sprintf (ordre + strlen(ordre), "0 %d 16 +1 quartzite 0 %d 08 %d 0 %d 22 2 0 %d 21 0 ", moi->id, moi->id, (int)moi->x + ((int)moi->y)*max_x, moi->id, moi->id);
					else if (t == img->t->gqz)
						sprintf (ordre + strlen(ordre), "0 %d 16 +1 quartz 0 %d 08 %d 0 %d 22 2 0 %d 21 0 ", moi->id, moi->id, (int)moi->x + ((int)moi->y)*max_x, moi->id, moi->id);
					else if (t == img->t->gba)
						sprintf (ordre + strlen(ordre), "0 %d 16 +1 basalt 0 %d 08 %d 0 %d 22 2 0 %d 21 0 ", moi->id, moi->id, (int)moi->x + ((int)moi->y)*max_x, moi->id, moi->id);
					else if (t == img->t->ggr)
						sprintf (ordre + strlen(ordre), "0 %d 16 +1 granit 0 %d 08 %d 0 %d 22 2 0 %d 21 0 ", moi->id, moi->id, (int)moi->x + ((int)moi->y)*max_x, moi->id, moi->id);
					else if (t == img->t->gsa)
						sprintf (ordre + strlen(ordre), "0 %d 16 +1 sandstone 0 %d 08 %d 0 %d 22 2 0 %d 21 0 ", moi->id, moi->id, (int)moi->x + ((int)moi->y)*max_x, moi->id, moi->id);
					else if (t == img->t->gsh)
						sprintf (ordre + strlen(ordre), "0 %d 16 +1 shale 0 %d 08 %d 0 %d 22 2 0 %d 21 0 ", moi->id, moi->id, (int)moi->x + ((int)moi->y)*max_x, moi->id, moi->id);
					else if (t == img->t->gma)
						sprintf (ordre + strlen(ordre), "0 %d 16 +1 marble 0 %d 08 %d 0 %d 22 2 0 %d 21 0 ", moi->id, moi->id, (int)moi->x + ((int)moi->y)*max_x, moi->id, moi->id);
					else if (t == img->t->ggy)
						sprintf (ordre + strlen(ordre), "0 %d 16 +1 gypsum 0 %d 08 %d 0 %d 22 2 0 %d 21 0 ", moi->id, moi->id, (int)moi->x + ((int)moi->y)*max_x, moi->id, moi->id);
					
				}
				if (t == img->t->sno)
					sprintf (ordre + strlen(ordre), "0 0 08 %d 0 0 13 %d wat ", (int)moi->x + ((int)moi->y)*max_x, (int)moi->x + ((int)moi->y)*max_x);
				// a tool works from either hand (items[12] = left, items[13] = right)
				int tool_hand = -1;
				if (strcmp(moi->items[12], "wood-pickaxe") == 0 || strcmp(moi->items[12], "stone-pickaxe") == 0 || strcmp(moi->items[12], "wooden-wedge") == 0)
					tool_hand = 12;
				else if (strcmp(moi->items[13], "wood-pickaxe") == 0 || strcmp(moi->items[13], "stone-pickaxe") == 0 || strcmp(moi->items[13], "wooden-wedge") == 0)
					tool_hand = 13;
				if (tool_hand != -1)
				{
					if (t == img->t->lim)
					{
						if (rand() % 3 == 0) 
							sprintf (ordre + strlen(ordre), "0 0 08 %d 0 0 13 %d dus 0 %d 22 3 0 %d 21 0 ", (int)moi->x + ((int)moi->y)*max_x, (int)moi->x + ((int)moi->y)*max_x, moi->id, moi->id);
						else
							sprintf (ordre + strlen(ordre), "0 0 08 %d 0 0 13 %d gli 0 %d 22 3 0 %d 21 0 ", (int)moi->x + ((int)moi->y)*max_x, (int)moi->x + ((int)moi->y)*max_x, moi->id, moi->id);
					}
					if (t == img->t->qua)
					{
						sprintf (ordre + strlen(ordre), "0 0 08 %d 0 0 13 %d gqa 0 %d 22 3 0 %d 21 0 ", (int)moi->x + ((int)moi->y)*max_x, (int)moi->x + ((int)moi->y)*max_x, moi->id, moi->id);
					}
					if (t == img->t->quz)
					{
						if (rand() % 2 == 0) 
							sprintf (ordre + strlen(ordre), "0 0 08 %d 0 0 13 %d gqz 0 %d 22 3 0 %d 21 0 ", (int)moi->x + ((int)moi->y)*max_x, (int)moi->x + ((int)moi->y)*max_x, moi->id, moi->id);
						else
							sprintf (ordre + strlen(ordre), "0 0 08 %d 0 0 13 %d snd 0 %d 22 3 0 %d 21 0 ", (int)moi->x + ((int)moi->y)*max_x, (int)moi->x + ((int)moi->y)*max_x, moi->id, moi->id);
					}
					if (t == img->t->bas)
					{
						sprintf (ordre + strlen(ordre), "0 0 08 %d 0 0 13 %d gba 0 %d 22 3 0 %d 21 0 ", (int)moi->x + ((int)moi->y)*max_x, (int)moi->x + ((int)moi->y)*max_x, moi->id, moi->id);
					}
					if (t == img->t->gra)
					{
						if (rand() % 3 == 0) 
							sprintf (ordre + strlen(ordre), "0 0 08 %d 0 0 13 %d snd 0 %d 22 3 0 %d 21 0 ", (int)moi->x + ((int)moi->y)*max_x, (int)moi->x + ((int)moi->y)*max_x, moi->id, moi->id);
						else
							sprintf (ordre + strlen(ordre), "0 0 08 %d 0 0 13 %d ggr 0 %d 22 3 0 %d 21 0 ", (int)moi->x + ((int)moi->y)*max_x, (int)moi->x + ((int)moi->y)*max_x, moi->id, moi->id);
					}
					if (t == img->t->san)
					{
						if (rand() % 2 == 0) 
							sprintf (ordre + strlen(ordre), "0 0 08 %d 0 0 13 %d gsa 0 %d 22 3 0 %d 21 0 ", (int)moi->x + ((int)moi->y)*max_x, (int)moi->x + ((int)moi->y)*max_x, moi->id, moi->id);
						else
							sprintf (ordre + strlen(ordre), "0 0 08 %d 0 0 13 %d snd 0 %d 22 3 0 %d 21 0 ", (int)moi->x + ((int)moi->y)*max_x, (int)moi->x + ((int)moi->y)*max_x, moi->id, moi->id);
					}
					if (t == img->t->sha)
					{
						if (rand() % 2 == 0) 
							sprintf (ordre + strlen(ordre), "0 0 08 %d 0 0 13 %d gsh 0 %d 22 3 0 %d 21 0 ", (int)moi->x + ((int)moi->y)*max_x, (int)moi->x + ((int)moi->y)*max_x, moi->id, moi->id);
						else
							sprintf (ordre + strlen(ordre), "0 0 08 %d 0 0 13 %d dus 0 %d 22 3 0 %d 21 0 ", (int)moi->x + ((int)moi->y)*max_x, (int)moi->x + ((int)moi->y)*max_x, moi->id, moi->id);
					}
					if (t == img->t->mar)
					{
						if (rand() % 3 == 0) 
							sprintf (ordre + strlen(ordre), "0 0 08 %d 0 0 13 %d dus 0 %d 22 3 0 %d 21 0 ", (int)moi->x + ((int)moi->y)*max_x, (int)moi->x + ((int)moi->y)*max_x, moi->id, moi->id);
						else
							sprintf (ordre + strlen(ordre), "0 0 08 %d 0 0 13 %d gma 0 %d 22 3 0 %d 21 0 ", (int)moi->x + ((int)moi->y)*max_x, (int)moi->x + ((int)moi->y)*max_x, moi->id, moi->id);
					}
					if (t == img->t->gyp)
					{
						if (rand() % 2 == 0) 
							sprintf (ordre + strlen(ordre), "0 0 08 %d 0 0 13 %d ggy 0 %d 22 3 0 %d 21 0 ", (int)moi->x + ((int)moi->y)*max_x, (int)moi->x + ((int)moi->y)*max_x, moi->id, moi->id);
						else
							sprintf (ordre + strlen(ordre), "0 0 08 %d 0 0 13 %d dus 0 %d 22 3 0 %d 21 0 ", (int)moi->x + ((int)moi->y)*max_x, (int)moi->x + ((int)moi->y)*max_x, moi->id, moi->id);
					}
					if (t == img->t->coa)
					{
						if (rand() % 2 == 0) 
							sprintf (ordre + strlen(ordre), "0 0 08 %d 0 0 13 %d dus 0 %d 22 3 0 %d 21 0 ", (int)moi->x + ((int)moi->y)*max_x, (int)moi->x + ((int)moi->y)*max_x, moi->id, moi->id);
						else
							sprintf (ordre + strlen(ordre), "0 0 08 %d 0 0 13 %d gco 0 %d 22 3 0 %d 21 0 ", (int)moi->x + ((int)moi->y)*max_x, (int)moi->x + ((int)moi->y)*max_x, moi->id, moi->id);
					}
					if (t == img->t->sal)
					{
						if (rand() % 2 == 0)
							sprintf (ordre + strlen(ordre), "0 0 08 %d 0 0 13 %d dus 0 %d 22 3 0 %d 21 0 ", (int)moi->x + ((int)moi->y)*max_x, (int)moi->x + ((int)moi->y)*max_x, moi->id, moi->id);
						else
							sprintf (ordre + strlen(ordre), "0 0 08 %d 0 0 13 %d gst 0 %d 22 3 0 %d 21 0 ", (int)moi->x + ((int)moi->y)*max_x, (int)moi->x + ((int)moi->y)*max_x, moi->id, moi->id);
					}
					// the wedge is single-use: once it actually broke a rock, unequip it (slot back to ".")
					if (strcmp(moi->items[tool_hand], "wooden-wedge") == 0 && (t == img->t->lim || t == img->t->qua || t == img->t->quz || t == img->t->bas || t == img->t->gra
						|| t == img->t->san || t == img->t->sha || t == img->t->mar || t == img->t->gyp || t == img->t->coa || t == img->t->sal))
						sprintf (ordre + strlen(ordre), "0 %d %d . ", moi->id, tool_hand == 12 ? 24 : 25);
				}
				
			}
		}
	}
}