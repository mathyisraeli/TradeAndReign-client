#include "ordre.h"
#include "picking.h"

void select_char(struct linked_list *selected[11])
{
	if (lettres->Mouse_Lclick == 1 &&  lettres->Mouse_Rclick == 0)
	{
		PickResult pick = pick_at(lettres->Mouse_pos_x, lettres->Mouse_pos_y);
		if (!pick.is_cell && pick.subtype == PICK_PERSO)
		{
			struct personnages *clicked = find_perso_by_id(pick.id);
			if (clicked != NULL)
			{
				printf ("%d %s\n", clicked->id, clicked->nom);
				if (exist_in_linked(selected[0], clicked) == 0)
					selected[0] = append_in_linked(selected[0], clicked);
				else
					selected[0] = remove_from_linked_list(selected[0], clicked);
			}
		}
	}
	else if(lettres->Mouse_Mclick == 1)
	{
		free_linked(selected[0], 0);
		selected[0] = NULL;
	}	
	if(lettres->keystates[SDL_SCANCODE_LSHIFT])
	{
		if(lettres->keystates[SDL_SCANCODE_1])
		{
			free_linked(selected[1], 0);
			selected[1] = copy_linked(selected[0]);
		}	
		if(lettres->keystates[SDL_SCANCODE_2])
		{
			free_linked(selected[2], 0);
			selected[2] = copy_linked(selected[0]);
		}
		if(lettres->keystates[SDL_SCANCODE_3])
		{
			free_linked(selected[3], 0);
			selected[3] = copy_linked(selected[0]);

		}
		if(lettres->keystates[SDL_SCANCODE_4])
		{
			free_linked(selected[4], 0);
			selected[4] = copy_linked(selected[0]);
		}
		if(lettres->keystates[SDL_SCANCODE_5])
		{
			free_linked(selected[5], 0);
			selected[5] = copy_linked(selected[0]);
		}
		if(lettres->keystates[SDL_SCANCODE_6])
		{
			free_linked(selected[6], 0);
			selected[6] = copy_linked(selected[0]);
		}
		if(lettres->keystates[SDL_SCANCODE_7])
		{
			free_linked(selected[7], 0);
			selected[7] = copy_linked(selected[0]);
		}
		if(lettres->keystates[SDL_SCANCODE_8])
		{
			free_linked(selected[8], 0);
			selected[8] = copy_linked(selected[0]);
		}
		if(lettres->keystates[SDL_SCANCODE_9])
		{
			free_linked(selected[9], 0);
			selected[9] = copy_linked(selected[0]);
		}
		if(lettres->keystates[SDL_SCANCODE_0])
		{
			free_linked(selected[10], 0);
			selected[10] = copy_linked(selected[0]);
		}
	}
	else
	{
		if(lettres->keystates[SDL_SCANCODE_1])
		{
			free_linked(selected[0], 0);
			selected[0] = copy_linked(selected[1]);
		}	
		if(lettres->keystates[SDL_SCANCODE_2])
		{
			free_linked(selected[0], 0);
			selected[0] = copy_linked(selected[2]);
		}
		if(lettres->keystates[	SDL_SCANCODE_3])
		{
			free_linked(selected[0], 0);
			selected[0] = copy_linked(selected[3]);
		}
		if(lettres->keystates[SDL_SCANCODE_4])
		{
			free_linked(selected[0], 0);
			selected[0] = copy_linked(selected[4]);
		}
		if(lettres->keystates[SDL_SCANCODE_5])
		{
			free_linked(selected[0], 0);
			selected[0] = copy_linked(selected[5]);
		}
		if(lettres->keystates[SDL_SCANCODE_6])
		{
			free_linked(selected[0], 0);
			selected[0] = copy_linked(selected[6]);
		}
		if(lettres->keystates[SDL_SCANCODE_7])
		{
			free_linked(selected[0], 0);
			selected[0] = copy_linked(selected[7]);
		}
		if(lettres->keystates[SDL_SCANCODE_8])
		{
			free_linked(selected[0], 0);
			selected[0] = copy_linked(selected[8]);
		}
		if(lettres->keystates[SDL_SCANCODE_9])
		{
			free_linked(selected[0], 0);
			selected[0] = copy_linked(selected[9]);
		}
		if(lettres->keystates[SDL_SCANCODE_0])
		{
			free_linked(selected[0], 0);
			selected[0] = copy_linked(selected[10]);
		}
	}
}

void commande(struct linked_list *selected)
{
	menu_cond->angle = lettres->wheel;
	if (selected != NULL)
	{
		//SDL_Rect position;
		//position.w = 20;
		//position.h = 20;
		PickResult pick = pick_at(lettres->Mouse_pos_x, lettres->Mouse_pos_y);
		float x, y;float alt; 
		if (pick.is_cell)
		{
			// Plain ground: invert the isometric projection against that
			// specific cell's own altitude, giving an exact continuous
			// position within it that follows the mouse.
			alt = ground_altitude[(pick.cell_index / max_x - start_y) * (end_x - start_x) + pick.cell_index % max_x - start_x];
			x = moi->x + (((float)lettres->Mouse_pos_x - 900.0f) + 2.0f * ((float)lettres->Mouse_pos_y - 450.0f - moi->altitude + alt)) / 68.0f;
			y  = moi->y + (2.0f * ((float)lettres->Mouse_pos_y - 450.0f - moi->altitude + alt) - ((float)lettres->Mouse_pos_x - 900.0f)) / 68.0f;
		}
		else if (pick.subtype == PICK_PERSO)
		{
			// A personnage's own position is already exact and continuous —
			// no need to invert anything, just head straight for them.
			struct personnages *p = find_perso_by_id(pick.id);
			x = p != NULL ? p->x : -1;
			y = p != NULL ? p->y : 0;
			alt = p != NULL ? p->altitude : 0;
		}
		else if (pick.subtype == PICK_BUILDING)
		{
			// Same inversion as the plain-ground case above, just against
			// this piece's own real altitude (ground + its height, see
			// picking.h) instead of ground_altitude[] directly — gives the
			// same continuous, mouse-following precision on a roof/floor as
			// on flat ground, instead of snapping to the piece's tile centre.
			alt = pick.piece_altitude_ground + pick.piece_height;
			x = moi->x + (((float)lettres->Mouse_pos_x - 900.0f) + 2.0f * ((float)lettres->Mouse_pos_y - 450.0f - moi->altitude + alt)) / 68.0f;
			y  = moi->y + (2.0f * ((float)lettres->Mouse_pos_y - 450.0f - moi->altitude + alt) - ((float)lettres->Mouse_pos_x - 900.0f)) / 68.0f;
		}
		else
		{
			x = -1; // nothing under the cursor (e.g. off the visible map)
			y = 0;
			alt = 0;
		}
		//position.x = (x - moi->x - y + moi->y) * 34 + 890;
		//position.y = (x - moi->x - moi->y  + y) * 17 + 440 - alt + moi->altitude;
		//SDL_RenderCopy(renderer, img->g->croix_inverse, NULL, &position);

		if (lettres->Mouse_Lclick == 0 &&  lettres->Mouse_Rclick == 1)
		{
			printf ("qsfdqf x=%f y=%f alt=%f | moi->x=%f moi->y=%f moi->altitude=%d | mouse=%d,%d | pick.is_cell=%d subtype=%d piece_x=%f piece_y=%f piece_alt_ground=%d piece_height=%d\n",
				x, y, alt, moi->x, moi->y, moi->altitude, lettres->Mouse_pos_x, lettres->Mouse_pos_y,
				pick.is_cell, pick.subtype, pick.piece_x, pick.piece_y, pick.piece_altitude_ground, pick.piece_height);
			for (struct linked_list *a = selected; a != NULL; a = a->next)
				sprintf (ordre + strlen(ordre), "0 %d 03 %f 0 %d 04 %f 0 %d 33 %f ", a->p->id, x, a->p->id, y, a->p->id, alt);
		}
	}
}
		

		



