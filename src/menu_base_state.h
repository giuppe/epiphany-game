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
#include "screen_state.h"
#include "fonts/font_manager.h"
#include "surface_manager.h"
#include "sprite.h"

#ifndef MENU_BASE_STATE_H
#define MENU_BASE_STATE_H

class Menu_List;

class Menu_List_Main;

class Menu_Entry;

class Menu_Base_State : public ScreenState
{
    protected:

        Font_Handle m_menu_font;

        Sprite m_selector;

        Surface* m_background;

        Menu_List* m_menu_list;


        void manage_input();

        void render_menu_list(Menu_List* menu_list, Sint32 menu_top_point, Sint32 menu_left_point, Sint32 menu_vertical_distance);
        
        void print_menu_background();
    
    public:
        Menu_Base_State();

        ~Menu_Base_State();

        void create();

        void update(double elapsed);

        void deinit();

        void draw();

};

#endif //MENU_BASE_STATE_H