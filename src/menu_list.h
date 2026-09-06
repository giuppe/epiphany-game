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
#include <vector>

#ifndef MENU_LIST_H_
#define MENU_LIST_H_

class Menu_Entry;



class Menu_List
{
public:

	
protected:

	std::vector<Menu_Entry*> m_entries_list;
	
	Uint32 m_selected;
	

public:
	virtual ~Menu_List(){};
	
	Uint32 get_selected() const {return m_selected;}
	
	bool is_selected(Uint32 entry)const{if(m_selected == entry) return true; return false;}
		
	
	void action_left();
	
	void action_right();
	
	void action_up();
	
	void action_down();
	
	void action_press();

	/**
	* To be called when ESC is pressed or the window is closed
	*/
	virtual void action_quit() = 0;
	
	virtual std::string get_menu_entry_string(Uint32 entry) const = 0;
	
	virtual Uint32 get_list_size() const = 0;
	
/*	
	virtual bool has_next_entry() = 0;
	
	virtual const char* get_next_entry() = 0;
	
	virtual void reset_entry_seek() = 0;
	
*/
};	

#endif /*MENU_LIST_H_*/
