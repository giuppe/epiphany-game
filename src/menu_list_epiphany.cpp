/***************************************************************************
                          menu_list_epiphany.cpp  -  description
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
#include "menu_list_epiphany.h"
#include "menu_entry.h"
#include "menu_entry_simple.h"
#include "menu_entry_ranged.h"
#include "menu_list_options.h"
#include <vector>
#include <cassert>


Menu_List_Epiphany::Menu_List_Epiphany(Uint32 unsolved_level)
{
	m_return_action = Menu_List_Epiphany::MENU_NONE;
	
	m_selected = 0;
	
	m_entries_list.push_back(new Menu_Entry_Simple("Start"));
	
	m_entries_list.push_back(new Menu_Entry_Ranged(0, unsolved_level, "Level: ", unsolved_level));
	
	m_entries_list.push_back(new Menu_Entry_Simple("Options"));
	
	//m_entries_list.push_back(new Menu_Entry_Simple("Credits"));
	
	m_entries_list.push_back(new Menu_Entry_Simple("Quit"));
	
}

Menu_List_Epiphany::~Menu_List_Epiphany()
{
	for(Uint32 i=0; i<m_entries_list.size(); i++)
	{
		delete m_entries_list[i];
	}
}

void Menu_List_Epiphany::action_press()
{
	m_entries_list[m_selected]->action_press();
	
	switch(m_selected)
	{
		case 0:
			m_return_action = MENU_START;
			break;
		case 2:
			m_return_action = MENU_OPTIONS;
			break;
		case 3:
			m_return_action = MENU_QUIT;
			break;
		default:
			m_return_action = MENU_NONE;
	}

}

void Menu_List_Epiphany::action_down()
{
	
	if(m_selected<m_entries_list.size()-1)
	{

		m_selected++;

	}

}




void Menu_List_Epiphany::action_up()
{
	
	if(m_selected>0)
	{

		m_selected--;

	}

}


void Menu_List_Epiphany::action_right()
{
	m_entries_list[m_selected]->action_right();
}




void Menu_List_Epiphany::action_left()
{
	m_entries_list[m_selected]->action_left();
}




std::string Menu_List_Epiphany::get_menu_entry_string(Uint32 entry) const
{
	assert(entry<m_entries_list.size() && "Fatal: Accessing menu_entry outside limits");

	return m_entries_list[entry]->get_string();
}


Uint32 Menu_List_Epiphany::get_list_size() const
{
	return m_entries_list.size();
		
}


Uint32 Menu_List_Epiphany::get_return_action() const
{
	return m_return_action;
}

Uint32 Menu_List_Epiphany::get_selected_level() const
{
	return m_entries_list[1]->get_value();
	
}


