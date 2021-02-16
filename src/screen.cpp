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
#include <SDL2/SDL.h>
#include <cassert>
#include "screen.h"
#include "sprite.h"
#include "entity.h"



Uint32 Screen::get_world_size_x()
{
	return m_world_size_x;
	
}




Uint32 Screen::get_world_size_y()
{

	return m_world_size_y;
	
}


SDL_Surface* Screen::get_screen()
{
	return m_virtual_screen;
}

SDL_Renderer* Screen::get_renderer()
{
	return m_renderer;
}

SDL_Surface* Screen::convert_surface_format(SDL_Surface* surface){
	SDL_Surface* temp = SDL_CreateRGBSurface(0, surface->w, surface->h, 32,
											0x00FF0000,
											0x0000FF00,
											0x000000FF,
											0xFF000000);
	SDL_BlitSurface(surface, NULL, temp, NULL);
	return temp;
}


void Screen::init(Uint32 resolution_x, Uint32 resolution_y, Uint32 world_size_x, Uint32 world_size_y)
{
	m_camera.x=0;
	m_camera.y=0;
	m_camera.w=resolution_x;
	m_camera.h=resolution_y-Epiconfig::instance()->get_score_size_y();

	
	m_world_size_x=world_size_x;
	m_world_size_y=world_size_y;
	
	m_window = SDL_CreateWindow("My Game Window",
                          SDL_WINDOWPOS_UNDEFINED,
                          SDL_WINDOWPOS_UNDEFINED,
                          resolution_x, resolution_y,
                          SDL_WINDOW_SHOWN);

	//m_screen = SDL_SetVideoMode(resolution_x, resolution_y, 0, SDL_HWSURFACE|SDL_DOUBLEBUF);
	if(m_window == NULL)
	{
		printf("Unable to set %d x %d video mode: %s\n", resolution_x, resolution_y, SDL_GetError());
		exit(1);
	}

	m_renderer = SDL_CreateRenderer(m_window, -1, 0);

	m_virtual_screen = SDL_CreateRGBSurface(0, resolution_x, resolution_y, 32,
											0x00FF0000,
											0x0000FF00,
											0x000000FF,
											0xFF000000);
	m_screen = SDL_CreateTexture(m_renderer,
								 SDL_PIXELFORMAT_ARGB8888,
								 SDL_TEXTUREACCESS_STREAMING,
								 resolution_x, resolution_y);
}


void Screen::resize_world_screen(Uint32 size_x, Uint32 size_y)
{
	if((size_x==0)||(size_y==0))
	{
		size_x = m_virtual_screen->w;
		size_y = m_virtual_screen->h;
	}
	
	
	m_virtual_screen = SDL_CreateRGBSurface(0, size_x, size_y, 32,
                                        0x00FF0000,
                                        0x0000FF00,
                                        0x000000FF,
                                        0xFF000000);
		
	
	
	m_world_size_x=size_x;
	m_world_size_y=size_y;
}


void Screen::set_window_title(const char* title)
{
	SDL_SetWindowTitle(m_window, title);
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


void Screen::set_camera_position(WorldCoord position)
{
	
	if(position.x>(m_camera.w/2))
	{
		if((position.x+(m_camera.w/2))<m_world_size_x)
		{
			m_camera.x=(position.x-(m_camera.w/2));
		}	
		else
		{
			//m_camera.x=(m_world_size_x-(m_camera.w));
			//patch by stefan
			m_camera.x = ((m_world_size_x>m_camera.w?m_world_size_x:m_camera.w)-(m_camera.w));
		}
	}
	else
	{
		m_camera.x=0;
	}
		
	if(position.y>(m_camera.h/2))
	{
		if((position.y+(m_camera.h/2))<m_world_size_y)
		{
			m_camera.y=(position.y-(m_camera.h/2));
		}	
		else
		{
			//m_camera.y=(m_world_size_y-(m_camera.h));
			// patch by stefan
			m_camera.y=((m_world_size_y>m_camera.h?m_world_size_y:m_camera.h)-(m_camera.h));
		}
	}
	else
	{
		m_camera.y=0;
	}


}




void Screen::clear()
{
	SDL_Surface* dest_surf = m_virtual_screen;
	
	SDL_FillRect(dest_surf, NULL, SDL_MapRGB(dest_surf->format, 0, 0, 0));
}	


void Screen::clear(Uint32 x, Uint32 y, Uint32 w, Uint32 h)
{
	SDL_Surface* dest_surf = m_virtual_screen;
	SDL_Rect dest_rect;
	dest_rect.x=x;
	dest_rect.y=y;
	dest_rect.w=w;
	dest_rect.h=h;
	
	
	SDL_FillRect(dest_surf, &dest_rect, SDL_MapRGB(dest_surf->format, 0, 0, 0));
}	



void Screen::flip_display()
{
	SDL_LockSurface(m_virtual_screen);
	SDL_UpdateTexture(m_screen, NULL, m_virtual_screen->pixels, m_virtual_screen->pitch);
	SDL_RenderClear(m_renderer);
	SDL_RenderCopy(m_renderer, m_screen, NULL, NULL);
	SDL_RenderPresent(m_renderer);
	SDL_UnlockSurface(m_virtual_screen);
}




void Screen::fill_rect(Sint32 x, Sint32 y, Uint32 size_x, Uint32 size_y, Uint8 r, Uint8 g, Uint8 b)
{
	SDL_Rect dest;
	dest.x = x;
	dest.y = y;
	dest.w = size_x;
	dest.h = size_y;
	SDL_FillRect(m_virtual_screen, &dest, SDL_MapRGB(m_virtual_screen->format, r, g, b));
}





void Screen::draw_rect(Sint32 x, Sint32 y, Uint32 size_x, Uint32 size_y, Uint8 r, Uint8 g, Uint8 b)
{
	assert(!"Error: Screen::draw_rect() not implemented.");

}


void Screen::blit_surface(SDL_Surface* surface, SDL_Rect* src, SDL_Rect* dest)
{
	SDL_Surface* dest_surf = m_virtual_screen;
	
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

void Screen::get_surface(SDL_Surface* surface, SDL_Rect* src, ScreenCoord dest)
{
	SDL_Rect rect_dest;
	rect_dest.x=dest.x;
	rect_dest.y=dest.y;
	SDL_Surface* src_surf = m_virtual_screen;
	SDL_Surface* dest_surf = surface;
	
	SDL_BlitSurface(src_surf, src,  dest_surf, &rect_dest);
	
}

void Screen::deinit()
{
	SDL_FreeSurface(m_virtual_screen);
	SDL_DestroyTexture(m_screen);
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
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
