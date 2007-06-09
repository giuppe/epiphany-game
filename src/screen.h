/***************************************************************************
                          screen.h  -  Basic Screen Interface
                             -------------------
    begin                : Mon Oct 22 2001
    copyright            : (C) 2001 by Giuseppe D'Aquì
    email                : kumber@tiscalinet.it
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "dephine.h"
#include "sprite.h"
#include "iscreen.h"
#ifndef SCREEN_H
#define SCREEN_H


class Entity;

class Screen : public IScreen
{
private:
	Uint32 m_screen_size_x;
	Uint32 m_screen_size_y;
	Uint32 m_cell_size;
	
	Uint32 m_win_pos_x;
	Uint32 m_win_pos_y;
	Uint32 m_win_size_x;
	Uint32 m_win_size_y;
	
	
public:

	void init(Uint32 resolution_x, Uint32 resolution_y, Uint32 level_size_x, Uint32 level_size_y, Uint32 cell_size);
	
	
	void put(Sprite& sprite);
		
	void put(Entity* entity);
	
	Uint32 get_screen_size_x();
	
	Uint32 get_screen_size_y();
		
	void set_cell_size(Uint32 cell_size);
	
	void set_window_center(int cell_x, int cell_y);
	
	void clear();
	
	void flip_display();
	
	void draw_rect(int x, int y, Uint32 size_x, Uint32 size_y, float r, float g, float b, float alpha);
	
	void fill_rect(int x, int y, Uint32 size_x, Uint32 size_y, float r, float g, float b, float alpha);
	
// begin Singleton stuff

private:

    static Screen* _instance;

protected:

    Screen(): m_screen_size_x(0), m_screen_size_y(0), m_cell_size(0) {};

public:

    static Screen* instance();

// end Singleton stuff
	
	
};
	
#endif //SCREEN_H

