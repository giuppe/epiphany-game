/***************************************************************************
                          epiconfig.h  -  description
                             -------------------
    begin                : Mon Sep 29 2003
    copyright            : (C) 2003 by Giuseppe D'Aqui'
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

#ifndef EPICONFIG_H
#define EPICONFIG_H

class Epiconfig
{
private:
	Uint32 m_screen_size_x;

	Uint32 m_screen_size_y;

	Uint32 m_score_size_y;

//	int m_sprite_size;

	Uint32 m_map_size_x;

	Uint32 m_map_size_y;

	Uint32 m_max_anim_drawn;

//	Uint32 m_max_anim;

	Uint32 m_moving_step;

	Uint32 m_msec_per_frame;
	
	Uint32 m_volume_sound;
	
	Uint32 m_volume_music;

public:

	void set_default_values();

	Uint32 get_screen_size_x();

	Uint32 get_screen_size_y();

	Uint32 get_score_size_y();

//	int get_sprite_size();

	Uint32 get_map_size_x();

	Uint32 get_map_size_y();

	Uint32 get_max_anim_drawn();

//	Uint32 get_max_anim();

	Uint32 get_moving_step();

	Uint32 get_msec_per_frame();
	
	Uint32 get_volume_sound();
	
	Uint32 get_volume_music();
	
	void set_volume_sound(Uint32 volume);
	
	void set_volume_music(Uint32 volume);
	
	void read_values_from_file(char* filename);
	
	void refresh_game_window_parameters();
	
// begin Singleton stuff

private:

	static Epiconfig* _instance;

protected:

	Epiconfig(){};

public:

	static Epiconfig* instance();

// end Singleton stuff

};

#endif //EPICONFIG_H

