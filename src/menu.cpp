/***************************************************************************
                          menu.cpp  -  description
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
#include "menu.h"
#include "surface.h"
#include "surface_manager.h"
#include "fonts/font.h"
#include "fonts/font_manager.h"
#include "fonts/font_factory.h"
#include <SDL2/SDL.h>
#include <string>
#include "input.h"
#include "screen.h"
#include "game.h"
#include "menu_list.h"
#include "menu_list_options.h"
#include "menu_list_epiphany.h"
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/html5.h>
#endif



Menu::Menu(Uint32 total_levels, Uint32 unsolved_level)
{
  
	m_total_levels=total_levels;

	set_unsolved_level(unsolved_level);

	m_current_level=m_unsolved_level;
	
	m_menu_font=Font_Factory::MENU_FONT;

	Surface_Manager* surf_man= Surface_Manager::instance();

	m_selector.init(surf_man->get_surface(Surface_Manager::SRF_MENU_SELECTOR));
	
	m_background = surf_man->get_surface(Surface_Manager::SRF_MENU_BACKGROUND);

	m_selector.start_animation();
	
	

}




Menu::~Menu()
{


}




Uint32 Menu::get_current_level()
{

  return m_current_level;

}




void Menu::set_current_level(Uint32 current_level)
{

  if(current_level<m_total_levels)
  {

    m_current_level=current_level;

  }
  else
  {

    DEBOUT("Alert: setting current_level outside range..."<<current_level<<"\n");

    m_current_level=m_unsolved_level;

  }

}




Uint32 Menu::get_unsolved_level()
{

  return m_unsolved_level;

}




void Menu::set_unsolved_level(Uint32 unsolved_level)
{

  if(unsolved_level<m_total_levels)
  {

    m_unsolved_level=unsolved_level;

  }
  else
  {

    DEBOUT("Alert: setting unsolved level outside range!\n");

    m_unsolved_level=0;

  }

}




bool Menu::increase_unsolved_level()
{

  m_unsolved_level++;

  if(m_unsolved_level==m_total_levels)
  {
    return false;
  }

  return true;
}


void Menu::print_menu_background()
{
	
	Epiconfig* config=Epiconfig::instance();
	
	ScreenCoord scr_coord;
	for(Uint32 i=0; i< config->get_screen_size_x(); i+=96)
	for(Uint32 j=0; j< config->get_screen_size_y(); j+=96)
	{
		
		scr_coord.x = i;
		scr_coord.y = j;
		Surface_Manager::instance()->get_surface(Surface_Manager::SRF_MENU_BACK_TILE)->put_screen(scr_coord);
	}
	
	scr_coord.x = config->get_screen_size_x()/2-148;
	scr_coord.y = 32;
	Surface_Manager::instance()->get_surface(Surface_Manager::SRF_MENU_TITLE)->put_screen(scr_coord);
	//m_background->put_screen(0,0, config->get_screen_size_x(), config->get_screen_size_y());
	
}

void Menu::setup()
{
	Epiconfig* config=Epiconfig::instance();
	
	Screen::instance()->resize_world_screen(0, 0);

	Input* input = Input::instance();
	
	m_main_menu_list = new Menu_List_Epiphany(m_unsolved_level);

	m_options_menu_list = new Menu_List_Options();

	m_main_menu_top_point= config->get_screen_size_y()/2;
	m_main_menu_left_point= config->get_screen_size_x()/2;
	m_main_menu_vertical_distance= config->get_screen_size_y()/12;
	
	m_options_menu_top_point= config->get_screen_size_y()/2;
	m_options_menu_left_point= config->get_screen_size_x()/3;
	m_options_menu_vertical_distance= config->get_screen_size_y()/12;

	input->reset_states();

	input->update();

}


void Menu::update(double elapsed)
{
	Screen* screen = Screen::instance();
	Input* input = Input::instance();
	Menu* menu = this;
	Font* menu_font = Font_Manager::instance()->get_font(m_menu_font);
	Sprite* selector = this->get_selector();	
	
	Menu_List* menu_list;
	Sint32 menu_top_point;
	Sint32 menu_left_point; 
	Sint32 menu_vertical_distance;
	if(m_is_options_menu_open==false)
	{
		menu_list = m_main_menu_list;
		menu_top_point = m_main_menu_top_point;
		menu_left_point = m_main_menu_left_point;
		menu_vertical_distance = m_main_menu_vertical_distance;
	}
	else
	{
		menu_list = m_options_menu_list;
		menu_top_point = m_options_menu_top_point;
		menu_left_point = m_options_menu_left_point;
		menu_vertical_distance = m_options_menu_vertical_distance;
	}
	

	screen->clear();

	menu->print_menu_background();
		
	//printing menu
						
	for(Uint32 i=0; i<menu_list->get_list_size(); i++)
	{
		menu_font->write(menu_left_point-50, menu_top_point+menu_vertical_distance*i, menu_list->get_menu_entry_string(i).c_str());
	}	
		

	if(input->get_up())
	{

		menu_list->action_up();

	}
		
	if(input->get_down())
	{

		menu_list->action_down();

	}
		
	if((input->get_left()))
	{

		menu_list->action_left();

	}
		
	if((input->get_right()))
	{

		menu_list->action_right();

	}
		
	if(input->get_enter())
	{
		menu_list->action_press();
	}
		

		
	ScreenCoord scr_coord;
		
	scr_coord.x = menu_left_point-90;
		
	scr_coord.y = menu_top_point+menu_list->get_selected()*menu_vertical_distance;
		
	selector->set_position_on_screen(scr_coord);
		
	selector->draw();
		
	//	m_selector.put_screen(scr_coord);

	screen->flip_display();

	input->update();
	
	if(m_is_options_menu_open == false)
	{
		switch(menu_list->get_return_action())
		{
			case Menu_List_Epiphany::MENU_START:
				m_result = MENU_EPIPHANY_START;
				break;
			case Menu_List_Epiphany::MENU_OPTIONS:
			{
				m_result = MENU_EPIPHANY_NONE;
				m_is_options_menu_open = true;
				//Menu_List_Options menu_options;
				//render_menu_list(&menu_options, config->get_screen_size_y()/2, config->get_screen_size_x()/3, config->get_screen_size_y()/12);
				break;
			}
			case Menu_List_Epiphany::MENU_QUIT:
				m_result = MENU_EPIPHANY_QUIT;
				break;
			//default:
				//DEBWARN("Warning: Selecting unhandled menu action: "<<menu_list->get_return_action()<<"; \n\tdefaulting to MENU_QUIT");
				//m_result = MENU_EPIPHANY_QUIT;
		}
		m_current_level = menu_list->get_selected_level();
	}
	else
	{
		switch(menu_list->get_return_action())
		{
			case Menu_List_Options::MENU_NONE:

			break;
			case Menu_List_Options::MENU_OK:
				m_is_options_menu_open = false;
			break;
		}
	}

	

}

void Menu::destroy()
{
	delete m_main_menu_list;
	delete m_options_menu_list;
}



