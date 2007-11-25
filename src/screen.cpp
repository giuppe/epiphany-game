/***************************************************************************
                          screen.cpp  -  description
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
#include "dephine.h"
#include <SDL/SDL.h>
#include <cassert>
#include "screen.h"
#include "sprite.h"
#include "entity.h"



Uint32 Screen::get_game_size_x()
{
	return m_game_size_x;
	
}




Uint32 Screen::get_game_size_y()
{

	return m_game_size_y;
	
}


SDL_Surface* Screen::get_screen()
{
	return m_screen;
}


void Screen::init(Uint32 resolution_x, Uint32 resolution_y, Uint32 level_size_x, Uint32 level_size_y)
{
	m_camera.x=0;
	m_camera.y=0;
	m_camera.w=resolution_x;
	m_camera.h=resolution_y-Epiconfig::instance()->get_score_size_y();

	
	m_game_size_x=level_size_x;
	m_game_size_y=level_size_y;
	
	m_screen = SDL_SetVideoMode(resolution_x, resolution_y, 0, SDL_HWSURFACE|SDL_DOUBLEBUF);
	if(m_screen == NULL)
	{
		printf("Unable to set %d x %d video mode: %s\n", resolution_x, resolution_y, SDL_GetError());
		exit(1);
	}
	
	
	
	m_game_screen = SDL_CreateRGBSurface(SDL_HWSURFACE, m_game_size_x, m_game_size_y, this->get_bpp(),0,0,0,0);
	
}


void Screen::resize_virtual_screen(Uint32 size_x, Uint32 size_y)
{
	if(m_use_virtual_screen)
	{
		m_game_screen = SDL_CreateRGBSurface(SDL_HWSURFACE, size_x, size_y, this->get_bpp(),0,0,0,0);
		m_game_size_x=size_x;
		m_game_size_y=size_y;
	}
}


Uint8 Screen::get_bpp()
{
	return SDL_GetVideoInfo()->vfmt->BitsPerPixel;
}




ScreenCoord Screen::coord_to_screen(WorldCoord wld_coord)
{
	ScreenCoord scr;
	scr.x = wld_coord.x - m_camera.x;
	scr.y = wld_coord.y - m_camera.y;
	return scr;
}

WorldCoord Screen::coord_to_world(ScreenCoord scr_coord)
{
	WorldCoord wld;
	wld.x = scr_coord.x + m_camera.x;
	wld.y = scr_coord.y + m_camera.y;
	return wld;
}


void Screen::put(Surface& surface, WorldCoord wld_coord)
{
	put(surface, coord_to_screen(wld_coord));
	
	
}

void Screen::put(Surface& surface, ScreenCoord scr_coord)
{
	surface.put_screen(scr_coord);
}





void Screen::set_camera_position(WorldCoord position)
{

	if(position.x>(m_camera.w/2))
	{
		if((position.x+(m_camera.w/2))<m_game_size_x)
		{
			m_camera.x=(position.x-(m_camera.w/2));
		}	
		else
		{
			m_camera.x=(m_game_size_x-(m_camera.w));
		}
	}
	else
	{
		m_camera.x=0;
	}
		
	if(position.y>(m_camera.h/2))
	{
		if((position.y+(m_camera.h/2))<m_game_size_y)
		{
			m_camera.y=(position.y-(m_camera.h/2));
		}	
		else
		{
			m_camera.y=(m_game_size_y-(m_camera.h));
		}
	}
	else
	{
		m_camera.y=0;
	}

//	if((x>(m_win_size_x/2))&&((x+(m_win_size_x/2))<m_screen_size_x))
//		m_win_pos_x=(x-(m_win_size_x/2));
		
//	if((y>(m_win_size_y/2))&&((y+(m_win_size_y/2))<m_screen_size_y))
//		m_win_pos_y=(y-(m_win_size_y/2));
}




void Screen::clear()
{
	SDL_Surface* dest_surf = m_screen;
	if(m_use_virtual_screen)
	{
		dest_surf = m_game_screen;
	}
	SDL_FillRect(dest_surf, NULL, SDL_MapRGB(dest_surf->format, 0, 0, 0));
}	




void Screen::flip_display()
{

	if(m_use_virtual_screen)
	{
		SDL_BlitSurface(m_game_screen, &m_camera, m_screen, NULL);
	}
	SDL_Flip(m_screen);
}




void Screen::fill_rect(Sint32 x, Sint32 y, Uint32 size_x, Uint32 size_y, Uint8 r, Uint8 g, Uint8 b)
{
	SDL_Rect dest;
	dest.x = x;
	dest.y = y;
	dest.w = size_x;
	dest.h = size_y;
	SDL_FillRect(m_screen, &dest, SDL_MapRGB(m_screen->format, r, g, b));
}





void Screen::draw_rect(Sint32 x, Sint32 y, Uint32 size_x, Uint32 size_y, Uint8 r, Uint8 g, Uint8 b)
{
	assert(!"Error: Screen::draw_rect() not implemented.");
	/*
	SDL_Rect dest;
	dest.x = x;
	dest.y = y;
	dest.w = size_x;
	dest.h = size_y;
	SDL_FillRect(m_screen, &dest, SDL_MapRGB(m_screen->format, r, g, b));
	*/
}


void Screen::blit_surface(SDL_Surface* surface, SDL_Rect* src, SDL_Rect* dest)
{
	SDL_Surface* dest_surf = m_screen;
	if(m_use_virtual_screen)
	{
		dest_surf = m_game_screen;
	}
	SDL_BlitSurface(surface, src,  dest_surf, dest);
}

void Screen::blit_surface(SDL_Surface* surface, SDL_Rect* src, ScreenCoord dest)
{
	SDL_Rect rect_dest;
	rect_dest.x=dest.x;
	rect_dest.y=dest.y;
	blit_surface(surface, src,&rect_dest);
}

void Screen::blit_surface(SDL_Surface* surface, SDL_Rect* src, WorldCoord dest)
{
	SDL_Rect rect_dest;
	ScreenCoord dest_screen = this->coord_to_screen(dest);
	rect_dest.x=dest_screen.x;
	rect_dest.y=dest_screen.y;
	blit_surface(surface, src,&rect_dest);
}

void Screen::deinit()
{
	SDL_FreeSurface(m_game_screen);
}

// begin Singleton stuff

Screen* Screen::_instance = 0;

Screen* Screen::instance()
{
	if (_instance == 0)
	{
		_instance = new Screen();
		
	}
	return _instance;
}

//end Singleton stuff
