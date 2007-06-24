/***************************************************************************
                          menu.h  -  description
                             -------------------
    begin                : Mon Jul 29 2002
    copyright            : (C) 2002 by Giuseppe D'Aqui'
    email                : kumber@tiscalinet.it
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License, Version 2, as published by  *
 *   the Free Software Foundation.                                   *
 *                                                                         *
 ***************************************************************************/

#include "dephine.h"
#include "fonts/font_manager.h"
#include "surface_manager.h"
#include "sprite.h"
#include "menu_list_epiphany.h"

#ifndef MENU_H
#define MENU_H
class Game;


class Menu
{
	
public:
	enum{
		MENU_EPIPHANY_START,
		MENU_EPIPHANY_CREDITS,
		MENU_EPIPHANY_QUIT
	};
	
private:

	Font_Handle m_menu_font;

	Uint32 m_current_level;

	Uint32 m_unsolved_level;

	Uint32 m_total_levels;

	Sprite m_selector;

	Surface* m_background;
	
	Menu_List_Epiphany* m_menu_list;

public:

	Menu(Uint32 total_levels, Uint32 unsolved_level);

	~Menu();

	void set_unsolved_level(Uint32 unsolved_level);

	Uint32 get_unsolved_level();

	Uint32 get_current_level();

	void set_current_level(Uint32 current_level);

	int go();

	bool increase_unsolved_level();

};

#endif //MENU_H
