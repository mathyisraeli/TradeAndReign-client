#ifndef TRADE_MENU_H
#define TRADE_MENU_H

#include <SDL2/SDL.h>
#include "../menu.h"
#include "../../graphic_widget/textBox.h"
#include "../../graphic_widget/textInfo.h"
#include "../../graphic_widget/menuSelector.h"
#include "../../graphic_widget/gauge.h"
#include "../../graphic_widget/dropDown.h"
#include "../../graphic_widget/pictureButton.h"
#include "../../perso.h"
#include "../../clavier.h"
#include "../../../../TradeAndReign-shared//utile.h"

void menu_trade(void);
void accept_trade(void);
void echange_item_net(struct personnages *perso1, struct personnages *perso2);

#endif /* TRADE_MENU_H */