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
 *   it under the terms of the GNU General Public License, Version 2, as published by  *
 *   the Free Software Foundation.                                   *
 *                                                                         *
 ***************************************************************************/

#include "epiconfig.h"
#include "tinyxml/tinyxml.h"


void Epiconfig::set_default_values()
{
	//size in pixels
	m_screen_size_x=640;
	m_screen_size_y=480;
	m_score_size_y=32;


	//size in cells
	m_map_size_x=32;
	m_map_size_y=32;

	//it must be a multiple of 2
	m_max_anim_drawn=8;



	m_moving_step=k_sprite_size/m_max_anim_drawn;

	//m_msec_per_frame=176/m_max_anim_drawn;
	m_msec_per_frame=150/m_max_anim_drawn;
	//m_msec_per_frame=240/m_max_anim_drawn;
	//m_msec_per_frame=120/m_max_anim_drawn;
	
	m_volume_sound = 128;
	
	m_volume_music = 128;
	
	refresh_game_window_parameters();
	
	
}




Uint32 Epiconfig::get_screen_size_x()
{
	return m_screen_size_x;
}




Uint32 Epiconfig::get_screen_size_y()
{
	return m_screen_size_y;
}




Uint32 Epiconfig::get_score_size_y()
{
	return m_score_size_y;
}




Uint32 Epiconfig::get_map_size_x()
{
	return m_map_size_x;
}




Uint32 Epiconfig::get_map_size_y()
{
	return m_map_size_y;
}




Uint32 Epiconfig::get_max_anim_drawn()
{
	return m_max_anim_drawn;
}




Uint32 Epiconfig::get_moving_step()
{
	return m_moving_step;
}




Uint32 Epiconfig::get_msec_per_frame()
{
	return m_msec_per_frame;
}




Uint32 Epiconfig::get_volume_sound()
{
	return m_volume_sound;
}




Uint32 Epiconfig::get_volume_music()
{
	return m_volume_music;
}




void Epiconfig::set_volume_sound(Uint32 volume)
{
	m_volume_sound = volume;
}


	

void Epiconfig::set_volume_music(Uint32 volume)
{
	m_volume_music = volume;
}



void Epiconfig::refresh_game_window_parameters()
{
   // m_level_size_x = m_game_size_x - 64;
   // m_level_size_y = m_level_size_y - 96;
    //m_game_window_pos_on_screen_x = 32;
    //m_game_window_pos_on_screen_y = 32;    
}




void Epiconfig::read_values_from_file(char* filename)
{

	TiXmlDocument doc;
	if(doc.LoadFile(filename))
	{
	
		TiXmlHandle docHandle( &doc );
		
		TiXmlText* screensize_x = docHandle.FirstChild("config").FirstChild("screen_size").FirstChild("x").FirstChild().Text();
		if(screensize_x)
		{
			m_screen_size_x = atoi(screensize_x->Value());
			DEBWARN("Setting Screen size x to: "<<m_screen_size_x);
		}

		TiXmlText* screensize_y = docHandle.FirstChild("config").FirstChild("screen_size").FirstChild("y").FirstChild().Text();
		if(screensize_y)
		{
			m_screen_size_y = atoi(screensize_y->Value());
			DEBWARN("Setting Screen size y to: "<<m_screen_size_y);
		}
	}
	else
	{
		DEBWARN("Unable to read file: "<<filename);
		set_default_values();
	}

    refresh_game_window_parameters();
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
