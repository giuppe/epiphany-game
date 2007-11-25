/***************************************************************************
                          sprite.cpp  -  description
                             -------------------
    begin                : Sat Sep 22 2001
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

#include "sprite.h"
#include "screen.h"


void Sprite::init(Surface* surf)
{

	m_surface=surf;
	
	m_pos.x=0;
	
	m_pos.y=0;
	
	m_move_to_pos.x=0;
	
	m_move_to_pos.y=0;
	
	m_state = SP_STOP;
	
	m_curr_frame=0;
	
	m_speed=1;
	
	m_initialized=true;
	
	m_total_frames = 8;
	
	
}



	
Sprite::~Sprite()
{
	
	
}




void Sprite::put_screen(ScreenCoord scr_coord, Uint32 frame_num)
{
	m_surface->put_screen(scr_coord, (Sint32)frame_num);
}




void Sprite::put_screen(ScreenCoord scr_coord)
{
	m_surface->put_screen(scr_coord, m_curr_frame+m_state);
}



void Sprite::set_pos_x(Uint32 pos_x)
{
	m_pos.x=pos_x;
	m_move_to_pos.x=pos_x;
}




void Sprite::set_pos_y(Uint32 pos_y)
{
	m_pos.y=pos_y;
	m_move_to_pos.y=pos_y;
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
	
	if(m_pos.x<m_move_to_pos.x)
	{
		if(m_pos.x+n_pixel>m_move_to_pos.x)
		{
			m_pos.x=m_move_to_pos.x;
		}
		else
		{
			m_pos.x+=n_pixel;
		}
	}
	else if(m_pos.x>m_move_to_pos.x)
	{
		if(m_pos.x-n_pixel<m_move_to_pos.x)
		{
			m_pos.x=m_move_to_pos.x;
		}
		else
		{
			m_pos.x-=n_pixel;
		}
	}

	if(m_pos.y<m_move_to_pos.y)
	{
		if(m_pos.y+n_pixel>m_move_to_pos.y)
		{
			m_pos.y=m_move_to_pos.y;
		}
		else
		{
			m_pos.y+=n_pixel;
		}
	}
	else if(m_pos.y>m_move_to_pos.y)
	{
		if(m_pos.y-n_pixel<m_move_to_pos.y)
		{
			m_pos.y=m_move_to_pos.y;
		}
		else
		{
			m_pos.y-=n_pixel;
		}
	}



}

void Sprite::move()
{
	
	Sint32 n_pixel = k_sprite_size/m_total_frames;
		
	move(n_pixel);

}

Uint32 Sprite::get_frame_number() const
{

	return m_curr_frame;

}

void Sprite::set_state(Anim_State state)
{
	m_state=state;
}

void Sprite::move_to_pos(Uint32 x, Uint32 y)
{
	m_move_to_pos.x=x;
	m_move_to_pos.y=y;
}


void Sprite::move_to_pos_x(Uint32 x)
{
	m_move_to_pos.x=x;
}

void Sprite::move_to_pos_y(Uint32 y)
{
	m_move_to_pos.y=y;
}


void Sprite::update_frame()
{
	set_curr_frame(m_curr_frame+1);
}



void Sprite::draw()
{

	this->put_screen(Screen::instance()->coord_to_screen(m_pos));

	
}


WorldCoord Sprite::get_position() const
{
	return m_pos;
}
	
void Sprite::set_position(WorldCoord pos)
{
	set_pos_x(pos.x);
	set_pos_y(pos.y);
}
	
void Sprite::move_to_position(WorldCoord pos)
{
	move_to_pos(pos.x, pos.y);
}
