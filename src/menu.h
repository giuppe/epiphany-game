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
#include "runnable.h"

#ifndef MENU_H
#define MENU_H
class Game;

class Menu_List;

class Menu_List_Epiphany;

class Menu_List_Options;

class Screen;

class Input;

class Font;



class Menu : public Runnable
{
	
public:
	enum{
		MENU_EPIPHANY_NONE,
		MENU_EPIPHANY_START,
		MENU_EPIPHANY_QUIT
	};
	
private:

	Font_Handle m_menu_font;

	Uint32 m_current_level;

	Uint32 m_unsolved_level;

	Uint32 m_total_levels;

	Sprite m_selector;

	Surface* m_background;

	Sint32 m_result = MENU_EPIPHANY_NONE;

	Menu_List_Epiphany* m_main_menu_list;

	Menu_List_Options* m_options_menu_list;

	Sint32 m_main_menu_top_point; 
	Sint32 m_main_menu_left_point; 
	Sint32 m_main_menu_vertical_distance;

	Sint32 m_options_menu_top_point; 
	Sint32 m_options_menu_left_point; 
	Sint32 m_options_menu_vertical_distance;

	bool m_is_options_menu_open = false;

public:

	Menu(Uint32 total_levels, Uint32 unsolved_level);

	~Menu();

	void set_unsolved_level(Uint32 unsolved_level);

	Uint32 get_unsolved_level();

	Uint32 get_current_level();

	void set_current_level(Uint32 current_level);

	bool increase_unsolved_level();
	
	void print_menu_background();

	Sprite* get_selector(){return &m_selector;};

	void setup();

	void update(double elapsed);

	void destroy();

	Sint32 get_result(){return m_result;};

};



#endif //MENU_H
