#include "craft_menu.h"

void craft_menu(void)
{
    for (int i = 0; 10 > i; i++)
    {
        if (moi->items_cnt[i] <= 0 || (moi->items[i][0] == '.' && moi->items[i][1] == '\0'))
            main_menu->menuCraft->selector->options[i][0] = '\0';
        else
            sprintf(main_menu->menuCraft->selector->options[i], "%s %d", moi->items[i], moi->items_cnt[i]);
    }

    drawSelector(renderer, main_menu->menuCraft->selector);
    
    if (lettres->keystates[SDL_SCANCODE_ESCAPE])
        main_menu->menuCraft->on = 0;
    if (lettres->keystates[SDL_SCANCODE_S] || lettres->keystates[SDL_SCANCODE_DOWN])
        main_menu->menuCraft->selector->selectedOption = (main_menu->menuCraft->selector->selectedOption + 1) % main_menu->menuCraft->selector->numOptions;
    if (lettres->keystates[SDL_SCANCODE_Z] || lettres->keystates[SDL_SCANCODE_UP])
        main_menu->menuCraft->selector->selectedOption = (main_menu->menuCraft->selector->selectedOption - 1 + main_menu->menuCraft->selector->numOptions) % main_menu->menuCraft->selector->numOptions;
    if (lettres->keystates[SDL_SCANCODE_RETURN])
        main_menu->menuCraft->selector->selectedOptionArray[main_menu->menuCraft->selector->selectedOption] *= -1;
    
    // wooden pillar
    int wooden_board = 0;
    int wooden_stick = 0;
    int basalt = 0;
    int quartzite = 0;
    for (int i = 0; i < 10; i++)
    {
        if (main_menu->menuCraft->selector->selectedOptionArray[i] != 1)
            continue;
        if (strncmp(main_menu->menuCraft->selector->options[i], "wooden-board", 12) == 0)
            wooden_board += 1;
        else if (strncmp(main_menu->menuCraft->selector->options[i], "wooden-stick", 12) == 0)
            wooden_stick += 1;
        else if (strncmp(main_menu->menuCraft->selector->options[i], "basalt", 6) == 0)
            basalt += 1;
        else if (strncmp(main_menu->menuCraft->selector->options[i], "quartzite", 9) == 0)
            quartzite += 1;
    }
    // Checked before the "wooden_stick == 3" wedge case below: the counts
    // (1 vs 3) never collide on their own, but checking the stone-bearing
    // combo first keeps the more specific recipe's priority explicit.
    if (wooden_stick == 1 && (basalt == 1 || quartzite == 1))
    {
        initTextInfo(&main_menu->menuCraft->result_craft, "stone-pickaxe", littleFont, 600, 100, 0, (SDL_Color){200, 200, 200, 255}, 0, 0, 0);
        drawTextInfo(renderer, &main_menu->menuCraft->result_craft);
        if (lettres->keystates[SDL_SCANCODE_O])
        {
            if (basalt == 1)
                sprintf (ordre + strlen(ordre), "0 %d 16 1 wooden-stick 0 %d 16 1 basalt 0 %d 16 +1 stone-pickaxe", moi->id, moi->id, moi->id);
            else
                sprintf (ordre + strlen(ordre), "0 %d 16 1 wooden-stick 0 %d 16 1 quartzite 0 %d 16 +1 stone-pickaxe", moi->id, moi->id, moi->id);
        }
    }
    else if (wooden_stick == 3)
    {
        initTextInfo(&main_menu->menuCraft->result_craft, "wooden-wedge", littleFont, 600, 100, 0, (SDL_Color){180, 140, 90, 255}, 0, 0, 0);
        drawTextInfo(renderer, &main_menu->menuCraft->result_craft);
        if (lettres->keystates[SDL_SCANCODE_O])
        {
            sprintf (ordre + strlen(ordre), "0 %d 16 3 wooden-stick 0 %d 16 +1 wooden-wedge", moi->id, moi->id);
        }
    }
    else if (wooden_board == 1)
    {
        initTextInfo(&main_menu->menuCraft->result_craft, "wooden-stick 4", littleFont, 600, 100, 0, (SDL_Color){255, 0, 255, 255}, 0, 0, 0);
        drawTextInfo(renderer, &main_menu->menuCraft->result_craft);
        if (lettres->keystates[SDL_SCANCODE_O])
        {
            sprintf (ordre + strlen(ordre), "0 %d 16 1 wooden-board 0 %d 16 +4 wooden-stick", moi->id, moi->id);
        }
    }
    else if (wooden_board == 9)
    {
        initTextInfo(&main_menu->menuCraft->result_craft, "wooden-pillar", littleFont, 600, 100, 0, (SDL_Color){255, 255, 255, 255}, 0, 0, 0);
        drawTextInfo(renderer, &main_menu->menuCraft->result_craft);
        if (lettres->keystates[SDL_SCANCODE_O])
        {
            sprintf (ordre + strlen(ordre), "0 %d 18 0 ", moi->id);
        }
    }
}