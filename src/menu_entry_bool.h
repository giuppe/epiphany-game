/***************************************************************************
                          menu_entry_bool.h  -  description
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

#ifndef MENU_ENTRY_BOOL_H_
#define MENU_ENTRY_BOOL_H_

#include "menu_entry.h"
#include <string>

class Menu_Entry_Bool : public Menu_Entry
{

	protected:
	
		std::string m_string;
	
		Uint32 m_current_value;
		
	
	public:

		Menu_Entry_Bool(const char* string):
						m_string(string),
						m_current_value(0)
						{};
																
		Menu_Entry_Bool(const char* string, Uint32 current_value):
																m_string(string),
																m_current_value(current_value)
																{};
	
		void set_current_value(Uint32 current_value);
		
		Uint32 get_value() const {return m_current_value;}
	
		std::string get_string() const;
	
		void set_string(const std::string& string){m_string = string;}
	
		void action_left(){};
	
		void action_right(){};
	
		void action_up(){};
	
		void action_down(){};
	
		void action_press();
	
		~Menu_Entry_Bool(){};		
	
};

#endif /*MENU_ENTRY_BOOL_H_*/
