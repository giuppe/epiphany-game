/***************************************************************************
                          menu_entry_bool.cpp  -  description
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

#include "menu_entry_bool.h"

void Menu_Entry_Bool::action_press()
{
	if(m_current_value == 0)
		m_current_value = 1;
	else
		m_current_value = 0;
		
}

std::string Menu_Entry_Bool::get_string() const
{
	if(m_current_value == 0)
	{
		return (m_string+std::string(" Off")).c_str();
	}
	
	return (m_string+std::string(" On")).c_str();
}
