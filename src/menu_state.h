/***************************************************************************
                          menu_state.h  -  description
                             -------------------
    begin                : Mon Jul 29 2002
    copyright            : (C) 2002 by Giuseppe D'Aqui'
    email                : kumber@tiscalinet.it
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License, Version 2, as published by  *
 *   the Free Software Foundation.                                   *
 *                                                                         *
 ***************************************************************************/

#include "dephine.h"
#include "fonts/font_manager.h"
#include "surface_manager.h"
#include "sprite.h"
#include "menu_base_state.h"
#include <vector>


#ifndef MENU_H
#define MENU_H




class Menu_State : public Menu_Base_State
{
	


public:

	Menu_State();

	~Menu_State();

	void create();

	void update(double elapsed);

	void deinit();

	void draw();


};

#endif //MENU_H
