#include "trade_menu.h"

//items10 is removed to perso1 and given to perso2
//items11 is removed to perso2 and given to perso1

void echange_item_net(struct personnages *perso1, struct personnages *perso2)
{
	//printf ("%s %s\n", perso1->nom, perso2->nom);
	//printf ("%s %s\n", perso1->item1, perso1->item2);
	if (strcmp(perso1->items[10], ".") == 0)
	{
		for (int i = 0; 10 > i; i++)
		{
			if (strcmp(perso2->items[i], perso1->items[11]) == 0 && perso2->items_cnt[i] >= perso1->items_cnt[11])
			{
				sprintf (ordre + strlen(ordre), "0 %d 16 +%d %s 0 %d 16 %d %s 0 ", 
				perso1->id, perso1->items_cnt[11], perso1->items[11],
				perso2->id, perso1->items_cnt[11], perso1->items[11]);
				return;
			}
		}
	}
	if (strcmp(perso1->items[11], ".") == 0)
	{
		for (int i = 0; 10 > i; i++)
		{
			if (strcmp(perso1->items[i], perso1->items[10]) == 0 && perso1->items_cnt[i] >= perso1->items_cnt[10])
			{
				sprintf (ordre + strlen(ordre), "0 %d 16 +%d %s 0 %d 16 %d %s 0 ", 
				perso2->id, perso1->items_cnt[10], perso1->items[10],
				perso1->id, perso1->items_cnt[10], perso1->items[10]);
				return;
			}
		}
	}
	else
	{
		char p1get=0; char p2get = 0;
        for (int i = 0; 10 > i; i++)
        {
			if (strcmp(perso2->items[i], perso1->items[11]) == 0 && perso2->items_cnt[i] >= perso1->items_cnt[11])
                p1get = 1;
            if (strcmp(perso1->items[i], perso1->items[10]) == 0 && perso1->items_cnt[i] >= perso1->items_cnt[10])
                p2get = 1;
        }
		if (p1get == 1 && p2get == 1)
		{
			sprintf (ordre + strlen(ordre), "0 %d 16 +%d %s 0 %d 16 +%d %s 0 %d 16 %d %s 0 %d 16 %d %s 0 ", 
			perso1->id, perso1->items_cnt[11], perso1->items[11], 
			perso2->id, perso1->items_cnt[10], perso1->items[10],
			perso2->id, perso1->items_cnt[11], perso1->items[11], 
			perso1->id, perso1->items_cnt[10], perso1->items[10]);
	    }
    }
	sprintf (ordre + strlen(ordre), "0 %d 17 none none 0 none 0 ", perso1->id);	
}


void menu_trade(void)
{
    struct personnages *chosen = NULL;
    float distance_chosen = 9;
    TextInfo echange_player = {NULL, littleFont, 600, 10, 0, (SDL_Color){0, 255, 0, 255}, 0, 0, 0};
    for (struct linked_list *l = list; l != NULL; l=l->next)
    {
        if (l->p != moi)
        {
            float s_distance = (l->p->x - moi->x)*(l->p->x - moi->x)+(l->p->y - moi->y)*(l->p->y - moi->y);
            if (s_distance < distance_chosen)
            {
                char is_enemie = 0;
                for (struct linked_enemie *ll = l->p->e_list; ll != NULL; ll=ll->next)
                    if (strcmp(ll->nom, moi->nom) == 0)
                        is_enemie = 1;
                if (is_enemie == 0)
                {
                    chosen = l->p;
                    distance_chosen = s_distance;
                }
            }
        }
    }
    if (chosen != NULL)
    {
        echange_player.text =  chosen->nom;
        drawTextInfo(renderer, &echange_player);
        for (int i = 0; 10 > i; i++)
        {
            if (moi->items_cnt[i] <= 0 || (moi->items[i][0] == '.' && moi->items[i][1] == '\0'))
                main_menu->menuInv->selector->options[i][0] = '\0';
            else
                sprintf(main_menu->menuInv->selector->options[i], "%s %d/%d", moi->items[i], min(main_menu->menuTrad->count1, moi->items_cnt[i]), moi->items_cnt[i]);
        }
        drawSelector(renderer, main_menu->menuInv->selector);
        for (int i = 0; 10 > i; i++)
        {
            if (chosen->items_cnt[i] <= 0 || (chosen->items[i][0] == '.' && chosen->items[i][1] == '\0'))
                main_menu->menuTrad->selector2->options[i][0] = '\0';
            else
                sprintf(main_menu->menuTrad->selector2->options[i], "%s %d/%d", chosen->items[i], min(main_menu->menuTrad->count2, chosen->items_cnt[i]), chosen->items_cnt[i]);
        }
        drawSelector(renderer, main_menu->menuTrad->selector2);
        if (lettres->keystates[SDL_SCANCODE_ESCAPE])
            main_menu->menuTrad->on = 0;
        if (main_menu->menuTrad->tab == -1)
        {
            if (lettres->keystates[SDL_SCANCODE_S] || lettres->keystates[SDL_SCANCODE_DOWN])
                main_menu->menuInv->selector->selectedOption = (main_menu->menuInv->selector->selectedOption + 1) % main_menu->menuInv->selector->numOptions;
            if (lettres->keystates[SDL_SCANCODE_Z] || lettres->keystates[SDL_SCANCODE_UP])
    	        main_menu->menuInv->selector->selectedOption = (main_menu->menuInv->selector->selectedOption - 1 + main_menu->menuInv->selector->numOptions) % main_menu->menuInv->selector->numOptions;
            if (lettres->keystates[SDL_SCANCODE_D] || lettres->keystates[SDL_SCANCODE_RIGHT])
                main_menu->menuTrad->count1 += 1;
            if (lettres->keystates[SDL_SCANCODE_Q] || lettres->keystates[SDL_SCANCODE_LEFT])
                main_menu->menuTrad->count1 -= 1;
        }
        else
        {
            if (lettres->keystates[SDL_SCANCODE_S] || lettres->keystates[SDL_SCANCODE_DOWN])
                main_menu->menuTrad->selector2->selectedOption = (main_menu->menuTrad->selector2->selectedOption + 1) % main_menu->menuTrad->selector2->numOptions;
            if (lettres->keystates[SDL_SCANCODE_Z] || lettres->keystates[SDL_SCANCODE_UP])
    	        main_menu->menuTrad->selector2->selectedOption = (main_menu->menuTrad->selector2->selectedOption - 1 + main_menu->menuTrad->selector2->numOptions) % main_menu->menuTrad->selector2->numOptions;
            if (lettres->keystates[SDL_SCANCODE_D] || lettres->keystates[SDL_SCANCODE_RIGHT])
                main_menu->menuTrad->count2 += 1;
            if (lettres->keystates[SDL_SCANCODE_Q] || lettres->keystates[SDL_SCANCODE_LEFT])
                main_menu->menuTrad->count2 -= 1;
        }
        if (lettres->keystates[SDL_SCANCODE_TAB])
            main_menu->menuTrad->tab *= -1;
        if (lettres->keystates[SDL_SCANCODE_RETURN])
        {    
            sprintf (ordre + strlen(ordre), "0 %d 17 %s %s %d %s %d ", 
            chosen->id, moi->nom, chosen->items[main_menu->menuTrad->selector2->selectedOption], min(chosen->items_cnt[main_menu->menuTrad->selector2->selectedOption], main_menu->menuTrad->count1), 
            moi->items[main_menu->menuInv->selector->selectedOption], min(moi->items_cnt[ main_menu->menuInv->selector->selectedOption], main_menu->menuTrad->count2));
        }
    }
    else
        main_menu->menuTrad->on = 0;

}

void accept_trade(void)
{
    struct personnages *echange_player = find_perso_by_id(moi->echange_player);
    if (echange_player == NULL || (echange_player->x - moi->x)*(echange_player->x - moi->x)+(echange_player->y - moi->y)*(echange_player->y - moi->y) > 9)
    {
        sprintf (ordre + strlen(ordre), "0 %d 17 none none 0 none 0 ", moi->id); // decline
        menu_cond->acceptTrade = -1;
    }
    if (lettres->keystates[SDL_SCANCODE_ESCAPE])
        menu_cond->acceptTrade = -1;
    drawTextBox(renderer, &menu_cond->bgEventTextBox, false);
    char text[300];
    sprintf (text, "do you want to trade %d %s against %d %s ?", moi->items_cnt[10], moi->items[10], moi->items_cnt[11], moi->items[11]);
    TextInfo text_display = {text,  littleFont, 200, 150,0,{255, 255, 255, 255}, 0,0,0};
    drawSelector(renderer, menu_cond->selector_accept_trade);
    drawTextInfo(renderer, &text_display);
    if (lettres->keystates[SDL_SCANCODE_S] || lettres->keystates[SDL_SCANCODE_DOWN])
    	menu_cond->selector_accept_trade->selectedOption = (menu_cond->selector_accept_trade->selectedOption + 1) % menu_cond->selector_accept_trade->numOptions;
    if (lettres->keystates[SDL_SCANCODE_Z] || lettres->keystates[SDL_SCANCODE_UP])
	    menu_cond->selector_accept_trade->selectedOption = (menu_cond->selector_accept_trade->selectedOption - 1 + menu_cond->selector_accept_trade->numOptions) % menu_cond->selector_accept_trade->numOptions;
    if (lettres->keystates[SDL_SCANCODE_RETURN] == 1)
    {
        if(menu_cond->selector_accept_trade->selectedOption == 0)
            echange_item_net(moi, find_perso_by_id(moi->echange_player));
        else if(menu_cond->selector_accept_trade->selectedOption == 1)
            sprintf (ordre + strlen(ordre), "0 %d 17 none none 0 none 0 ", moi->id); // decline
        else
        {
            sprintf (ordre + strlen(ordre), "0 %d 17 none none 0 none 0 ", moi->id); // decline
            main_menu->on.isPressed = 1;
            main_menu->menuTrad->on = 1;
        }
        menu_cond->acceptTrade = -1;
    }
}