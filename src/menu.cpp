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
#include <SDL/SDL.h>
#include <string>
#include "input.h"
#include "screen.h"
#include "game.h"
#include "menu_list.h"
#include "menu_list_options.h"
#include "menu_list_epiphany.h"




Menu::Menu(Uint32 total_levels, Uint32 unsolved_level)
{
  
	m_total_levels=total_levels;

	set_unsolved_level(unsolved_level);

	m_current_level=m_unsolved_level;
	
	m_menu_font=Font_Factory::MENU_FONT;

	Surface_Manager* surf_man= Surface_Manager::instance();

	m_selector.init(surf_man->get_surface(Surface_Manager::SRF_MENU_SELECTOR));
	
	m_background = surf_man->get_surface(Surface_Manager::SRF_MENU_BACKGROUND);

	
	

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




Sint32 Menu::go()
{


	Epiconfig* config=Epiconfig::instance();
	
	Menu_List_Epiphany* m_menu_list = new Menu_List_Epiphany(m_unsolved_level);

	render_menu_list(m_menu_list, config->get_screen_size_y()/2, config->get_screen_size_x()/2, config->get_screen_size_y()/12);

	DEBOUT("Menu selected: "<<m_menu_list->get_selected()<<"\n");

	Uint32 return_action;
	
	switch(m_menu_list->get_return_action())
	{
		case Menu_List_Epiphany::MENU_START:
			return_action = MENU_EPIPHANY_START;
			break;
		case Menu_List_Epiphany::MENU_OPTIONS:
		{
			return_action = MENU_EPIPHANY_NONE;
			Menu_List_Options menu_options;
			render_menu_list(&menu_options, config->get_screen_size_y()/2, config->get_screen_size_x()/2, config->get_screen_size_y()/12);
			break;
		}
		case Menu_List_Epiphany::MENU_QUIT:
			return_action = MENU_EPIPHANY_QUIT;
			break;
		default:
			DEBWARN("Warning: Selecting unhandled menu action: "<<m_menu_list->get_return_action()<<"; \n\tdefaulting to MENU_QUIT");
			return_action = MENU_EPIPHANY_QUIT;
	}

	m_current_level = m_menu_list->get_selected_level();
	
	delete m_menu_list;

	return return_action;

}




void Menu::print_menu_background()
{
	
	Epiconfig* config=Epiconfig::instance();
	
	
	m_background->put_screen(0,0, config->get_screen_size_x(), config->get_screen_size_y());
	
}




void Menu::render_menu_list(Menu_List* menu_list, Sint32 menu_top_point, Sint32 menu_left_point, Sint32 menu_vertical_distance)
{
	Uint32 current_time;

	Input* input = Input::instance();

	Screen* screen = Screen::instance();

	Font* menu_font = Font_Manager::instance()->get_font(m_menu_font); 

	input->update();
	
	while(menu_list->get_return_action() == Menu_List::MENU_NONE)
	{

		current_time=SDL_GetTicks();

		screen->clear();

		this->print_menu_background();
		
		//printing menu
		
				
		for(Uint32 i=0; i<menu_list->get_list_size(); i++)
		{
			menu_font->write(menu_left_point-50, menu_top_point+menu_vertical_distance*i, menu_list->get_menu_entry_string(i));
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
		
		
		
		m_selector.update_frame();
		
		//animated menu selector drawing
		
		m_selector.put_screen(menu_left_point-90,menu_top_point+menu_list->get_selected()*menu_vertical_distance,32,32);

		screen->flip_display();

		do
		{
			
			if((SDL_GetTicks()-current_time)<90)
			{

				SDL_Delay(10);

			}

		}

		while((SDL_GetTicks()-current_time)<100);

		input->update();

	}	
}

