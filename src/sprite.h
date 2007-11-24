/***************************************************************************
                          sprite.h  -  description
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
#include "surface.h"

#ifndef SPRITE_H
#define SPRITE_H


enum Anim_State{ SP_STOP=0,
				 SP_UP=k_max_anim,
				 SP_RIGHT=k_max_anim*2,
				 SP_DOWN=k_max_anim*3,
				 SP_LEFT=k_max_anim*4
				 /*, SP_EAT=k_max_anim*5*/};


class Sprite
{

private:

	Surface* m_surface;
	
	Uint32 m_pos_x;
	
	Uint32 m_pos_y;
	
	Uint32 m_move_to_pos_x;
	
	Uint32 m_move_to_pos_y;
	
	Uint32 m_step_x;

	Uint32 m_step_y;

	Uint32 m_speed;
		
	Uint32 m_curr_frame;
	
	bool m_initialized;

	Anim_State m_state;	
	
	Uint32 m_total_frames; 
	
	void put_screen(Sint32 pos_x, Sint32 pos_y, Uint32 size_x, Uint32 size_y, Uint32 frame_num);
	
	
	void set_curr_frame(Uint32 frame);
	
	void move(Uint32 n_pixel);
	
	Uint32 m_sprite_width;
	
	Uint32 m_sprite_height;
	
public:

	
	
	Sprite():m_initialized(false), m_total_frames(8){};

	Sprite(Surface* surface);
	
	Sprite(const Sprite& sprite);
	
	~Sprite();
	
	void set_speed(Uint32 speed);
		

	
	void put_screen(Sint32 pos_x, Sint32 pos_y, Uint32 size_x, Uint32 size_y);

		
	
	Uint32 get_pos_x() const
	{
		return m_pos_x;
  	}
	
	Uint32 get_pos_y() const
	{
		return m_pos_y;
 	}
 	
	void set_pos_x(Uint32 x);
	
	void set_pos_y(Uint32 y);
	
	void move_to_pos(Uint32 x, Uint32 y);
	
	void move_to_pos_x(Uint32 x);
	
	void move_to_pos_y(Uint32 y);
	
	void move();
	
	void update_frame();
	
	Uint32 get_frame_number() const;
	
	void init(Surface* surf);
	
	void set_state(Anim_State state);
	
	void draw();
		
};
	
#endif //SPRITE_H
