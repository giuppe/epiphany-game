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



#ifndef SPRITE_H
#define SPRITE_H
#include "dephine.h"
#include "surface.h"
#include "world_coord.h"



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
	
	Surface* m_back_replacement;
	
	WorldCoord m_pos;
	
	WorldCoord m_old_pos;
	
	WorldCoord m_move_to_pos;
		
	Uint32 m_speed;
		
	Uint32 m_curr_frame;
	
	bool m_is_animating;
	
	bool m_is_changed;
	
	bool m_initialized;

	Anim_State m_state;	
	
	Uint32 m_total_frames; 
	
	void put_screen(ScreenCoord scr_coord, Uint32 frame_num);
	
	
	void set_curr_frame(Uint32 frame);
	
	void move(Uint32 n_pixel);
	
	Sprite(const Sprite& sprite);
	
	Sprite(Surface* surface);
 	
	void set_pos_x(Uint32 x);
	
	void set_pos_y(Uint32 y);
	
	
	void move_to_pos_x(Uint32 x);
	
	void move_to_pos_y(Uint32 y);
	
	void move_to_pos(Uint32 x, Uint32 y);
	
	void put_screen(ScreenCoord scr_coord);
	
	void update_frame();
	
	void set_is_changed();
	
public:

	
	
	Sprite():m_is_changed(true),m_initialized(false){};

	
	~Sprite();
	
	void set_speed(Uint32 speed);
	


	WorldCoord get_position() const;
	
	void set_position(WorldCoord pos);
	
	void move_to_position(WorldCoord pos);
	
	void move();
	
	void set_position_on_screen(ScreenCoord scr_coord);
	

	
	Uint32 get_frame_number() const;
	
	void init(Surface* surf);
	
	void set_state(Anim_State state);
	
	void draw();
	
	void clear_bg();
	
	void update_bg();
	
	void start_animation();
	
	void stop_animation();
	

		
};
	
#endif //SPRITE_H
