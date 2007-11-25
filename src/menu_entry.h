/***************************************************************************
                          menu_entry.h  -  description
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

#ifndef MENU_ENTRY_H_
#define MENU_ENTRY_H_

#include "dephine.h"

class Menu_Entry
{
protected:
	
//	std::string m_string;

public:

	Menu_Entry(){};
	
	virtual std::string get_string() const = 0;
	
//	virtual void set_string(const char* string) = 0;
	
	virtual void action_left() = 0;
	
	virtual void action_right() = 0;
	
	virtual void action_up() = 0;
	
	virtual void action_down() = 0;
	
	virtual void action_press() = 0;
	
	virtual Uint32 get_value() const = 0;
	
	virtual ~Menu_Entry(){};		
	
};

#endif /*MENU_ENTRY_H_*/
