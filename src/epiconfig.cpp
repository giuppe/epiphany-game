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
#include <cstdlib>
#include "sprite.h"


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
	
	m_volume_sound = 8;
	
	m_volume_music = 8;
	
	m_last_level = 0;
	
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




Uint32 Epiconfig::get_last_level()
{
	return m_last_level;
}




void Epiconfig::set_last_level(Uint32 level)
{
	m_last_level = level;
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
	
	set_default_values();

	TiXmlDocument doc;
	
	
	if(doc.LoadFile(filename))
	{
	
		TiXmlHandle docHandle( &doc );
		
		TiXmlText* screensize_x = docHandle.FirstChild("config").FirstChild("screen_size").FirstChild("x").FirstChild().Text();
		if(screensize_x)
		{
			m_screen_size_x = atoi(screensize_x->Value());
			DEBWARN("Setting Screen size x to: "<<m_screen_size_x<<"\n");
		}

		TiXmlText* screensize_y = docHandle.FirstChild("config").FirstChild("screen_size").FirstChild("y").FirstChild().Text();
		if(screensize_y)
		{
			m_screen_size_y = atoi(screensize_y->Value());
			DEBWARN("Setting Screen size y to: "<<m_screen_size_y<<"\n");
		}
		
		TiXmlText* last_level = docHandle.FirstChild("user").FirstChild("last_level").FirstChild().Text();
		if(last_level)
		{
			m_last_level = atoi(last_level->Value());
			DEBWARN("Setting last level to: "<<m_last_level<<"\n");
		}
		
		TiXmlText* sound_volume = docHandle.FirstChild("config").FirstChild("sound_volume").FirstChild().Text();
		if(sound_volume)
		{
			m_volume_sound = atoi(sound_volume->Value());
			DEBWARN("Setting sound volume to: "<<m_volume_sound<<"\n");
		}

		TiXmlText* music_volume = docHandle.FirstChild("config").FirstChild("music_volume").FirstChild().Text();
		if(music_volume)
		{
			m_volume_music = atoi(music_volume->Value());
			DEBWARN("Setting music volume to: "<<m_volume_music<<"\n");
		}

		
	}
	else
	{
		DEBWARN("Unable to read file: "<<filename<<"\n");
		
		//set_default_values();
	}

    refresh_game_window_parameters();
}



void Epiconfig::save_values_to_file(char* filename)
{
	

	TiXmlDocument doc;
	
	TiXmlDeclaration * decl = new TiXmlDeclaration( "1.0", "", "" );
	
	doc.LinkEndChild( decl );
	
	TiXmlElement * e_config = new TiXmlElement( "config" );
	doc.LinkEndChild( e_config );
	
	TiXmlElement * e_screen = new TiXmlElement( "screen_size" );
	e_config->LinkEndChild( e_screen );
	
	TiXmlElement * e_screen_x = new TiXmlElement( "x" );
	e_screen->LinkEndChild( e_screen_x );
	
	TiXmlElement * e_screen_y = new TiXmlElement( "y" );
	e_screen->LinkEndChild( e_screen_y );
	
	TiXmlElement * e_user = new TiXmlElement( "user" );
	doc.LinkEndChild( e_user );
	
	TiXmlElement * e_last_level = new TiXmlElement( "last_level" );
	e_user->LinkEndChild( e_last_level );
	
	TiXmlElement * e_sound_volume = new TiXmlElement( "sound_volume" );
	e_config->LinkEndChild( e_sound_volume );
	
	TiXmlElement * e_music_volume = new TiXmlElement( "music_volume" );
	e_config->LinkEndChild( e_music_volume );
	
	char* text_screen_size_x = new char[10];
	
	char* text_screen_size_y = new char[10];
	
	char* text_last_level = new char[10];
	
	sprintf(text_last_level, "%d", m_last_level);
	
	sprintf(text_screen_size_x, "%d", m_screen_size_x);
	
	sprintf(text_screen_size_y, "%d", m_screen_size_y);
	
	
	char* text_sound_volume = new char[10];
	
	sprintf(text_sound_volume, "%d", m_volume_sound);
	
	char* text_music_volume = new char[10];
	
	sprintf(text_music_volume, "%d", m_volume_music);
	
	TiXmlText * screen_x = new TiXmlText( text_screen_size_x );
	e_screen_x->LinkEndChild( screen_x );
	
	TiXmlText * screen_y = new TiXmlText( text_screen_size_y );
	e_screen_y->LinkEndChild( screen_y );
	
	TiXmlText * last_level = new TiXmlText( text_last_level );
	e_last_level->LinkEndChild( last_level );
	
	e_sound_volume->LinkEndChild( new TiXmlText( text_sound_volume ) );
	
	e_music_volume->LinkEndChild( new TiXmlText( text_music_volume ) );
	
	doc.SaveFile( filename );
	
	/*
	if(doc.LoadFile(filename))
	{
	
		TiXmlHandle docHandle( &doc );
		
		TiXmlText* screensize_x = docHandle.FirstChild("config").FirstChild("screen_size").FirstChild("x").FirstChild().Text();
		if(screensize_x)
		{
			m_screen_size_x = atoi(screensize_x->Value());
			DEBWARN("Setting Screen size x to: "<<m_screen_size_x<<"\n");
		}

		TiXmlText* screensize_y = docHandle.FirstChild("config").FirstChild("screen_size").FirstChild("y").FirstChild().Text();
		if(screensize_y)
		{
			m_screen_size_y = atoi(screensize_y->Value());
			DEBWARN("Setting Screen size y to: "<<m_screen_size_y<<"\n");
		}
		
		TiXmlText* last_level = docHandle.FirstChild("user").FirstChild("last_level").FirstChild().Text();
		if(last_level)
		{
			m_last_level = atoi(last_level->Value());
			DEBWARN("Setting last level to: "<<m_last_level<<"\n");
		}
		
	}
	else
	{
		DEBWARN("Unable to read file: "<<filename<<"\n");
		
		//set_default_values();
	}

    refresh_game_window_parameters();
    */
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
