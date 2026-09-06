/***************************************************************************
                          menu_list_main.h  -  description
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
#include "menu_list.h"
#include "menu_entry.h"
#include <vector>

#ifndef MENU_LIST_EPIPHANY_H_
#define MENU_LIST_EPIPHANY_H_

class Menu_List_Main : public Menu_List
{
private:

	
	
	Uint32 m_current_level;

	Uint32 m_total_levels;
	
public:
	
	Menu_List_Main();
	
	~Menu_List_Main();
		
	void action_left();
	
	void action_right();
	
	void action_up();
	
	void action_down();

	void action_quit();
	
	Uint32 get_list_size() const;
	
	std::string get_menu_entry_string(Uint32 entry) const;

	Uint32 get_current_level(){return m_current_level;}
	
};

#endif /*MENU_LIST_EPIPHANY_H_*/
