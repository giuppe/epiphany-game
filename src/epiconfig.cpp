/***************************************************************************
                          epiconfig.cpp  -  description
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

#include "epiconfig.h"


void Epiconfig::set_default_values()
{
	//size in pixels
	m_game_size_x=640;
	m_game_size_y=480;
	m_score_size_y=32;

	//size in cells
	m_level_size_x=32;
	m_level_size_y=32;

	//it must be a multiple of 2
	m_max_anim_drawn=4;



	m_moving_step=k_sprite_size/m_max_anim_drawn;

	//m_msec_per_frame=176/m_max_anim_drawn;
	m_msec_per_frame=150/m_max_anim_drawn;
}

unsigned int Epiconfig::get_game_size_x()
{
	return m_game_size_x;
}

unsigned int Epiconfig::get_game_size_y()
{
	return m_game_size_y;
}

unsigned int Epiconfig::get_score_size_y()
{
	return m_score_size_y;
}
/*
int Epiconfig::get_sprite_size()
{
	return m_sprite_size;
}
*/
int Epiconfig::get_level_size_x()
{
	return m_level_size_x;
}

int Epiconfig::get_level_size_y()
{
	return m_level_size_y;
}

unsigned int Epiconfig::get_max_anim_drawn()
{
	return m_max_anim_drawn;
}
/*
unsigned int Epiconfig::get_max_anim()
{
	return m_max_anim;
}
*/
unsigned int Epiconfig::get_moving_step()
{
	return m_moving_step;
}

unsigned int Epiconfig::get_msec_per_frame()
{
	return m_msec_per_frame;
}



// begin Singleton stuff

Epiconfig* Epiconfig::_instance = 0;

Epiconfig* Epiconfig::instance()
{
	if (_instance == 0)
	{
		_instance = new Epiconfig;
	}
	return _instance;
}

//end Singleton stuff
