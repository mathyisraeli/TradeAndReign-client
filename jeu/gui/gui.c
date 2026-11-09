#include "gui.h"

void gui_event(struct personnages *moi) 
{
	SDL_Rect position;
	   
    //ordre de deplacement
	if (moi->ordrex > 0)
	{
        // Driven purely by the order's own 3 coordinates (ordrex, ordrey,
        // ordrea) now, not a ground_altitude[] lookup — that lookup assumed
        // flat ground under the target and put the marker in the wrong place
        // for an order given on a roof/floor. ordrea already carries the
        // exact target altitude (see picking.h / ordre.c), so this is the
        // same isometric formula as everywhere else, just fed with it.
        position.x = (moi->ordrex - moi->x - moi->ordrey + moi->y) * 34 + 890;
		position.y = (moi->ordrex - moi->x - moi->y  + moi->ordrey) * 17 + 440 - moi->ordrea + moi->altitude;
        position.w = 20; position.h = 20;
		if (powf(moi->x - moi->ordrex, 2) + powf(moi->y - moi->ordrey, 2) < 0.1)
        {
			sprintf (ordre + strlen(ordre), "0 %d 03 -1 ", moi->id);
        }
		SDL_RenderCopy(renderer, img->g->croix, NULL, &position);
	}
	
    //speak bubble
    for (struct linked_list *p = list; p != NULL; p = p->next)
	{
        if (strlen(p->p->speak) > 1)
        {
            TextInfo bubble = {p->p->speak,  littleFont, 
            (p->p->x - moi->x - p->p->y +  moi->y) * 34 + 900, 
            (p->p->x - moi->x + p->p->y - moi->y) * 17 + 350 - ground_altitude[((int)p->p->y - start_y) * (end_x - start_x) + (int)p->p->x - start_x] + moi->altitude,
            0,{255, 255, 255, 255}, 0,0,0};
            drawTextInfo(renderer, &bubble);
        }
    }
}

void display_selected(struct linked_list *selected)
{
    for (struct linked_list *p = selected; p != NULL; p = p->next)
    {
        SDL_Rect position2 = {p->p->screenx-1, p->p->screeny-1, p->p->sizescreenx + 1,p->p->sizescreeny + 1};
        SDL_RenderCopy(renderer, img->g->selecteur, NULL, &position2);
    }
    //TextInfo text_my_stats = {"pv\nqdsf", littleFont, 1100, 100, 0, {0, 0, 0, 255}, 1, 1, 0};
    //drawTextInfo(renderer, &text_my_stats);
}

void display_elipse_and_personal_datas()
{
    //SDL_Rect position = {0, 0, 1800, 900};
    char energy_text[20] = "energy : ";
    TextInfo energy = {energy_text, littleFont, 50, 850, 0, (SDL_Color){0, 0, 0, 255}, 0, 0, 0};
    char altitude_text[32] = "altitude : ";
    TextInfo altitude = {altitude_text, littleFont, 50, 875, 0, (SDL_Color){0, 0, 0, 255}, 0, 0, 0};
    sprintf (energy_text + 9, "%d", moi->faim);
    snprintf (altitude_text + 11, sizeof(altitude_text) - 11, "%d", moi->altitude / 38); // displayed in meters for the player, unlike the raw pixel-layer unit used everywhere else
    //SDL_RenderCopy(renderer, img->g->elipse, NULL, &position);

    
    //SDL_RenderCopy(renderer, img->g->menuButton, NULL, &position);
    if (lettres->Mouse_Lclick == 1)
    {
        if (lettres->Mouse_pos_x > 50 && lettres->Mouse_pos_x < 85 && lettres->Mouse_pos_y > 50 && lettres->Mouse_pos_y < 85)
            main_menu->on.isPressed = !main_menu->on.isPressed;
        else if (lettres->Mouse_pos_x >= main_menu->menuSound->on.x && lettres->Mouse_pos_x <= main_menu->menuSound->on.x + main_menu->menuSound->on.width && lettres->Mouse_pos_y >= main_menu->menuSound->on.y && lettres->Mouse_pos_y  <= main_menu->menuSound->on.y + main_menu->menuSound->on.height)
        {
            if(main_menu->menuSound->on.isPressed)
            {
                Mix_PlayMusic(sons->menu, 1);
                main_menu->menuSound->on.isPressed = false;
            }
            else
            {
                stopMusic();
                main_menu->menuSound->on.isPressed = true;
            }
        }
    }
    drawPictureButton( &main_menu->on);
    drawPictureButton(&menu_cond->accept_trade);
    drawPictureButton(&menu_cond->manage_formation);
    drawPictureButton(&main_menu->menuSound->on);
    drawGauge(&my_stats_display->my_health, moi->pv, moi->max_pv);
    drawTextInfo(renderer, &energy);
    drawTextInfo(renderer, &altitude);
}

void menu_religion(struct menu *m)
{
    m = m;
}

void speakPerso(struct personnages *moi, char* ordre)
{
    drawTextBox(renderer, speakBubble->textBox, true);
  
    if (text->on != 0)
    {
        strncat(speakBubble->textBox->text, text->textToPrint, sizeof(speakBubble->textBox->text) - strlen(speakBubble->textBox->text) - 1);
        text->on = 0;
    }
    else 
    {
        if (*text->key == SDLK_BACKSPACE)
            speakBubble->textBox->text[strlen(speakBubble->textBox->text)-1] = 0;
        else if (*text->key == SDLK_ESCAPE)
            speakBubble->on = 0;
        else if (*text->key == SDLK_RETURN)
        {
            sprintf (ordre + strlen(ordre), "0 %d 20 %s\037 ", moi->id, speakBubble->textBox->text);
            speakBubble->textBox->text[0] = 0;
            speakBubble->on = 0;
        } 
        *text->key = SDLK_UNKNOWN;
    }
}

void menu()
{
    if (main_menu->menuInv->on == 1)
    {
        menu_inventaire();
    }
    else if (main_menu->menuDip->on == 1)
    {
        diplomatic_menu();
    }
    else if (main_menu->menuTrad->on == 1)
    {
        menu_trade();
    }
    else if (main_menu->menuCraft->on == 1)
    {
        craft_menu();
    }
    else if (main_menu->menuTech->on == 1)
    {
        menu_technologie();
    }
    else
    {
        main_menu->menuDip->errorText.text = "\0";
	    if (lettres->keystates[SDL_SCANCODE_S] || lettres->keystates[SDL_SCANCODE_DOWN])
    	    main_menu->selector->selectedOption = (main_menu->selector->selectedOption + 1) % main_menu->selector->numOptions;
    	if (lettres->keystates[SDL_SCANCODE_Z] || lettres->keystates[SDL_SCANCODE_UP])
	        main_menu->selector->selectedOption = (main_menu->selector->selectedOption - 1 + main_menu->selector->numOptions) % main_menu->selector->numOptions;
        if (lettres->keystates[SDL_SCANCODE_ESCAPE])
            main_menu->on.isPressed = 0;
    
        if (lettres->keystates[SDL_SCANCODE_RETURN])
        {
            if(main_menu->selector->selectedOption == 0)
                main_menu->menuInv->on = 1;
            else if(main_menu->selector->selectedOption == 1)
                main_menu->menuDip->on = 1;
            else if(main_menu->selector->selectedOption == 2)
                main_menu->menuTrad->on = 1;
            else if(main_menu->selector->selectedOption == 7)
                main_menu->menuCraft->on = 1;
            else if(main_menu->selector->selectedOption == 4)
                main_menu->menuTech->on = 1;
        }
        drawSelector(renderer, main_menu->selector); 
    }
}


