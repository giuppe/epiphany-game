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
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "dephine.h"

#ifndef EPICONFIG_H
#define EPICONFIG_H

class Epiconfig
{
private:
	unsigned int m_game_size_x;

	unsigned int m_game_size_y;

	unsigned int m_score_size_y;

//	int m_sprite_size;

	int m_level_size_x;

	int m_level_size_y;

	unsigned int m_max_anim_drawn;

//	unsigned int m_max_anim;

	unsigned int m_moving_step;

	unsigned int m_msec_per_frame;

public:

	void set_default_values();

	unsigned int get_game_size_x();

	unsigned int get_game_size_y();

	unsigned int get_score_size_y();

//	int get_sprite_size();

	int get_level_size_x();

	int get_level_size_y();

	unsigned int get_max_anim_drawn();

//	unsigned int get_max_anim();

	unsigned int get_moving_step();

	unsigned int get_msec_per_frame();
	
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

