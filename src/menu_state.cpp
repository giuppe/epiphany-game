/***************************************************************************
                          menu_state.cpp  -  description
                             -------------------
    begin                : Thu Aug 1 2002
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
#include "menu_state.h"
#include "surface.h"
#include "surface_manager.h"
#include "music_manager.h"
#include "credits_state.h"
#include "fonts/font.h"
#include "fonts/font_manager.h"
#include "fonts/font_factory.h"
#include <SDL2/SDL.h>
#include <cmath>
#include <string>
#include "input.h"
#include "screen.h"
#include "game.h"
#include "menu_list.h"
#include "menu_list_options.h"
#include "menu_list_main.h"

#include "menu_entry.h"
#include "menu_entry_simple.h"
#include "menu_entry_ranged.h"
#include "menu_list_options.h"

#include "menu_options_state.h"

#include "game_manager.h"



Menu_State::Menu_State()
{
	
	
	
	

}




Menu_State::~Menu_State()
{


}











void Menu_State::create()
{
	Menu_Base_State::create();

	Music_Manager::instance()->play(MUS_MENU);
	m_menu_list = new Menu_List_Main();
	
}

void Menu_State::update(double elapsed)
{
	Menu_Base_State::update(elapsed);
	
	
	//DEBOUT("Menu selected: "<<m_menu_list->get_selected()<<"\n");

	

}

void Menu_State::draw()
{
	Menu_Base_State::draw();
	Epiconfig* config = Epiconfig::instance();
	this->render_menu_list(m_menu_list, 150, config->get_base_screen_size_x()/2, config->get_base_screen_size_y()/9);

}

void Menu_State::deinit()
{
	Menu_Base_State::deinit();
	delete m_menu_list;

}
