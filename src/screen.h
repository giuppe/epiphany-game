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

class Font;




class Screen
{
private:
	Uint32 m_world_size_x;
	Uint32 m_world_size_y;
	
	SDL_Surface* m_screen;
	
	SDL_Surface* m_virtual_screen;
	
	SDL_Rect m_camera;
	
	friend class Font;
	
	bool m_use_virtual_screen;
	
	SDL_Surface* get_screen();
	
	void blit_surface(SDL_Surface* surface, SDL_Rect* src, SDL_Rect* dest);


public:

	void init(Uint32 resolution_x, Uint32 resolution_y, Uint32 world_size_x, Uint32 world_size_y);
	
	void deinit();
	
	Uint8 get_bpp();
	

		

	Uint32 get_world_size_x();
	
	Uint32 get_world_size_y();
	

	void use_virtual_screen(){m_use_virtual_screen = true;}

	
	void set_camera_position(WorldCoord position);
	
	void clear();
	
	void clear(Uint32 x, Uint32 y, Uint32 w, Uint32 h);
	
	void flip_display();
	
	void draw_rect(Sint32 x, Sint32 y, Uint32 size_x, Uint32 size_y, Uint8 r, Uint8 g, Uint8 b);
	
	void fill_rect(Sint32 x, Sint32 y, Uint32 size_x, Uint32 size_y, Uint8 r, Uint8 g, Uint8 b);
	

	void blit_surface(SDL_Surface* surface, SDL_Rect* src, ScreenCoord dest);
	
	void blit_surface(SDL_Surface* surface, SDL_Rect* src, WorldCoord dest);
	
	void get_surface(SDL_Surface* surface, SDL_Rect* src, ScreenCoord dest);
	
	WorldCoord coord_to_world(ScreenCoord scr_coord);
	
	ScreenCoord coord_to_screen(WorldCoord wld_coord);
	
	void resize_world_screen(Uint32 size_x=0, Uint32 size_y=0);
	
// begin Singleton stuff

private:

    static Screen* _instance;

protected:

    Screen(): m_world_size_x(0), m_world_size_y(0), m_use_virtual_screen(false){};

public:

    static Screen* instance();

// end Singleton stuff
	
	
};
	
#endif //SCREEN_H

