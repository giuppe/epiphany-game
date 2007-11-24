/***************************************************************************
                          music_manager.cpp  -  description
                             -------------------
    begin                : Jun 13 2007
    copyright            : (C) 2007 by Giuseppe D'Aqui'
    email                : kumber@tiscalinet.it
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License, Version 2,      *
 *   as published by the Free Software Foundation.                         *
 *                                                                         *
 ***************************************************************************/

#include "dephine.h"
#include <SDL/SDL_mixer.h>
#include "music_manager.h"
#include "resource_factory.h"
#include "sfx.h"

void Music_Manager::init()
{

	m_disabled = Sample_Manager::instance()->is_disabled();
	
	if(m_disabled==true)
		{
			DEBOUT("Sound system disabled, not initing music\n");
			return;
		}
	
	//FIXME: we should auto-resize the vector
	m_musics.resize(25);
	
	music_enabled = true;
	
	load_musics();
	
	this->set_volume(Epiconfig::instance()->get_volume_music());
}


void Music_Manager::load_musics()
{

	if(m_disabled==true)
		{
			DEBOUT("Sound system disabled, not loading music\n");
			return;
		}
	
	Resource_Factory* res_factory=Resource_Factory::instance();

	std::string res_path(res_factory->get_resource_path());

	res_path+= "/sfx/";

	//FIXME should check the existence of music files
	m_musics[MUS_MENU]=Mix_LoadMUS((res_path+"epiphany_menu.ogg").c_str());

	m_musics[MUS_CREDITS]=Mix_LoadMUS((res_path+"epiphany_credits.ogg").c_str());

	m_musics[MUS_GAME]=Mix_LoadMUS((res_path+"epiphany_game.ogg").c_str());

	m_musics[MUS_READY]=Mix_LoadMUS((res_path+"epiphany_ready.ogg").c_str());

}

void Music_Manager::deinit()
{
	if(m_disabled==true)
		{
			DEBOUT("Sound system disabled, not unloading music\n");
			return;
		}
	Mix_FreeMusic(m_musics[MUS_MENU]);
	Mix_FreeMusic(m_musics[MUS_CREDITS]);
	Mix_FreeMusic(m_musics[MUS_GAME]);
	Mix_FreeMusic(m_musics[MUS_READY]);
	Epiconfig::instance()->set_volume_music(this->get_volume());
}

Mix_Music* Music_Manager::get_music(Music_Type music)
{
	if(m_disabled==true)
	{
			DEBOUT("Sound system disabled, cannot get music\n");
			exit(1);
			return NULL;
	}
	//FIXME: it should assert the existence of sample
	return m_musics[music];
	
}




void Music_Manager::play(Music_Type type)
{
	if(m_disabled==true)
		{
			return;
		}
	
	if(music_enabled == false)
		return;
		
	Mix_Music* music = get_music(type);
	
	if(Mix_PlayMusic(music, -1)==-1) {
    	DEBWARN("Mix_PlayMusic: "<< Mix_GetError()<<"\n");
	}
}


Uint32 Music_Manager::get_max_volume()
{
	return MIX_MAX_VOLUME/16;
}




void Music_Manager::set_volume(Uint32 value)
{
	if(m_disabled==true)
		{
			DEBOUT("Sound system disabled, cannot set volume\n");
			return;
		}
	Mix_VolumeMusic(value*16);
}




Uint32 Music_Manager::get_volume()
{
	if(m_disabled==true)
		{
			DEBOUT("Sound system disabled, volume is always zero\n");
			return 0;
		}
	return Mix_VolumeMusic(-1)/16;
}


void Music_Manager::disable_music()
{
	music_enabled=false;
}

void Music_Manager::enable_music()
{
	music_enabled = true;
}



Music_Manager* Music_Manager::_instance = 0;

Music_Manager* Music_Manager::instance()
{
	if(_instance==0)
	{
		_instance=new Music_Manager();
		_instance->init();
	}
	return _instance;
}

