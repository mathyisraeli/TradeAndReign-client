#include "inventaire_menu.h"

void menu_inventaire(void)
{
    for (int i = 0; 10 > i; i++)
    {
        if (moi->items_cnt[i] <= 0 || (moi->items[i][0] == '.' && moi->items[i][1] == '\0'))
            main_menu->menuInv->selector->options[i][0] = '\0';
        else
            sprintf(main_menu->menuInv->selector->options[i], "%s %d", moi->items[i], moi->items_cnt[i]);
    }

    drawSelector(renderer, main_menu->menuInv->selector);
    drawSelector(renderer, main_menu->menuInv->equipement);
    if (main_menu->menuInv->enter == 0)
    {
        if (lettres->keystates[SDL_SCANCODE_ESCAPE])
            main_menu->menuInv->on = 0;
        if (lettres->keystates[SDL_SCANCODE_S] || lettres->keystates[SDL_SCANCODE_DOWN])
    	    main_menu->menuInv->selector->selectedOption = (main_menu->menuInv->selector->selectedOption + 1) % main_menu->menuInv->selector->numOptions;
        if (lettres->keystates[SDL_SCANCODE_Z] || lettres->keystates[SDL_SCANCODE_UP])
    	    main_menu->menuInv->selector->selectedOption = (main_menu->menuInv->selector->selectedOption - 1 + main_menu->menuInv->selector->numOptions) % main_menu->menuInv->selector->numOptions;
        if (lettres->keystates[SDL_SCANCODE_RETURN])
            main_menu->menuInv->enter = 1;
    }
    else
    {
        if (lettres->keystates[SDL_SCANCODE_RETURN])
        {
            if(main_menu->menuInv->actions->selectedOption == 0)//consume
            {
                //if (counter_use_item > 3)
                //{
                    if (strcmp(moi->items[main_menu->menuInv->selector->selectedOption], "fruit") == 0)
                        sprintf(ordre+strlen(ordre), "0 %d 16 1 fruit 0 %d 07 %d ", moi->id, moi->id, FOOD_VALUE_FRUIT);
                    else if (strcmp(moi->items[main_menu->menuInv->selector->selectedOption], "vegetable") == 0)
                        sprintf(ordre+strlen(ordre), "0 %d 16 1 vegetable 0 %d 07 %d ", moi->id, moi->id, FOOD_VALUE_VEGETABLE);
                    else if (strcmp(moi->items[main_menu->menuInv->selector->selectedOption], "meat") == 0)
                        sprintf(ordre+strlen(ordre), "0 %d 16 1 meat 0 %d 07 %d ", moi->id, moi->id, FOOD_VALUE_MEAT);
                    else if (strcmp(moi->items[main_menu->menuInv->selector->selectedOption], "spice") == 0)
                        sprintf(ordre+strlen(ordre), "0 %d 16 1 spice 0 %d 07 %d ", moi->id, moi->id, FOOD_VALUE_SPICE);
                    else if (strcmp(moi->items[main_menu->menuInv->selector->selectedOption], "herbe") == 0)
                    {
                        if (find_building_by_id(building_id[(int)moi->x + (int)moi->y*max_x]) == NULL)
                            sprintf(ordre+strlen(ordre), "0 %d 16 1 herbe 0 %d 13 %d he1 ", moi->id, moi->id, (int)moi->x + (int)moi->y*max_x);
                    }
                    else if (strcmp(moi->items[main_menu->menuInv->selector->selectedOption], "sable") == 0)
                    {
                        if (find_building_by_id(building_id[(int)moi->x + (int)moi->y*max_x]) == NULL)
                            sprintf(ordre+strlen(ordre), "0 %d 16 1 sable 0 %d 13 %d sa1 ", moi->id, moi->id, (int)moi->x + (int)moi->y*max_x);
                    }
                  //  counter_use_item = 0;
                //}
                //counter_use_item += 1;
            }
            else if (main_menu->menuInv->actions->selectedOption == 1)//equipe
            {
                if (strcmp(moi->items[main_menu->menuInv->selector->selectedOption], "leather_helmet") == 0)
                {
                    if (strcmp(moi->items[14], ".") != 0)
                        sprintf(ordre+strlen(ordre), "0 %d 16 +1 %s ", moi->id, moi->items[14]);
                    sprintf(ordre+strlen(ordre), "0 %d 27 leather_helmet 0 %d 16 1 leather_helmet ", moi->id, moi->id);
                }
                else if (strcmp(moi->items[main_menu->menuInv->selector->selectedOption], "leather_jacket")== 0)
                {
                    if (strcmp(moi->items[15], ".") != 0)
                        sprintf(ordre+strlen(ordre), "0 %d 16 +1 %s ", moi->id, moi->items[15]);
                    sprintf(ordre+strlen(ordre), "0 %d 28 leather_jacket 0 %d 16 1 leather_jacket ", moi->id, moi->id);
                }
                else if (strcmp(moi->items[main_menu->menuInv->selector->selectedOption], "leather_pants")==0)
                {
                    if (strcmp(moi->items[16], ".") != 0)
                        sprintf(ordre+strlen(ordre), "0 %d 16 +1 %s ", moi->id, moi->items[16]);
                    sprintf(ordre+strlen(ordre), "0 %d 28 leather_pants 0 %d 16 1 leather_pants ", moi->id, moi->id);
                }
                else if (strcmp(moi->items[main_menu->menuInv->selector->selectedOption], "breeches")==0)
                {
                    if (strcmp(moi->items[16], ".") != 0)
                        sprintf(ordre+strlen(ordre), "0 %d 16 +1 %s ", moi->id, moi->items[16]);
                    sprintf(ordre+strlen(ordre), "0 %d 28 breeches 0 %d 16 1 breeches ", moi->id, moi->id);
                }
                else if (strcmp(moi->items[main_menu->menuInv->selector->selectedOption], "shift")==0)
                {
                    if (strcmp(moi->items[16], ".") != 0)
                        sprintf(ordre+strlen(ordre), "0 %d 16 +1 %s ", moi->id, moi->items[16]);
                    sprintf(ordre+strlen(ordre), "0 %d 28 shift 0 %d 16 1 shift ", moi->id, moi->id);
                }
                else if (strcmp(moi->items[main_menu->menuInv->selector->selectedOption], "leather_boots") == 0)
                {
                    if (strcmp(moi->items[17], ".") != 0)
                        sprintf(ordre+strlen(ordre), "0 %d 16 +1 %s ", moi->id, moi->items[17]);
                    sprintf(ordre+strlen(ordre), "0 %d 30 leather_boots 0 %d 16 1 leather_boots ", moi->id, moi->id);
                }
            }   
            else if (main_menu->menuInv->actions->selectedOption== 2)//drop
                sprintf(ordre+strlen(ordre), "0 %d 16 %d %s ", moi->id, moi->items_cnt[main_menu->menuInv->selector->selectedOption], moi->items[main_menu->menuInv->selector->selectedOption]);
            main_menu->menuInv->enter = 0;
        }
        if (lettres->keystates[SDL_SCANCODE_ESCAPE])
            main_menu->menuInv->enter = 0;
        if (lettres->keystates[SDL_SCANCODE_S] || lettres->keystates[SDL_SCANCODE_DOWN])
    	    main_menu->menuInv->actions->selectedOption = (main_menu->menuInv->actions->selectedOption + 1) % main_menu->menuInv->actions->numOptions;
        if (lettres->keystates[SDL_SCANCODE_Z] || lettres->keystates[SDL_SCANCODE_UP])
    	    main_menu->menuInv->actions->selectedOption = (main_menu->menuInv->actions->selectedOption - 1 + main_menu->menuInv->actions->numOptions) % main_menu->menuInv->actions->numOptions;
        drawSelector(renderer, main_menu->menuInv->actions);
    }
}