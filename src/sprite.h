/***************************************************************************
                          sprite.h  -  description
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
#include "surface_manager.h"

#ifndef SPRITE_H
#define SPRITE_H


enum Anim_Type{ SP_STOP=0,
				 SP_UP=k_max_anim,
				 SP_RIGHT=k_max_anim*2,
				 SP_DOWN=k_max_anim*3,
				 SP_LEFT=k_max_anim*4
				 /*, SP_EAT=k_max_anim*5*/};


class Sprite
{

private:

	Surface* m_surface;
	
//	CL_Surface* m_up_anim;
	
//	CL_Surface* m_right_anim;
	
//	CL_Surface* m_down_anim;
	
//	CL_Surface* m_left_anim;
	
//	CL_Surface* m_stop_surf;
	
//	CL_Surface* m_eat_anim;
	
	Uint32 m_pos_x;
	
	Uint32 m_pos_y;
	
	Uint32 m_move_to_pos_x;
	
	Uint32 m_move_to_pos_y;
	
	Uint32 m_step_x;

	Uint32 m_step_y;

	Uint32 m_speed;
		
	int m_curr_frame;
	
	bool m_initialized;

	Anim_Type m_state;	
	
	void put_screen(int pos_x, int pos_y, Uint32 size_x, Uint32 size_y, Uint32 frame_num);
	
	void set_curr_frame(int frame);
	
	void move(Uint32 n_pixel);
	
	
public:
	
	Sprite():m_initialized(false){};

	Sprite(Surface* surface);
	
	Sprite(const Sprite& sprite);
	
//	Sprite& operator=(const Sprite& sprite);
	
//	void set_surface(Anim_Type type);
	
	~Sprite();
	
	void set_speed(Uint32 speed);
	
	//CL_Surface* operator->();
	
	
	void put_screen(int pos_x, int pos_y, Uint32 size_x, Uint32 size_y);
	
	
	Uint32 get_pos_x()
	{
		return m_pos_x;
  	}
	
	Uint32 get_pos_y()
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
	
	int get_frame_number();
	
	void init(Surface* surf);
	
	void set_state(Anim_Type state);
		
};
	
#endif //SPRITE_H
