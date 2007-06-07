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
#include "game.h"

Menu::Menu(unsigned int total_levels, unsigned int unsolved_level)
{
  

  m_total_levels=total_levels;

  set_unsolved_level(unsolved_level);

  m_current_level=m_unsolved_level;

	CL_ResourceManager* res_manager=Game::instance()->get_resource_manager();

	m_menu_font=CL_Font::load("Fonts/FNT_Menu", res_manager);

  m_selector=CL_Surface::load("Surfaces/MNU_Selector", res_manager);

  m_background=CL_Surface::load("Surfaces/MNU_Background", res_manager);
}

Menu::~Menu()
{
	delete m_menu_font;
	
	delete m_selector;

	delete m_background;
}


unsigned int Menu::get_current_level()
{
  return m_current_level;
}

void Menu::set_current_level(unsigned int current_level)
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
unsigned int Menu::get_unsolved_level()
{
  return m_unsolved_level;
}

void Menu::set_unsolved_level(unsigned int unsolved_level)
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


int Menu::go()
{
	DEBOUT("Entering menu()...\n");
	Epiconfig* config=Epiconfig::instance();
	int selected=0;
	unsigned int level_number=m_current_level;
	unsigned int current_time;
	CL_String level_string;
	int curr_sprite=0;
	CL_System::keep_alive();
	while(!(((CL_Keyboard::get_keycode(CL_KEY_ENTER))||
				(CL_Keyboard::get_keycode(CL_KEY_SPACE)))&&
				(selected!=1)) )

	{
		current_time=CL_System::get_time();
		CL_Display::clear_display(0.0, 0.0, 0.0, 1.0);
		m_background->put_screen(0,0, (int)config->get_game_size_x(), (int)config->get_game_size_y());
		level_string=(int)level_number;
		//m_menu_font->print_center(k_game_size_x/2,30,"Epiphany");
		int menu_top_point=config->get_game_size_y()/2;
		int menu_vertical_distance=config->get_game_size_y()/10;
		m_menu_font->print_left((config->get_game_size_x()/2)-50, menu_top_point, "Start");
		m_menu_font->print_left((config->get_game_size_x()/2)-50, menu_top_point+menu_vertical_distance, "Level:");
		m_menu_font->print_left((config->get_game_size_x()/2)+60, menu_top_point+menu_vertical_distance, level_string);
		m_menu_font->print_left((config->get_game_size_x()/2)-50, menu_top_point+menu_vertical_distance*2, "Credits");
		m_menu_font->print_left((config->get_game_size_x()/2)-50, menu_top_point+menu_vertical_distance*3, "Quit");
		if(CL_Keyboard::get_keycode(CL_KEY_UP))
		{
			if(selected>0)
			{
				selected--;
			}
		}
		
		if(CL_Keyboard::get_keycode(CL_KEY_DOWN))
		{
			if(selected<3)
			{
				selected++;
			}
		}
		
		if((CL_Keyboard::get_keycode(CL_KEY_LEFT))&&
				(selected==1)&&
				(level_number>0))
		{
			level_number--;
		}
		
		if((CL_Keyboard::get_keycode(CL_KEY_RIGHT))&&
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

		
		CL_Display::flip_display();
		do
		{
			CL_System::keep_alive();
			if((CL_System::get_time()-current_time)<90)
			{
				CL_System::sleep(10);
			}
		}
		while((CL_System::get_time()-current_time)<100);
	}	
	m_current_level=level_number;

	DEBOUT("Exiting Menu::go()... "<<selected<<"\n");
	return selected;
}
