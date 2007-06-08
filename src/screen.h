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
	unsigned int m_screen_size_x;
	unsigned int m_screen_size_y;
	unsigned int m_cell_size;
	
	unsigned int m_win_pos_x;
	unsigned int m_win_pos_y;
	unsigned int m_win_size_x;
	unsigned int m_win_size_y;
	
	
public:

	void init(unsigned int resolution_x, unsigned int resolution_y, unsigned int level_size_x, unsigned int level_size_y, unsigned int cell_size);
	
	Screen();
	
	//void put(Sprite& sprite, unsigned int pos_x, unsigned int pos_y);

	void put(Sprite& sprite);
		
	void put(Entity* entity);
	
	unsigned int get_screen_size_x();
	
	unsigned int get_screen_size_y();
	
//	void init(unsigned int resolution_x, unsigned int resolution_y, unsigned int level_size_x, unsigned int level_size_y, unsigned int cell_size);
	
	void set_cell_size(unsigned int cell_size);
	
	void set_window_center(int cell_x, int cell_y);
	
	void clear();
	
	void flip_display();
	
	void draw_rect(int x, int y, unsigned int size_x, unsigned int size_y, float r, float g, float b, float alpha);
	
	void fill_rect(int x, int y, unsigned int size_x, unsigned int size_y, float r, float g, float b, float alpha);
	
};
	
#endif //SCREEN_H

