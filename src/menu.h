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
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "dephine.h"


#ifndef MENU_H
#define MENU_H
class Game;

class Menu
{
private:
	//Game* m_game;

	CL_Font* m_menu_font;

	unsigned int m_current_level;

	unsigned int m_unsolved_level;

	unsigned int m_total_levels;

	CL_Surface* m_selector;

	CL_Surface* m_background;

public:

	Menu(unsigned int total_levels, unsigned int unsolved_level);

	~Menu();

	void set_unsolved_level(unsigned int unsolved_level);

	unsigned int get_unsolved_level();

	unsigned int get_current_level();

	void set_current_level(unsigned int current_level);

	int go();

	bool increase_unsolved_level();

};

#endif //MENU_H
