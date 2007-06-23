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
#include "menu_entry.h"
#include "menu_entry_simple.h"
#include "menu_entry_ranged.h"





Menu::Menu(Uint32 total_levels, Uint32 unsolved_level)
{
  
	m_total_levels=total_levels;

	set_unsolved_level(unsolved_level);

	m_current_level=m_unsolved_level;
	
	m_menu_font=Font_Factory::MENU_FONT;

	Surface_Manager* surf_man= Surface_Manager::instance();

	m_selector.init(surf_man->get_surface(Surface_Manager::SRF_MENU_SELECTOR));
	
	m_background = surf_man->get_surface(Surface_Manager::SRF_MENU_BACKGROUND);

	Menu_Entry* menu_start = new Menu_Entry_Simple("Start");
	
	Menu_Entry* menu_level = new Menu_Entry_Ranged(0, m_unsolved_level, "Level: ");
	
	Menu_Entry* menu_credits = new Menu_Entry_Simple("Credits");
	
	Menu_Entry* menu_quit = new Menu_Entry_Simple("Quit");
	
	
	m_menu_strings.push_back(menu_start);
	
	m_menu_strings.push_back(menu_level);
	
	m_menu_strings.push_back(menu_credits);
	
	m_menu_strings.push_back(menu_quit);
	

}




Menu::~Menu()
{
	for(Uint32 i=0; i<m_menu_strings.size(); i++)
	{
		delete m_menu_strings[i];
	}

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
    return false;

  return true;
}




Sint32 Menu::go()
{

	DEBOUT("Entering menu()...\n");

	Epiconfig* config=Epiconfig::instance();

	Sint32 selected=0;

	Uint32 level_number=m_current_level;

	Uint32 current_time;

	char level_number_string[255];

	//Sint32 curr_sprite=0;

	Input* input = Input::instance();

	Screen* screen = Screen::instance();

	Font* menu_font =Font_Manager::instance()->get_font(m_menu_font); 

	input->update();

	while(!(((input->get_enter())||
				(input->get_fire()))&&
				(selected!=1)) )
	{

		current_time=SDL_GetTicks();

		screen->clear();

		m_background->put_screen(0,0, config->get_game_size_x(), config->get_game_size_y());

		sprintf(level_number_string, "%d",level_number);

		//m_menu_font->print_center(k_game_size_x/2,30,"Epiphany");

		int menu_top_point=config->get_game_size_y()/2;

		int menu_vertical_distance=config->get_game_size_y()/10;
		
		//inserting level number
		

		
		//printing menu
		
		for(Uint32 i=0; i<m_menu_strings.size(); i++)
		{
			menu_font->write((config->get_game_size_x()/2)-50, menu_top_point+menu_vertical_distance*i, m_menu_strings[i]->get_string());
		}	
		
	
/*
		menu_font->write((config->get_game_size_x()/2)-50, menu_top_point, "Start");

		menu_font->write((config->get_game_size_x()/2)-50, menu_top_point+menu_vertical_distance, "Level:");

		menu_font->write((config->get_game_size_x()/2)+60, menu_top_point+menu_vertical_distance, level_string);

		menu_font->write((config->get_game_size_x()/2)-50, menu_top_point+menu_vertical_distance*2, "Credits");

		menu_font->write((config->get_game_size_x()/2)-50, menu_top_point+menu_vertical_distance*3, "Quit");
*/
		if(input->get_up())
		{

			if(selected>0)
			{

				selected--;

			}

		}
		
		if(input->get_down())
		{

			if(selected<3)
			{

				selected++;

			}

		}
		
		if((input->get_left()))
		{

			//level_number--;
			m_menu_strings[selected]->action_left();

		}
		
		if((input->get_right()))
		{

					m_menu_strings[selected]->action_right();

		}
		
		m_selector.update_frame();
		
		//animated menu selector drawing
		m_selector.put_screen((config->get_game_size_x()/2)-90,menu_top_point+selected*menu_vertical_distance,32,32);
/*
		if(curr_sprite<7)
		{

			curr_sprite++;

		}
		else
		{

			curr_sprite=0;

		}
*/
	
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

	m_current_level=level_number;

	DEBOUT("Exiting Menu::go()... "<<selected<<"\n");

	return selected;

}
