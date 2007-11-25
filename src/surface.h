/***************************************************************************
                          surface.h  -  description
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



#ifndef SURFACE_H_
#define SURFACE_H_
#include "dephine.h"
#include <SDL/SDL.h>


//typedef CL_Surface Surface;


struct ScreenCoord;

class Surface
{
private:
	
	struct Frame
	{
		SDL_Surface* image;
		Uint32 pause;
	};
	
	//SDL_Surface* m_surface;
	
	Uint32 m_frame_size_x;
	
	Uint32 m_frame_size_y;
	
	Frame* m_surfaces;
	
	Uint32 m_num_frames;
	
	bool m_is_inited;
	
public:

	Surface():m_frame_size_x(0), m_frame_size_y(0), m_is_inited(false){};
	
	//Surface(SDL_Surface* surface):m_surface(surface), m_frame_size_x(0), m_frame_size_y(0){};

	void put_screen(ScreenCoord scr_coord, int frame_no=-1);
	
	void init(SDL_Surface* surface, Uint32 frame_size_x=32, Uint32 frame_size_y=32);
	
	~Surface();
	
};



#endif /*SURFACE_H_*/
