/***************************************************************************
                          screen.cpp  -  description
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
#include <SDL/SDL.h>
#include "screen.h"
#include "sprite.h"
#include "entity.h"



Uint32 Screen::get_screen_size_x()
{
	return m_screen_size_x;
	
}

Uint32 Screen::get_screen_size_y()
{

	return m_screen_size_y;
	
}

void Screen::init(Uint32 resolution_x, Uint32 resolution_y, Uint32 level_size_x, Uint32 level_size_y, Uint32 cell_size)
{
	m_win_pos_x=0;
	m_win_pos_y=0;
	m_win_size_x=resolution_x;
	m_win_size_y=resolution_y-Epiconfig::instance()->get_score_size_y();
	m_cell_size=cell_size;
	
	m_screen_size_x=level_size_x*m_cell_size;
	m_screen_size_y=level_size_y*m_cell_size;
	
	m_screen = SDL_SetVideoMode(resolution_x, resolution_y, 0, SDL_HWSURFACE|SDL_DOUBLEBUF);
	if(m_screen == NULL)
	{
		printf("Unable to set %d x %d video mode: %s\n", resolution_x, resolution_y, SDL_GetError());
	}
}


void Screen::put(Sprite& sprite)
{
	int curr_pos_x=sprite.get_pos_x();
	int curr_pos_y=sprite.get_pos_y();
/*	if(	((curr_pos_x+48>m_win_pos_x)&&
			(curr_pos_x<(m_win_pos_x+m_win_size_x)))&&
			((curr_pos_y+48>m_win_pos_y)&&
			(curr_pos_y<(m_win_pos_y+m_win_size_y))))*/
	{
//	DEBOUT("drawing sprite at: "<<curr_pos_x<<", "<<curr_pos_y<<"\n");
	//int frame=sprite.get_frame_number();
	//sprite.put_screen((int)(curr_pos_x-m_win_pos_x), (int)(curr_pos_y-m_win_pos_y), (int)m_cell_size, (int)m_cell_size, frame);
	sprite.put_screen((int)(curr_pos_x-m_win_pos_x), (int)(curr_pos_y-m_win_pos_y), (int)m_cell_size, (int)m_cell_size);
	}
	
}

void Screen::set_cell_size(Uint32 cell_size)
{
	
	m_cell_size=cell_size;
	
}

void Screen::set_window_center(int x, int y)
{

	if(x>(m_win_size_x/2))
	{
		if((x+(m_win_size_x/2))<m_screen_size_x)
		{
			m_win_pos_x=(x-(m_win_size_x/2));
		}	
		else
		{
			m_win_pos_x=(m_screen_size_x-(m_win_size_x));
		}
	}
	else
	{
		m_win_pos_x=0;
	}
		
	if(y>(m_win_size_y/2))
	{
		if((y+(m_win_size_y/2))<m_screen_size_y)
		{
			m_win_pos_y=(y-(m_win_size_y/2));
		}	
		else
		{
			m_win_pos_y=(m_screen_size_y-(m_win_size_y));
		}
	}
	else
	{
		m_win_pos_y=0;
	}

//	if((x>(m_win_size_x/2))&&((x+(m_win_size_x/2))<m_screen_size_x))
//		m_win_pos_x=(x-(m_win_size_x/2));
		
//	if((y>(m_win_size_y/2))&&((y+(m_win_size_y/2))<m_screen_size_y))
//		m_win_pos_y=(y-(m_win_size_y/2));
}

void Screen::clear()
{
	SDL_FillRect(m_screen, NULL, SDL_MapRGB(m_screen->format, 0, 0, 0));
}	

void Screen::flip_display()
{
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
	/*
	SDL_Rect dest;
	dest.x = x;
	dest.y = y;
	dest.w = size_x;
	dest.h = size_y;
	SDL_FillRect(m_screen, &dest, SDL_MapRGB(m_screen->format, r, g, b));
	*/
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
