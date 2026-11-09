#include "building.h"


int parse_building(struct building *b, char *line)
{
    int i;
    sscanf(line, "%s %d %d %d %d %c %c %n", b->skin, &b->id, &b->pv, &b->x, &b->y, &b->angle, &b->state, &i);
    return i;
}

int append_building(char *line)
{
    struct building *new = malloc(sizeof(struct building));
    int ret = parse_building(new, line);
    actualise_stat_building(new);
    actualise_building_altitude(new);
    new->next = NULL;
    if (list_building == NULL || list_building->id > new->id)
    {
        new->next = list_building;
        list_building = new;
    }
    else
    {
        struct building *parcour = list_building;
        while (parcour->next != NULL && new->id > parcour->next->id)
            parcour = parcour->next;
        new->next = parcour->next;
        parcour->next = new;
    }
    return ret;
}

struct building *find_building_by_id(int id)
{
	struct building *parcour = list_building;
	while (parcour != NULL)
	{
		if (parcour->id == id)
		{
			return parcour;
		}
		parcour = parcour->next;
	}
	return NULL;
}

struct building *destruction(void)
{
	struct building *tmp = list_building;
	struct building *prev;
	while (tmp != NULL && tmp->pv <= 0)
	{
        printf ("destruction\n");
        list_disp = deleteKey_build(tmp->id);
		list_building = list_building->next;
		remove_building_altitude(tmp);
		free(tmp);
		tmp = list_building;

	}
	while (tmp != NULL)
	{
		while (tmp != NULL && tmp->pv > 0)
		{
			prev = tmp;
			tmp = tmp->next;
		}
		if (tmp == NULL)
			return list_building;
        printf ("destruction\n");
        list_disp = deleteKey_build(tmp->id);
		prev->next = tmp->next;
		remove_building_altitude(tmp);
        free(tmp);
		tmp = prev->next;
	}
	return list_building;
}

void remove_building_altitude(struct building *parcour)
{
    if (strcmp(parcour->skin, "111") == 0)
    {   
        building_id[(int)(parcour->y) * max_x + (int)(parcour->x)] =  -1;
        building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x)] = -1;
        building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x)] = -1;
        building_id[(int)(parcour->y) * max_x + (int)(parcour->x-2)] = -1;
        building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x-2)] = -1;
        building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x-2)] = -1;
        building_id[(int)(parcour->y) * max_x + (int)(parcour->x)-1] = -1;
        building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x)-1] = -1;
        building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x)-1] = -1;
    }
    else if (strcmp(parcour->skin, "125") == 0)
    {
        building_id[(int)(parcour->y) * max_x + (int)(parcour->x)] =  -1;
        building_id[(int)(parcour->y) * max_x + (int)(parcour->x+1)] = -1;
        building_id[(int)(parcour->y) * max_x + (int)(parcour->x+2)] = -1;
        building_id[(int)(parcour->y) * max_x + (int)(parcour->x+3)] = -1;
        building_id[(int)(parcour->y) * max_x + (int)(parcour->x+4)] = -1;
    }
    else if (strcmp(parcour->skin, "131")  == 0)
    {
        if (parcour->angle == 'd')
        {
            building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x+1)] = -1;
            building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x+1)] = -1;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x+1)] = -1;
            building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x+1)] = -1;
            building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x+1)] = -1;
            building_id[(int)(parcour->y-3) * max_x + (int)(parcour->x+1)] = -1;
            building_id[(int)(parcour->y+3) * max_x + (int)(parcour->x)] = -1;
            building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x)] = -1;
            building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x)] = -1;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x)] = -1;
            building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x)] = -1;
            building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x)] = -1;
            building_id[(int)(parcour->y-3) * max_x + (int)(parcour->x)] = -1;
            building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x-1)] = -1;
            building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x-1)] = -1;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x-1)] = -1;
            building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x-1)] = -1;
            building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x-1)] = -1;
            building_id[(int)(parcour->y-3) * max_x + (int)(parcour->x-1)] = -1;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x+2)] = -1;
            building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x+2)] = -1;
            building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x+2)] = -1;
            building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x+2)] = -1;
            building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x+2)] = -1;
            building_id[(int)(parcour->y-3) * max_x + (int)(parcour->x+2)] = -1;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x-2)] = -1;
            building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x-2)] = -1;
            building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x-2)] = -1;
            building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x-2)] = -1;
            building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x-2)] = -1;
            building_id[(int)(parcour->y-3) * max_x + (int)(parcour->x-2)] = -1;
            building_id[(int)(parcour->y-4) * max_x + (int)(parcour->x+1)] = -1;
            building_id[(int)(parcour->y-4) * max_x + (int)(parcour->x)] = -1;
            building_id[(int)(parcour->y-4) * max_x + (int)(parcour->x-1)] = -1;
            building_id[(int)(parcour->y+3) * max_x + (int)(parcour->x+1)] = -1;
            building_id[(int)(parcour->y+4) * max_x + (int)(parcour->x)] = -1;
            building_id[(int)(parcour->y+3) * max_x + (int)(parcour->x-1)] = -1;
        }
        else if (parcour->angle=='h')
        {
            building_id[(int)(parcour->y+3) * max_x + (int)(parcour->x+2)] = -1;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x+2)] = -1;
            building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x+2)] = -1;
            building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x+2)] = -1;
            building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x+2)] = -1;
            building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x+2)] = -1;
            building_id[(int)(parcour->y+3) * max_x + (int)(parcour->x-2)] = -1;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x-2)] = -1;
            building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x-2)] = -1;
            building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x-2)] = -1;
            building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x-2)] = -1;
            building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x-2)] = -1;
            building_id[(int)(parcour->y+4) * max_x + (int)(parcour->x+1)] = -1;
            building_id[(int)(parcour->y+4) * max_x + (int)(parcour->x)] = -1;
            building_id[(int)(parcour->y+4) * max_x + (int)(parcour->x-1)] = -1;
            building_id[(int)(parcour->y+3) * max_x + (int)(parcour->x-1)] = -1;
            building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x-1)] = -1;
            building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x-1)] = -1;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x-1)] = -1;
            building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x-1)] = -1;
            building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x-1)] = -1;
            building_id[(int)(parcour->y+3) * max_x + (int)(parcour->x)] = -1;
            building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x)] = -1;
            building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x)] = -1;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x)] = -1;
            building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x)] = -1;
            building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x)] = -1;
            building_id[(int)(parcour->y-3) * max_x + (int)(parcour->x)] = -1;
            building_id[(int)(parcour->y+3) * max_x + (int)(parcour->x+1)] = -1;
            building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x+1)] = -1;
            building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x+1)] = -1;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x+1)] = -1;
            building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x+1)] = -1;
            building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x+1)] = -1;
            building_id[(int)(parcour->y-3) * max_x + (int)(parcour->x+1)] = -1;
            building_id[(int)(parcour->y-3) * max_x + (int)(parcour->x-1)] = -1;
            building_id[(int)(parcour->y-4) * max_x + (int)(parcour->x)] = -1;  
        }
        else if (parcour->angle == 'f') // k
        {
            building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x-2)] = -1;
            building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x-1)] = -1;
            building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x)] = -1;
            building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x+1)] = -1;
            building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x+2)] = -1;
            building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x+3)] = -1;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x-3)] = -1;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x-2)] = -1;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x-1)] = -1;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x)] = -1;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x+1)] = -1;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x+2)] = -1;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x+3)] = -1;
            building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x-2)] = -1;
            building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x-1)] = -1;
            building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x)] = -1;
            building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x+1)] = -1;
            building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x+2)] = -1;
            building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x+3)] = -1;
            building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x-3)] = -1;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x-4)] = -1;
            building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x-3)] = -1;
            building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x+4)] = -1;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x+4)] = -1;
            building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x+4)] = -1;
            building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x+3)] = -1;
            building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x+2)] = -1;
            building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x+1)] = -1;
            building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x)] = -1;
            building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x-1)] = -1;
            building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x-2)] = -1;
            building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x+3)] = -1;
            building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x+2)] = -1;
            building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x+1)] = -1;
            building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x)] = -1;
            building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x-1)] = -1;
            building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x-2)] = -1;

        }
        else if (parcour->angle == 'b') // e
        {
            building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x-3)] = -1;
            building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x-2)] = -1;
            building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x-1)] = -1;
            building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x)] = -1;
            building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x+1)] = -1;
            building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x+2)] = -1;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x-3)] = -1;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x-2)] = -1;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x-1)] = -1;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x)] = -1;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x+1)] = -1;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x+2)] = -1;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x+3)] = -1;
            building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x-3)] = -1;
            building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x-2)] = -1;
            building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x-1)] = -1;
            building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x)] = -1;
            building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x+1)] = -1;
            building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x+2)] = -1;
            building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x+3)] = -1;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x+4)] = -1;
            building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x+3)] = -1;
            building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x-4)] = -1;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x-4)] = -1;
            building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x-4)] = -1;
            building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x+2)] = -1;
            building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x+1)] = -1;
            building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x)] = -1;
            building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x-1)] = -1;
            building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x-2)] = -1;
            building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x-3)] = -1;
            building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x+2)] = -1;
            building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x+1)] = -1;
            building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x)] = -1;
            building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x-1)] = -1;
            building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x-2)] = -1;
            building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x-3)] = -1;
        }
    }
}

void actualise_building_altitude(struct building *parcour)
{    
    
    if (strcmp(parcour->skin, "111") == 0)
    {   
        building_id[(int)(parcour->y) * max_x + (int)(parcour->x)] =  parcour->id;
        building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x)] = parcour->id;
        building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x)] = parcour->id;
        building_id[(int)(parcour->y) * max_x + (int)(parcour->x-2)] = parcour->id;
        building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x-2)] = parcour->id;
        building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x-2)] = parcour->id;
        building_id[(int)(parcour->y) * max_x + (int)(parcour->x)-1] = parcour->id;
        building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x)-1] = parcour->id;
        building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x)-1] = parcour->id;
    }

    else if (strcmp(parcour->skin, "125") == 0)
    {
        building_id[(int)(parcour->y) * max_x + (int)(parcour->x)] =  parcour->id;
        building_id[(int)(parcour->y) * max_x + (int)(parcour->x+1)] = parcour->id;
        building_id[(int)(parcour->y) * max_x + (int)(parcour->x+2)] = parcour->id;
        building_id[(int)(parcour->y) * max_x + (int)(parcour->x+3)] = parcour->id;
        building_id[(int)(parcour->y) * max_x + (int)(parcour->x+4)] = parcour->id;
    }
    else if (strcmp(parcour->skin, "131")  == 0)
    {
        if (parcour->angle == 'd')
        {
            building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x+1)] = parcour->id;
            building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x+1)] = parcour->id;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x+1)] = parcour->id;
            building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x+1)] = parcour->id;
            building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x+1)] = parcour->id;
            building_id[(int)(parcour->y-3) * max_x + (int)(parcour->x+1)] = parcour->id;
            building_id[(int)(parcour->y+3) * max_x + (int)(parcour->x)] = parcour->id;
            building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x)] = parcour->id;
            building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x)] = parcour->id;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x)] = parcour->id;
            building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x)] = parcour->id;
            building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x)] = parcour->id;
            building_id[(int)(parcour->y-3) * max_x + (int)(parcour->x)] = parcour->id;
            building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x-1)] = parcour->id;
            building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x-1)] = parcour->id;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x-1)] = parcour->id;
            building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x-1)] = parcour->id;
            building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x-1)] = parcour->id;
            building_id[(int)(parcour->y-3) * max_x + (int)(parcour->x-1)] = parcour->id;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x+2)] = parcour->id;
            building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x+2)] = parcour->id;
            building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x+2)] = parcour->id;
            building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x+2)] = parcour->id;
            building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x+2)] = parcour->id;
            building_id[(int)(parcour->y-3) * max_x + (int)(parcour->x+2)] = parcour->id;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x-2)] = parcour->id;
            building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x-2)] = parcour->id;
            building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x-2)] = parcour->id;
            building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x-2)] = parcour->id;
            building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x-2)] = parcour->id;
            building_id[(int)(parcour->y-3) * max_x + (int)(parcour->x-2)] = parcour->id;
            building_id[(int)(parcour->y-4) * max_x + (int)(parcour->x+1)] = parcour->id;
            building_id[(int)(parcour->y-4) * max_x + (int)(parcour->x)] = parcour->id;
            building_id[(int)(parcour->y-4) * max_x + (int)(parcour->x-1)] = parcour->id;
            building_id[(int)(parcour->y+3) * max_x + (int)(parcour->x+1)] = parcour->id;
            building_id[(int)(parcour->y+4) * max_x + (int)(parcour->x)] = parcour->id;
            building_id[(int)(parcour->y+3) * max_x + (int)(parcour->x-1)] = parcour->id;
        }
        else if (parcour->angle=='h')
        {
            building_id[(int)(parcour->y+3) * max_x + (int)(parcour->x+2)] = parcour->id;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x+2)] = parcour->id;
            building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x+2)] = parcour->id;
            building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x+2)] = parcour->id;
            building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x+2)] = parcour->id;
            building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x+2)] = parcour->id;
            building_id[(int)(parcour->y+3) * max_x + (int)(parcour->x-2)] = parcour->id;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x-2)] = parcour->id;
            building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x-2)] = parcour->id;
            building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x-2)] = parcour->id;
            building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x-2)] = parcour->id;
            building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x-2)] = parcour->id;
            building_id[(int)(parcour->y+4) * max_x + (int)(parcour->x+1)] = parcour->id;
            building_id[(int)(parcour->y+4) * max_x + (int)(parcour->x)] = parcour->id;
            building_id[(int)(parcour->y+4) * max_x + (int)(parcour->x-1)] = parcour->id;
            building_id[(int)(parcour->y+3) * max_x + (int)(parcour->x-1)] = parcour->id;
            building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x-1)] = parcour->id;
            building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x-1)] = parcour->id;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x-1)] = parcour->id;
            building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x-1)] = parcour->id;
            building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x-1)] = parcour->id;
            building_id[(int)(parcour->y+3) * max_x + (int)(parcour->x)] = parcour->id;
            building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x)] = parcour->id;
            building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x)] = parcour->id;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x)] = parcour->id;
            building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x)] = parcour->id;
            building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x)] = parcour->id;
            building_id[(int)(parcour->y-3) * max_x + (int)(parcour->x)] = parcour->id;
            building_id[(int)(parcour->y+3) * max_x + (int)(parcour->x+1)] = parcour->id;
            building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x+1)] = parcour->id;
            building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x+1)] = parcour->id;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x+1)] = parcour->id;
            building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x+1)] = parcour->id;
            building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x+1)] = parcour->id;
            building_id[(int)(parcour->y-3) * max_x + (int)(parcour->x+1)] = parcour->id;
            building_id[(int)(parcour->y-3) * max_x + (int)(parcour->x-1)] = parcour->id;
            building_id[(int)(parcour->y-4) * max_x + (int)(parcour->x)] = parcour->id;  
        }
        else if (parcour->angle == 'f') // k
        {
            building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x-2)] = parcour->id;
            building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x-1)] = parcour->id;
            building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x)] = parcour->id;
            building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x+1)] = parcour->id;
            building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x+2)] = parcour->id;
            building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x+3)] = parcour->id;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x-3)] = parcour->id;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x-2)] = parcour->id;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x-1)] = parcour->id;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x)] = parcour->id;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x+1)] = parcour->id;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x+2)] = parcour->id;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x+3)] = parcour->id;
            building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x-2)] = parcour->id;
            building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x-1)] = parcour->id;
            building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x)] = parcour->id;
            building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x+1)] = parcour->id;
            building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x+2)] = parcour->id;
            building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x+3)] = parcour->id;
            building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x-3)] = parcour->id;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x-4)] = parcour->id;
            building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x-3)] = parcour->id;
            building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x+4)] = parcour->id;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x+4)] = parcour->id;
            building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x+4)] = parcour->id;
            building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x+3)] = parcour->id;
            building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x+2)] = parcour->id;
            building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x+1)] = parcour->id;
            building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x)] = parcour->id;
            building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x-1)] = parcour->id;
            building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x-2)] = parcour->id;
            building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x+3)] = parcour->id;
            building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x+2)] = parcour->id;
            building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x+1)] = parcour->id;
            building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x)] = parcour->id;
            building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x-1)] = parcour->id;
            building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x-2)] = parcour->id;

        }
        else if (parcour->angle == 'b') 
        {
            building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x-3)] = parcour->id;
            building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x-2)] = parcour->id;
            building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x-1)] = parcour->id;
            building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x)] = parcour->id;
            building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x+1)] = parcour->id;
            building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x+2)] = parcour->id;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x-3)] = parcour->id;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x-2)] = parcour->id;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x-1)] = parcour->id;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x)] = parcour->id;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x+1)] = parcour->id;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x+2)] = parcour->id;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x+3)] = parcour->id;
            building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x-3)] = parcour->id;
            building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x-2)] = parcour->id;
            building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x-1)] = parcour->id;
            building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x)] = parcour->id;
            building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x+1)] = parcour->id;
            building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x+2)] = parcour->id;
            building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x+3)] = parcour->id;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x+4)] = parcour->id;
            building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x+3)] = parcour->id;
            building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x-4)] = parcour->id;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x-4)] = parcour->id;
            building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x-4)] = parcour->id;
            building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x+2)] = parcour->id;
            building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x+1)] = parcour->id;
            building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x)] = parcour->id;
            building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x-1)] = parcour->id;
            building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x-2)] = parcour->id;
            building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x-3)] = parcour->id;
            building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x+2)] = parcour->id;
            building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x+1)] = parcour->id;
            building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x)] = parcour->id;
            building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x-1)] = parcour->id;
            building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x-2)] = parcour->id;
            building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x-3)] = parcour->id;
        }
    }
    else if (strcmp(parcour->skin, "141") == 0)
        building_id[(int)(parcour->y) * max_x + (int)(parcour->x)] = parcour->id;

}