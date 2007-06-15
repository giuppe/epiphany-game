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
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
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

Menu::Menu(Uint32 total_levels, Uint32 unsolved_level)
{
  

	m_total_levels=total_levels;

	set_unsolved_level(unsolved_level);

	m_current_level=m_unsolved_level;

	
	m_menu_font=Font_Factory::MENU_FONT;

	Surface_Manager* surf_man= Surface_Manager::instance();

	m_selector = surf_man->get_surface(Surface_Manager::SRF_MENU_SELECTOR);
	
	m_background = surf_man->get_surface(Surface_Manager::SRF_MENU_BACKGROUND);

//	m_selector->init(CL_Surface::load("Surfaces/MNU_Selector", res_manager));

//	m_background->init(CL_Surface::load("Surfaces/MNU_Background", res_manager));
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
	char level_string[3];
	Sint32 curr_sprite=0;
	Input* input = Input::instance();
	Screen* screen = Screen::instance();
	Font* menu_font =Font_Manager::instance()->get_font(m_menu_font); 
	//CL_System::keep_alive();
	input->update();
	while(!(((input->get_enter())||
				(input->get_fire()))&&
				(selected!=1)) )

	{
		current_time=SDL_GetTicks();
		screen->clear();
		m_background->put_screen(0,0, config->get_game_size_x(), config->get_game_size_y());
		sprintf(level_string, "%d",level_number);
		//m_menu_font->print_center(k_game_size_x/2,30,"Epiphany");
		int menu_top_point=config->get_game_size_y()/2;
		int menu_vertical_distance=config->get_game_size_y()/10;
		menu_font->write((config->get_game_size_x()/2)-50, menu_top_point, "Start");
		menu_font->write((config->get_game_size_x()/2)-50, menu_top_point+menu_vertical_distance, "Level:");
		menu_font->write((config->get_game_size_x()/2)+60, menu_top_point+menu_vertical_distance, level_string);
		menu_font->write((config->get_game_size_x()/2)-50, menu_top_point+menu_vertical_distance*2, "Credits");
		menu_font->write((config->get_game_size_x()/2)-50, menu_top_point+menu_vertical_distance*3, "Quit");
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
		
		if((input->get_left())&&
				(selected==1)&&
				(level_number>0))
		{
			level_number--;
		}
		
		if((input->get_right())&&
				(selected==1)&&
				(level_number<m_total_levels-1)&&
				(level_number<m_unsolved_level))
		{
			level_number++;
		}
		
		//animated menu selector drawing
		m_selector->put_screen((config->get_game_size_x()/2)-90,menu_top_point+selected*menu_vertical_distance,32,32,curr_sprite);

		if(curr_sprite<7)
		{
			curr_sprite++;
		}
		else
		{
			curr_sprite=0;
		}

		
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
