/***************************************************************************
                          menu_entry_simple.h  -  description
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

#ifndef MENU_ENTRY_SIMPLE_H_
#define MENU_ENTRY_SIMPLE_H_

#include "menu_entry.h"

class Menu_Entry_Simple : public Menu_Entry
{
	protected:
		std::string m_string;
		
	public:
	//	Menu_Entry_Simple(){};
	
		Menu_Entry_Simple(const char* string):m_string(string){};
	
		std::string get_string() const {return m_string;};
	
		void set_string(const std::string& string){m_string = string;};
		
		Uint32 get_value() const{ return 0;}
	
		void action_left(){};
	
		void action_right(){};
	
		void action_up(){};
	
		void action_down(){};
	
		void action_press(){};
	
		~Menu_Entry_Simple(){};		
	
};

#endif /*MENU_ENTRY_SIMPLE_H_*/
