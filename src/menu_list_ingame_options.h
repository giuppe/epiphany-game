/***************************************************************************
                          menu_list_options.h  -  description
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
#include <vector>

#ifndef MENU_LIST_INGAME_OPTIONS_H_
#define MENU_LIST_INGAME_OPTIONS_H_

class Menu_Entry;

class Menu_List_Ingame_Options : public Menu_List
{
private:
	
	bool m_fullscreen;

public:
	Uint32 sample_volume;
	Uint32 music_volume;
	
	Menu_List_Ingame_Options();
	
	~Menu_List_Ingame_Options();
		
	void action_left();
	
	void action_right();
	

	void action_quit();
	
	Uint32 get_list_size() const;
	
	std::string get_menu_entry_string(Uint32 entry) const;
	
};

#endif /*MENU_LIST_INGAME_OPTIONS_H_*/
