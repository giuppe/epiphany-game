/***************************************************************************
                          menu_list_options.cpp  -  description
                             -------------------
    begin                : Jun 13 2007
    copyright            : (C) 2007 by Giuseppe D'Aqui'
    email                : kumber@tiscalinet.it
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License, Version 2,      *
 *   as published by the Free Software Foundation.                         *
 *                                                                         *
 ***************************************************************************/

#include "dephine.h"
#include "menu_list_ingame_options.h"
#include "menu_entry.h"
#include "menu_entry_simple.h"
#include "menu_entry_ranged.h"
#include "menu_entry_bool.h"
#include "menu_state.h"
#include "sfx.h"
#include "music_manager.h"
#include "game_manager.h"
#include "credits_state.h"
#include "screen.h"
#include <vector>
#include <cassert>

Menu_List_Ingame_Options* callback_ingame_obj;

void menu_options_ingame_callback_back()
{
	Game_Manager::instance()->change_state(new Menu_State());
}

void menu_options_ingame_callback_sample_volume()
{
	Sample_Manager::instance()->set_volume(callback_ingame_obj->sample_volume);
}

void menu_options_ingame_callback_music_volume()
{
	Music_Manager::instance()->set_volume(callback_ingame_obj->music_volume);
}

void menu_options_ingame_callback_fullscreen()
{
	Screen::instance()->toggle_fullscreen();
	Epiconfig::instance()->set_fullscreen(Screen::instance()->is_fullscreen());
			
}


Menu_List_Ingame_Options::Menu_List_Ingame_Options()
{
	m_selected = 0;

	sample_volume = Sample_Manager::instance()->get_volume();

	music_volume = Music_Manager::instance()->get_volume();

	m_fullscreen = Screen::instance()->is_fullscreen();

	callback_ingame_obj = this;
	
	m_entries_list.push_back(new Menu_Entry_Ranged(0, Sample_Manager::instance()->get_max_volume(), "Sound Volume: ", &sample_volume, &menu_options_ingame_callback_sample_volume));

	m_entries_list.push_back(new Menu_Entry_Ranged(0, Music_Manager::instance()->get_max_volume(), "Music Volume: ", &music_volume, &menu_options_ingame_callback_music_volume));
	
	m_entries_list.push_back(new Menu_Entry_Bool("Fullscreen: ", &m_fullscreen, &menu_options_ingame_callback_fullscreen));
	
	m_entries_list.push_back(new Menu_Entry_Simple("Back", &menu_options_ingame_callback_back));
	
}




Menu_List_Ingame_Options::~Menu_List_Ingame_Options()
{
	for(Uint32 i=0; i<m_entries_list.size(); i++)
	{
		delete m_entries_list[i];
	}
}




void Menu_List_Ingame_Options::action_quit()
{
	(*menu_options_ingame_callback_back)();
	this->action_press();
}




void Menu_List_Ingame_Options::action_right()
{
	Menu_List::action_right();
	Sample_Manager::instance()->set_volume(m_entries_list[0]->get_value());
	Music_Manager::instance()->set_volume(m_entries_list[1]->get_value());
			
}




void Menu_List_Ingame_Options::action_left()
{
	Menu_List::action_left();
	Sample_Manager::instance()->set_volume(m_entries_list[0]->get_value());
	Music_Manager::instance()->set_volume(m_entries_list[1]->get_value());
			
}




std::string Menu_List_Ingame_Options::get_menu_entry_string(Uint32 entry) const
{
	assert(entry<m_entries_list.size() && "Fatal: Accessing menu_entry outside limits");

	return m_entries_list[entry]->get_string();
}




Uint32 Menu_List_Ingame_Options::get_list_size() const
{
	return m_entries_list.size();
		
}



