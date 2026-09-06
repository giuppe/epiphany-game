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


void Sprite::start_animation()
{
	m_is_animating=true;
}

void Sprite::stop_animation()
{
	m_is_animating=false;
}

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

	m_offset.x = 0.0;
	m_offset.y = 0.0;
	
	this->set_is_changed();
	
	m_is_animating=false;
	
	
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
	ScreenCoord final_coord;
	final_coord.x = scr_coord.x + m_offset.x;
	final_coord.y = scr_coord.y + m_offset.y;
	m_surface->put_screen(final_coord, m_curr_frame+m_state);
}



void Sprite::set_pos_x(Uint32 pos_x)
{
	m_pos.x=pos_x;
	m_move_to_pos.x=pos_x;
	set_is_changed();
}




void Sprite::set_pos_y(Uint32 pos_y)
{
	m_pos.y=pos_y;
	m_move_to_pos.y=pos_y;
	set_is_changed();
}


void Sprite::set_offset_x(Sint32 x)
{
	m_offset.x=x;
	set_is_changed();
}

void Sprite::set_offset_y(Sint32 y)
{
	m_offset.y=y;
	set_is_changed();
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
	set_is_changed();
}




void Sprite::set_speed(Uint32 speed)
{
	m_speed=speed;
}




void Sprite::move(Uint32 n_pixel)
{
	
	if(n_pixel==0){
		return;
	}
	
	m_old_pos=m_pos;
	n_pixel*=m_speed;
	
	if((m_pos.x != m_move_to_pos.x)&&(m_pos.y!=m_move_to_pos.y)){
		set_is_changed();
	}
	
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
	if(m_state!=state){
		m_state=state;
		set_is_changed();
	}
}

void Sprite::move_to_pos(Uint32 x, Uint32 y)
{
	m_move_to_pos.x=x;
	m_move_to_pos.y=y;
	set_is_changed();
}


void Sprite::move_to_pos_x(Uint32 x)
{
	m_move_to_pos.x=x;
	set_is_changed();
}

void Sprite::move_to_pos_y(Uint32 y)
{
	m_move_to_pos.y=y;
	set_is_changed();
}


void Sprite::update_frame()
{
	Uint64 current_time = SDL_GetTicks64();
	if(m_is_animating && current_time-m_time_of_last_frame > frame_duration*1000){
		set_curr_frame(m_curr_frame+1);
		set_is_changed();
		m_time_of_last_frame = current_time;
	}

}



void Sprite::draw()
{
	update_frame();
	//if(m_is_changed==true){
		
		this->put_screen(Screen::instance()->coord_to_screen(m_pos));
		m_is_changed=false;
	//}
	
}


WorldCoord Sprite::get_position() const
{
	return m_pos;
}
	
void Sprite::set_position(WorldCoord pos)
{
	if((pos.x == this->m_pos.x)&&(pos.y== this->m_pos.y)){
		return;
	}
	set_pos_x(pos.x);
	set_pos_y(pos.y);
	set_is_changed();
}

void Sprite::set_position_on_screen(ScreenCoord pos)
{
	WorldCoord wld = Screen::instance()->coord_to_world(pos);
	set_pos_x(wld.x);
	set_pos_y(wld.y);
	set_is_changed();
}
	
void Sprite::move_to_position(WorldCoord pos)
{
	if((pos.x == this->m_pos.x)&&(pos.y== this->m_pos.y)){
		return;
	}
	move_to_pos(pos.x, pos.y);
	set_is_changed();
}


void Sprite::set_is_changed(){
	m_is_changed=true;
}
