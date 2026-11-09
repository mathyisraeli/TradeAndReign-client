#include "parseur.h"

struct personnages *get_ptr_from_id(int id)
{
	struct linked_list *parcour = list;
	while (parcour != NULL)
	{
		if (parcour->p->id == id)
			return parcour->p;
		parcour = parcour->next;
	}
	return NULL;
}

struct building *get_building_from_id(int id)
{
	struct building *parcour = list_building;
	while (parcour != NULL)
	{
		if (parcour->id == id)
			return parcour;
		parcour = parcour->next;
	}
	return NULL;
}

int parse_order(struct personnages *p, char *line)
{
    //printf ("-{%s}\n", line);

    int i;
    int j;
    char tmpI[10];
    char tmpN[50];
    p->e_list = NULL;

    // vitesse_dep is no longer sent by the server — see the comment on
    // append_perso_to_order() in serv/net.c and on vitesse_dep in perso.h.
    sscanf(line, "%s %d %d %d %d %d %d %d %d %c %s %s %s %s %d %d %s %d %s %d %s %d %s %d %s %d %s %d %s %d %s %d %s %d %s %d %s %d %s %s %s %s %s %s %s %f %f %d %f %f %f %d %f %n",
    p->skin, &p->id, &p->pv, &p->nb_vassaux, &p->faim, &p->inside, &p->house_id, &p->animation, &p->animation_2, &p->angle, p->physique, p->nom_de_compte, p->nom,  p->nom_superieur, &p->echange_player,
    &p->items_cnt[0], p->items[0], &p->items_cnt[1], p->items[1], &p->items_cnt[2], p->items[2], &p->items_cnt[3], p->items[3], &p->items_cnt[4], p->items[4], &p->items_cnt[5], p->items[5],
    &p->items_cnt[6], p->items[6], &p->items_cnt[7], p->items[7], &p->items_cnt[8], p->items[8], &p->items_cnt[9], p->items[9], &p->items_cnt[10], p->items[10], &p->items_cnt[11], p->items[11],
    p->items[12], p->items[13],p->items[14], p->items[15],p->items[16], p->items[17], &p->x, &p->y, &p->altitude, &p->ordrex, &p->ordrey, &p->ordrea, &p->dom, &p->porte_dom, &i);
    while (line[i] != ']')
    {
        i += 1;
        if (line[i] != ']')
        {
            j = 0;
            while (line[i] != ' ')
            {
                tmpN[j] = line[i];
                i++;
                j++;
            }
            tmpN[j] = 0;
            i++;
            j = 0;
            while (line[i] != ' ' && line[i] != ']')
            {
                tmpI[j] = line[i];
                i++;
                j++;
            }
            tmpI[j] = 0;
            p->e_list = append_enemie(tmpN, p->e_list, atoi(tmpI));
        }
    }
    i+= 3;
    j = 0;
    while (line[i] != ']')
    {
        p->skill[j] = line[i];
        i += 1;
        j += 1;
    }
    i += 1;
    j = 0;
    while (line[i] != '\n' && line[i] != 0)
    {
        p->speak[j] = line[i];
        i += 1;
        j += 1;
    }
    p->speak[j] = 0;
    return i + 1;
                     
}
