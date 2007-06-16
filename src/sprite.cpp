/***************************************************************************
                          sprite.cpp  -  description
                             -------------------
    begin                : Sat Sep 22 2001
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


Sprite::Sprite(Surface* surface)
{

	m_surface=surface;
	
	m_pos_x=0;
	
	m_pos_y=0;
	
	m_move_to_pos_x=0;
	
	m_move_to_pos_y=0;
	
	m_initialized=true;
	
	m_curr_frame=0;
	
	m_speed=1;
	
	m_state = SP_STOP;
	
	//FIXME: we should obtain this number from Surface
	m_total_frames = 8;
	
}

Sprite::Sprite(const Sprite& sprite)
{

	//DEBOUT("Entering Sprite cpyctor...\n");

//	CL_Surface temp=*(sprite.m_surface);

//	m_surface=new CL_Surface(temp);

	m_surface=sprite.m_surface;
	
	m_pos_x=sprite.m_pos_x;
	
	m_pos_y=sprite.m_pos_y;
	
	m_move_to_pos_x=sprite.m_move_to_pos_x;
	
	m_move_to_pos_y=sprite.m_move_to_pos_y;
	
	m_initialized=true;
	
	m_curr_frame=sprite.m_curr_frame;

	m_speed=sprite.m_speed;
	
	m_state = sprite.m_state;
	
	m_total_frames = sprite.m_total_frames;
	
}


void Sprite::init(Surface* surf)
{

	m_surface=surf;
	
	m_pos_x=0;
	
	m_pos_y=0;
	
	m_move_to_pos_x=0;
	
	m_move_to_pos_y=0;

	m_initialized=true;
	
	m_state = SP_STOP;
	
}
	
Sprite::~Sprite()
{
	
	
}
void Sprite::put_screen(Sint32 x, Sint32 y, Uint32 size_x, Uint32 size_y, Uint32 frame_num)
{
	m_surface->put_screen(x, y, (Sint32)size_x, (Sint32)size_y, (Sint32)frame_num);
}

void Sprite::put_screen(Sint32 x, Sint32 y, Uint32 size_x, Uint32 size_y)
{
	m_surface->put_screen(x, y, (Sint32)size_x, (Sint32)size_y, m_curr_frame+m_state);
}


void Sprite::set_pos_x(Uint32 pos_x)
{
	m_pos_x=pos_x;
	m_move_to_pos_x=pos_x;
}

void Sprite::set_pos_y(Uint32 pos_y)
{
	m_pos_y=pos_y;
	m_move_to_pos_y=pos_y;
}

void Sprite::set_curr_frame(Uint32 frame)
{
	//FIXME: check should be on number of sprite frames
	if(frame >= m_total_frames)
	{
		m_curr_frame = 0;
	}
	else
	{
		m_curr_frame=frame;
	}
}

void Sprite::set_speed(Uint32 speed)
{
	m_speed=speed;
}

void Sprite::move(Uint32 n_pixel)
{
	
	n_pixel*=m_speed;
	if(m_pos_x<m_move_to_pos_x)
	{
		if(m_pos_x+n_pixel>m_move_to_pos_x)
		{
			m_pos_x=m_move_to_pos_x;
		}
		else
		{
			m_pos_x+=n_pixel;
		}
	}
	else if(m_pos_x>m_move_to_pos_x)
	{
		if(m_pos_x-n_pixel<m_move_to_pos_x)
		{
			m_pos_x=m_move_to_pos_x;
		}
		else
		{
			m_pos_x-=n_pixel;
		}
	}

	if(m_pos_y<m_move_to_pos_y)
	{
		if(m_pos_y+n_pixel>m_move_to_pos_y)
		{
			m_pos_y=m_move_to_pos_y;
		}
		else
		{
			m_pos_y+=n_pixel;
		}
	}
	else if(m_pos_y>m_move_to_pos_y)
	{
		if(m_pos_y-n_pixel<m_move_to_pos_y)
		{
			m_pos_y=m_move_to_pos_y;
		}
		else
		{
			m_pos_y-=n_pixel;
		}
	}



}

void Sprite::move()
{
	
	Sint32 n_pixel = k_sprite_size/m_total_frames;
	
	n_pixel*=m_speed;
	if(m_pos_x!=m_move_to_pos_x)
	{
	if(m_pos_x<m_move_to_pos_x)
	{
		if(m_pos_x+n_pixel>m_move_to_pos_x)
		{
			m_pos_x=m_move_to_pos_x;
		}
		else
		{
			m_pos_x+=n_pixel;
		}
	}
	else
	{
		if(m_pos_x-n_pixel<m_move_to_pos_x)
		{
			m_pos_x=m_move_to_pos_x;
		}
		else
		{
			m_pos_x-=n_pixel;
		}
	}
	
	}

	if(m_pos_y!=m_move_to_pos_y)
	{

	if(m_pos_y<m_move_to_pos_y)
	{
		if(m_pos_y+n_pixel>m_move_to_pos_y)
		{
			m_pos_y=m_move_to_pos_y;
		}
		else
		{
			m_pos_y+=n_pixel;
		}
	}
	else
	{
		if(m_pos_y-n_pixel<m_move_to_pos_y)
		{
			m_pos_y=m_move_to_pos_y;
		}
		else
		{
			m_pos_y-=n_pixel;
		}
	}
	}



}

Uint32 Sprite::get_frame_number()
{

	return m_curr_frame;

}

void Sprite::set_state(Anim_State state)
{
	m_state=state;
}

void Sprite::move_to_pos(Uint32 x, Uint32 y)
{
	m_move_to_pos_x=x;
	m_move_to_pos_y=y;
}


void Sprite::move_to_pos_x(Uint32 x)
{
	m_move_to_pos_x=x;
}

void Sprite::move_to_pos_y(Uint32 y)
{
	m_move_to_pos_y=y;
}


void Sprite::update_frame()
{
	set_curr_frame(m_curr_frame+1);
}
