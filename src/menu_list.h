/***************************************************************************
                          menu_list.h  -  description
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

#ifndef MENU_LIST_H_
#define MENU_LIST_H_


class Menu_List
{
public:
	enum{
		MENU_NONE = 0
	};
	
protected:
	
	Uint32 m_selected;
	

public:
	virtual ~Menu_List(){};
	
	Uint32 get_selected(){return m_selected;}
	
	bool is_selected(Uint32 entry){if(m_selected == entry) return true; return false;}
		
	virtual Uint32 get_return_action() = 0;
	
	virtual void action_left() = 0;
	
	virtual void action_right() = 0;
	
	virtual void action_up() = 0;
	
	virtual void action_down() = 0;
	
	virtual void action_press() = 0;
	
	virtual const char* get_menu_entry_string(Uint32 entry) = 0;
	
	virtual Uint32 get_list_size() = 0;
	
/*	
	virtual bool has_next_entry() = 0;
	
	virtual const char* get_next_entry() = 0;
	
	virtual void reset_entry_seek() = 0;
	
*/
};	

#endif /*MENU_LIST_H_*/
