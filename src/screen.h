/***************************************************************************
                          screen.h  -  Basic Screen Interface
                             -------------------
    begin                : Mon Oct 22 2001
    copyright            : (C) 2001 by Giuseppe D'Aqu�
    email                : kumber@tiscalinet.it
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License, Version 2, as published by  *
 *   the Free Software Foundation.                                   *
 *                                                                         *
 ***************************************************************************/



#ifndef SCREEN_H
#define SCREEN_H
#include "dephine.h"
#include "sprite.h"
#include "world_coord.h"
#include "screen_coord.h"

class Entity;






class Screen
{
private:
	Uint32 m_screen_size_x;
	Uint32 m_screen_size_y;
	Uint32 m_cell_size;
	
	SDL_Surface* m_screen;
	
	SDL_Surface* m_game_screen;
	
	SDL_Rect m_camera;
	
public:

	void init(Uint32 resolution_x, Uint32 resolution_y, Uint32 level_size_x, Uint32 level_size_y, Uint32 cell_size);
	
	Uint8 get_bpp();
	
	void put(Sprite& sprite);
		
	//void put(Entity* entity);
	
	//void put(Surface* surface, Sint32 x, Sint32 y);
	

	void put(Surface& surface, ScreenCoord scr_coord);
	
	void put(Surface& surface, WorldCoord wld_coord);
	
	Uint32 get_screen_size_x();
	
	Uint32 get_screen_size_y();
	
	Uint32 get_win_pos_x();
	
	Uint32 get_win_pos_y();
	
	Uint32 get_win_size_x();
	
	Uint32 get_win_size_y();
	
	Uint32 get_cell_size()
	{
		return m_cell_size;
	}
		
	void set_cell_size(Uint32 cell_size);
	
	void set_window_center(Uint32 cell_x, Uint32 cell_y);
	
	void clear();
	
	void flip_display();
	
	void draw_rect(Sint32 x, Sint32 y, Uint32 size_x, Uint32 size_y, Uint8 r, Uint8 g, Uint8 b);
	
	void fill_rect(Sint32 x, Sint32 y, Uint32 size_x, Uint32 size_y, Uint8 r, Uint8 g, Uint8 b);
	
	SDL_Surface* get_screen(){return m_screen;}
	
	WorldCoord coord_to_world(ScreenCoord scr_coord);
	
	ScreenCoord coord_to_screen(WorldCoord wld_coord);
	
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

