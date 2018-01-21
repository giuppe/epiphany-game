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
	
	m_back_replacement= new Surface();
	
	m_back_replacement->init(SDL_CreateRGBSurface(SDL_HWSURFACE, k_sprite_size+8, k_sprite_size+8, Screen::instance()->get_bpp(),0,0,0,0),0,0);
	
	
	m_pos.x=0;
	
	m_pos.y=0;
	
	m_move_to_pos.x=0;
	
	m_move_to_pos.y=0;
	
	m_state = SP_STOP;
	
	m_curr_frame=0;
	
	m_speed=1;
	
	m_initialized=true;
	
	m_total_frames = 8;
	
	this->set_is_changed();
	
	m_is_animating=false;
	
	
}



	
Sprite::~Sprite()
{
	if (m_initialized) {
		delete m_back_replacement;
	}
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
	set_is_changed();
}




void Sprite::set_pos_y(Uint32 pos_y)
{
	m_pos.y=pos_y;
	m_move_to_pos.y=pos_y;
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
	if(m_is_animating==true){
		set_curr_frame(m_curr_frame+1);
		set_is_changed();
	}

}



void Sprite::draw()
{
	update_frame();
	if(m_is_changed==true){
		
		this->put_screen(Screen::instance()->coord_to_screen(m_pos));
		m_is_changed=false;
	}
	
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

void Sprite::clear_bg(){
	if(m_is_changed==true){
		Screen* screen = Screen::instance(); 
		ScreenCoord screen_pos = screen->coord_to_screen(m_pos);
		screen->clear(screen_pos.x-2,screen_pos.y-2,36,36);
	}
}

void Sprite::update_bg(){
	if(m_is_changed==true){
		Screen* screen = Screen::instance(); 
		ScreenCoord screen_pos = screen->coord_to_screen(m_pos);
		SDL_Rect src_rect;
		src_rect.x=0;
		src_rect.y=0;
		src_rect.w=k_sprite_size+8;
		src_rect.h=k_sprite_size+8;
		screen_pos.x -= 4;
		screen_pos.y -= 4;
		m_back_replacement->put_screen(screen_pos,0);
		SDL_Surface* new_back = SDL_CreateRGBSurface(SDL_HWSURFACE, k_sprite_size+8, k_sprite_size+8, Screen::instance()->get_bpp(),0,0,0,0);
		
		screen->get_surface(new_back, &src_rect, screen_pos);
		delete m_back_replacement;
		m_back_replacement = new Surface();
		m_back_replacement->init(new_back, k_sprite_size+8, k_sprite_size+8);
	}
}

void Sprite::set_is_changed(){
	m_is_changed=true;
}
