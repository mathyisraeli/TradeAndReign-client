#include "linked_display.h"
#include "perso.h"

// The z-sort key at (x,y): a personnage's own altitude if this node is one,
// otherwise the ground's altitude under it — looked up live rather than
// cached on the node, so it can't go stale (see the comment on `height` in
// linked_display.h for why that matters).
static int to_disp_altitude(struct to_disp *node)
{
    if (node->p != NULL)
        return node->p->altitude;
    return ground_altitude[((int)node->y - start_y) * (end_x - start_x) + (int)node->x - start_x];
}

void sortedInsert(struct to_disp* new_node)
{
    struct to_disp* current;
    int new_alt = to_disp_altitude(new_node);
    /* Special case for the head end */
    if (list_disp == NULL || (int)list_disp->y > (int)new_node->y || (list_disp->x > new_node->x && (int)list_disp->y == (int)new_node->y) || ((int)list_disp->x == (int)new_node->x && (int)list_disp->y == (int)new_node->y && to_disp_altitude(list_disp) > new_alt)) {
        new_node->next = list_disp;
        list_disp = new_node;
    }
    else {
        /* Locate the node before the
 point of insertion */
        current = list_disp;
        while (current->next != NULL && ((int)new_node->y > (int)current->next->y || (new_node->x > current->next->x && (int)new_node->y == (int)current->next->y) || ((int)current->next->x == (int)new_node->x && (int)current->next->y == (int)new_node->y && to_disp_altitude(current->next) < new_alt))) {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
}

struct to_disp* deleteKey_char(int id)
{
    if (!list_disp)
        return list_disp;
    // Until the head data is equal to the key move the head
    // pointer. Building ids and personnage ids are independent namespaces
    // server-side, so they can collide — the type check (b == NULL) is
    // required here too, or a building sharing this id gets wrongly dropped.
    while (list_disp && list_disp->id == id && list_disp->b == NULL)
        list_disp = list_disp->next;
    struct to_disp *curr = list_disp, *prev = NULL;
    while (curr) {
        if (curr->id == id && curr->b == NULL)
            prev->next = curr->next;
        else
            prev = curr;
        curr = curr->next;
    }
    return list_disp;
}

struct to_disp* deleteKey_build(int id)
{
    if (!list_disp)
        return list_disp;
    // Until the head data is equal to the key move the head
    // pointer. Building ids and personnage ids are independent namespaces
    // server-side, so they can collide — the type check (p == NULL) is
    // required here too, or a personnage sharing this id gets wrongly dropped.
    while (list_disp && list_disp->id == id && list_disp->p == NULL)
        list_disp = list_disp->next;
    struct to_disp *curr = list_disp, *prev = NULL;
    while (curr) {
        if (curr->id == id && curr->p == NULL)
            prev->next = curr->next;
        else
            prev = curr;
        curr = curr->next;
    }
    return list_disp;
}
