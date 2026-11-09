#include "perso.h"
#include "shared_var.h"


int getSizeLinkedList(struct linked_list *list)
{
	int size = 0;
	for (struct linked_list *l = list; l != NULL; l = l->next)
		size++;
	return size;
}

struct linked_list *copy_linked(struct linked_list *list)
{
	if (list == NULL)
		return NULL;
	struct linked_list *head = malloc(sizeof(struct linked_list));
	struct linked_list *parcour = head;
	while (list != NULL)
	{
		parcour->p = list->p;
		if (list->next == NULL)
			parcour->next = NULL;
		else
		{
			parcour->next = malloc(sizeof(struct linked_list));
			parcour = parcour->next;
		}
		list = list->next;
	}
	return head;
}


void free_linked(struct linked_list *list, char free_content)
{
	if (list != NULL)
	{
		free_linked(list->next, free_content);
		if (free_content == 1)
		{
			
			free(list->p);
			//free_linked_char(list->p->e_list);
		}
		free(list);
	}
}

char exist_in_linked(struct linked_list *list, struct personnages *to_test)
{
	for (struct linked_list *l = list; l != NULL; l = l->next)
		if (l->p == to_test)
			return 1;
	return 0;
}

struct linked_list *append_in_linked(struct linked_list *list,struct personnages *p)
{
	struct linked_list *to_append = malloc(sizeof(struct linked_list));
	to_append->p = p;
	if (list == NULL || list->p->id > p->id)
	{
		to_append->next = list;
		list = to_append;
		return list;
	}
	else
	{
		struct linked_list *parcour = list;
		while (parcour->next != NULL && p->id > parcour->p->id)
			parcour = parcour->next;
		if (parcour->p != p)
		{
			to_append->next = parcour->next;
			parcour->next = to_append;
		}
		return list;
	}
}

int append_perso(char *line)
{
	if (line[0] == '\0')
		return 0;
	struct personnages *n = malloc(sizeof(struct personnages));
	int a = parse_order(n, line);
	init_stat(n);
	struct linked_list *to_append = malloc(sizeof(struct linked_list));
	to_append->p = n;
	to_append->next = NULL;
	if (list == NULL)
		list = to_append;	
	else
	{
		struct linked_list *parcour = list;
		while (parcour->next != NULL)
			parcour = parcour->next;
		parcour->next = to_append;
	}
	return a;
}

struct personnages *find_perso_by_id(int id)
{
	struct linked_list *parcour = list;
	while (parcour != NULL)
	{
		if (parcour->p->id == id)
		{
			return parcour->p;
		}
		parcour = parcour->next;
	}
	return NULL;
}


struct personnages *find_perso_by_name(char *name)
{
	struct linked_list *parcour = list;
	while (parcour != NULL)
	{
		if (strcmp(parcour->p->nom, name) == 0)
		{
			return parcour->p;
		}
		parcour = parcour->next;
	}
	return NULL;
}

struct linked_list *death(void)
{
	struct linked_list *tmp = list;
	struct linked_list *prev;
	// bug #43: this used to free any pv<=0 node unconditionally, including moi
	// itself (the locally-controlled character) - the global `moi` pointer was
	// never cleared or reassigned afterward, so every subsequent frame's
	// deplacement(moi) kept reading/writing through freed memory, sending a
	// garbage moi->id to the server (confirmed live via gdb: a connected
	// player's own hunger-driven death sent "0 -138392800 22 0 ..." to the
	// server, which indexed list.data[-138392800] and segfaulted). moi is
	// excluded here until there's an actual death/respawn flow for the player.
	while (tmp != NULL && tmp->p->pv <= 0 && tmp->p != moi)
	{
		printf ("%s just died\n", tmp->p->nom);
		list = list->next;
		free_linked_enemie(tmp->p->e_list);
		list_disp = deleteKey_char(tmp->p->id);
		free(tmp->p);
		free(tmp);
		tmp = list;
	}
	while (tmp != NULL)
	{
		while (tmp != NULL && (tmp->p->pv > 0 || tmp->p == moi))
		{
			prev = tmp;
			tmp = tmp->next;
		}
		if (tmp == NULL)
			return list;
		prev->next = tmp->next;
		printf ("%s just died\n", tmp->p->nom);
		free_linked_enemie(tmp->p->e_list);
		list_disp = deleteKey_char(tmp->p->id);
        free(tmp->p);
        free(tmp);
		tmp = prev->next;
	}
	return list;
}

struct linked_list *remove_from_linked_list(struct linked_list *list, struct personnages  *to_rem)
{
	struct linked_list *ret = list;
	struct linked_list *prev;
	if (list != NULL)
	{
		if (list->p == to_rem)
		{
			list = list->next;
			free(ret);
			return list;
		}
		while (list->next != NULL)
		{
			prev = list;
			list = list->next;
			if (list->p == to_rem)
			{
				prev->next = list->next;
				free(list);
				return ret;
			}
		}
		if (list->p == to_rem)
		{
			free(list);
			prev->next = NULL;
		}
	}
	return ret;
}

struct linked_list *clean_selected(struct linked_list *list)
{
	struct linked_list *ret = list;
	struct linked_list *prev;
	if (list != NULL)
	{
		if (list->p->pv <= 0 || list->p->id == -1)
		{
			list = list->next;
			free(ret);
		}
		if (list == NULL)
			return NULL;
		while (list->next != NULL)
		{
			prev = list;
			list = list->next;
			if (list->p->pv <= 0 || list->p->id == -1)
			{
				prev->next = list->next;
				free(list);
				list = prev;
			}
		}
		if (list->p->pv <= 0 || list->p->id == -1)
		{
			prev->next = NULL;
			free(list);
		}
	}
	return ret;
}
