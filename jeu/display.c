#include "display.h"
#include "shared_var.h"
#include "gui/gui.h"
//#include "SDL2/SDL2_gfxPrimitives.h"

/*void bubble_sort_perso()
{
	for (struct linked_list *par = list; par != NULL; par = par->next)
	{
		for (struct linked_list *par2 = list; par2->next != NULL; par2 = par2->next)
		{
			if ((int)par2->p->y > (int)par2->next->p->y || ((int)par2->p->y == (int)par2->next->p->y && par2->p->x > par2->next->p->x))
			{
				struct personnages *tmp = par2->p;
				par2->p = par2->next->p;
				par2->next->p = tmp;
			}
		}
	}
}*/


void display_ground(void)
{
    SDL_Rect position;
    if (moi->inside != -1)
    {
        for (struct to_disp *parcour = list_disp;parcour != NULL; parcour=parcour->next)
        {
            if (parcour->p && parcour->p->inside == moi->inside && ((int)parcour->x - moi->x) * ((int)parcour->x - moi->x) + ((int)parcour->y - moi->y) * ((int)parcour->y - moi->y) <= 441)
            {
                SDL_QueryTexture(parcour->img, NULL, NULL,&position.w, &position.h);
                position.x = (parcour->x - moi->x - parcour->y + moi->y) * 34 + parcour->offset_x - position.w / 2;
                position.y = (parcour->x - moi->x + parcour->y - moi->y) * 17 + parcour->offset_y - position.h - parcour->p->altitude + moi->altitude;
                parcour->p->screenx = position.x;
                parcour->p->screeny = position.y;
                parcour->p->sizescreenx = position.w;
                parcour->p->sizescreeny = position.h;
                SDL_RenderCopy(renderer, parcour->img, NULL, &position);
            }
            else if (parcour->b && parcour->b->id == moi->inside && parcour->x - (int)moi->x * parcour->x -(int) moi->x + parcour->y - (int)moi->y * parcour->y - (int)moi->y <= 441)
            {
                SDL_QueryTexture(parcour->img, NULL, NULL,&position.w, &position.h);
                position.x = (parcour->x - moi->x - parcour->y + moi->y) * 34 + parcour->offset_x - position.w / 2;
                position.y = (parcour->x - moi->x + parcour->y - moi->y) * 17 + parcour->offset_y - position.h - ground_altitude[((int)parcour->y - start_y) * (end_x - start_x) + (int)parcour->x - start_x] + moi->altitude;
                SDL_RenderCopy(renderer, parcour->img, NULL, &position);
            }
        }
    }
    else
    {
            /* --- Fenêtre de rendu --- */
        struct to_disp *parcour = list_disp;

        /* Avance jusqu’au premier objet visible */
            while (parcour && (((int)parcour->x - moi->x) * ((int)parcour->x - moi->x) + ((int)parcour->y - moi->y) * ((int)parcour->y - moi->y) > 441))
                parcour = parcour->next;

        int ii = 0;
        //printf ("%d %d %d %d\n", start_y, end_y, start_x, end_x);

        for (int y = start_y; y < end_y; y++)
        {
            for (int x = start_x; x < end_x; x++)
            {
                float dx = x - moi->x;
                float dy = y - moi->y;

                if (dx*dx + dy*dy > 441)
                {
                    ii++;
                    continue;
                }

                position.x = (dx - dy) * 34 + 866;
                position.y = (dx + dy) * 17 + 450 - ground_altitude[ii] + moi->altitude;
                position.w = 68;
                position.h = 34;

                SDL_RenderCopy(renderer, ground_texture[ii], NULL, &position);

                position.y += 17;
                position.h = 89;
                SDL_RenderCopy(renderer, img->t->w1, NULL, &position);

                /* --- Objets / personnages --- */
                while (parcour && (int)parcour->x == x && (int)parcour->y == y)
                {
                    int watter =  38*(ground_texture[ii]==img->t->wat);
                    if (parcour->p && parcour->p->inside == -1)
                    {
                        SDL_QueryTexture(parcour->img, NULL, NULL,&position.w, &position.h);
                        position.x = (parcour->x - moi->x - parcour->y + moi->y) * 34 + parcour->offset_x - position.w / 2;
                        position.y = (parcour->x - moi->x + parcour->y - moi->y) * 17 + parcour->offset_y - position.h - parcour->p->altitude + moi->altitude + watter;
                        parcour->p->screenx = position.x;
                        parcour->p->screeny = position.y;
                        parcour->p->sizescreenx = position.w;
                        parcour->p->sizescreeny = position.h;
                        SDL_RenderCopy(renderer, parcour->img, NULL, &position);
                    }
                    else if (parcour->b)
                    {
                        SDL_QueryTexture(parcour->img, NULL, NULL,&position.w, &position.h);
                        position.x = (parcour->x - moi->x - parcour->y + moi->y) * 34 + parcour->offset_x - position.w / 2;
                        position.y = (parcour->x - moi->x + parcour->y - moi->y) * 17 + parcour->offset_y - position.h - ground_altitude[ii]  + moi->altitude + watter;
                        SDL_RenderCopy(renderer, parcour->img, NULL, &position);
                    }


                    parcour = parcour->next;
                    while (parcour && (((int)parcour->x - moi->x) * ((int)parcour->x - moi->x) + ((int)parcour->y - moi->y) * ((int)parcour->y - moi->y) > 441))
                        parcour = parcour->next;
                }

                ii++;
            }
        }
    }
}