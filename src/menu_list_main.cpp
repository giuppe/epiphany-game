/***************************************************************************
                          menu_list_main.cpp  -  description
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
#include "menu_list_main.h"
#include "menu_entry.h"
#include "menu_entry_simple.h"
#include "menu_entry_ranged.h"
#include "menu_list_options.h"
#include "loading_state.h"
#include "credits_state.h"
#include "menu_options_state.h"
#include "menu_base_state.h"
#include "game_manager.h"
#include <vector>
#include <cassert>

Menu_List_Main* callback_menumain_obj;

void menu_callback_start()
{
	Game_Manager::instance()->change_state(new Loading_State());
}

void menu_callback_quit()
{
	Game_Manager::instance()->change_state(new CreditsState());
}

void menu_callback_options()
{
	callback_menumain_obj->get_parent_menu_state()->launch_substate(new Menu_Options_State());
}

void menu_callback_level()
{
	DEBOUT(callback_menumain_obj->get_current_level());
	Epiconfig::instance()->set_current_level(callback_menumain_obj->get_current_level());
}

Menu_List_Main::Menu_List_Main(Menu_Base_State* parent)
{
	m_parent_menu_state = parent;

	Uint32 unsolved_level = Epiconfig::instance()->get_last_level();

	Uint32 last_selected_level = Epiconfig::instance()->get_current_level();
	
	Uint32 total_levels = Game_Manager::instance()->find_levels_in_dir();

	m_total_levels = total_levels;
	
	if(last_selected_level == 999)
		m_current_level = unsolved_level;
	else
		m_current_level = last_selected_level;
	
	m_selected = 0;

	Epiconfig::instance()->set_current_level(m_current_level);

	callback_menumain_obj = this;
	
	m_entries_list.push_back(new Menu_Entry_Simple("Start", &menu_callback_start));
	
	m_entries_list.push_back(new Menu_Entry_Ranged(0, unsolved_level, "Level: ", &m_current_level, &menu_callback_level));
	
	m_entries_list.push_back(new Menu_Entry_Simple("Options", &menu_callback_options));
	
	//m_entries_list.push_back(new Menu_Entry_Simple("Credits"));
	
	m_entries_list.push_back(new Menu_Entry_Simple("Quit", &menu_callback_quit));
	
}

Menu_List_Main::~Menu_List_Main()
{
	for(Uint32 i=0; i<m_entries_list.size(); i++)
	{
		delete m_entries_list[i];
	}
}

void Menu_List_Main::action_quit()
{
	(*menu_callback_quit)();
}





std::string Menu_List_Main::get_menu_entry_string(Uint32 entry) const
{
	assert(entry<m_entries_list.size() && "Fatal: Accessing menu_entry outside limits");

	return m_entries_list[entry]->get_string();
}


Uint32 Menu_List_Main::get_list_size() const
{
	return m_entries_list.size();
		
}




