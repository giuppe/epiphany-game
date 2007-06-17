/***************************************************************************
                          sfx.cpp  -  description
                             -------------------
    begin                : Fri Aug 16 2002
    copyright            : (C) 2002 by Giuseppe D'Aqui'
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
#include "sfx.h"
#include "sample.h"
#include <vector>
#include <string>
#include "SDL/SDL_mixer.h"
#include "game.h"


void Sample_Manager::init()
{
	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024)==-1) 
	{
    	printf("Mix_OpenAudio: %s\n", Mix_GetError());
    	exit(2);
	}
	

	
	
	//FIXME: we should auto-resize the vector
	m_samples.resize(25);
	// allocate 16 mixing channels
	Mix_AllocateChannels(32);
	Mix_GroupChannels(0, 1, m_channels_monsters);
	Mix_GroupChannels(2, 3, m_channels_boulders);
	Mix_GroupChannels(4, 5, m_channels_gems);
	Mix_GroupChannels(6, 7, m_channels_explosions);
	Mix_GroupChannel(8, m_channels_timealarm);
	
	load_samples();
}

void Sample_Manager::load_samples()
{

	Resource_Factory* res_factory=Resource_Factory::instance();

	std::string res_path(res_factory->get_resource_path());

	res_path+= "/sfx/";
	

	m_samples[SFX_BOULDER_FALL]=new Sample(Mix_LoadWAV((res_path+"boulder_fall.wav").c_str()));
	m_samples[SFX_EMERALD_EAT]=new Sample(Mix_LoadWAV((res_path+"emerald_eat.wav").c_str()));
	m_samples[SFX_SAPPHIRE_EAT]=new Sample(Mix_LoadWAV((res_path+"sapphire_eat.wav").c_str()));
	m_samples[SFX_GAME_GAMEOVER]=new Sample(Mix_LoadWAV((res_path+"gameover.wav").c_str()));
	m_samples[SFX_DOOR_PASS]=new Sample(Mix_LoadWAV((res_path+"door_pass.wav").c_str()));
	m_samples[SFX_EMERALD_FALL]=new Sample(Mix_LoadWAV((res_path+"gem_fall.wav").c_str()));
	m_samples[SFX_SAPPHIRE_FALL]=new Sample(Mix_LoadWAV((res_path+"gem_fall.wav").c_str()));
	m_samples[SFX_GRASS_EAT]=new Sample(Mix_LoadWAV((res_path+"grass_eat.wav").c_str()));
	m_samples[SFX_KEY_EAT]=new Sample(Mix_LoadWAV((res_path+"key_eat.wav").c_str()));
	m_samples[SFX_PLAYER_MOVE]=new Sample(Mix_LoadWAV((res_path+"player_move.wav").c_str()));
	m_samples[SFX_MONSTER_MOVE]=new Sample(Mix_LoadWAV((res_path+"monster_move.wav").c_str()));
	m_samples[SFX_WOOD_SMASH]=new Sample(Mix_LoadWAV((res_path+"wood_smash.wav").c_str()));
	m_samples[SFX_GAME_TIMEALARM]=new Sample(Mix_LoadWAV((res_path+"timealarm.wav").c_str()));
	m_samples[SFX_EXPLOSION]=new Sample(Mix_LoadWAV((res_path+"explosion.wav").c_str()));


}

void Sample_Manager::deinit()
{
	delete m_samples[SFX_BOULDER_FALL];
	delete 	m_samples[SFX_EMERALD_EAT];
	delete 	m_samples[SFX_SAPPHIRE_EAT];
	delete 	m_samples[SFX_GAME_GAMEOVER];
	delete 	m_samples[SFX_DOOR_PASS];
	delete 	m_samples[SFX_EMERALD_FALL];
	delete 	m_samples[SFX_SAPPHIRE_FALL];
	delete 	m_samples[SFX_GRASS_EAT];
	delete 	m_samples[SFX_KEY_EAT];
	delete 	m_samples[SFX_PLAYER_MOVE];
	delete 	m_samples[SFX_MONSTER_MOVE];
	delete 	m_samples[SFX_WOOD_SMASH];
	delete 	m_samples[SFX_GAME_TIMEALARM];
	delete 	m_samples[SFX_EXPLOSION];
}

Sample* Sample_Manager::get_sample(Sample_Type sfx)
{
	//FIXME: it should assert the existence of sample
	return m_samples[sfx];
	
}

void Sample_Manager::play(Sample_Type type)
{
	Sint32 channel_group=-1;
	switch(type)
	{
		case SFX_BOULDER_FALL:
			channel_group = m_channels_boulders;
			break;
		case SFX_MONSTER_MOVE:
			channel_group = m_channels_monsters;
			break;
		case SFX_EXPLOSION:
			channel_group = m_channels_explosions;
			break;
		case SFX_EMERALD_FALL:
		case SFX_SAPPHIRE_FALL:
			channel_group = m_channels_gems;
			break;
		case SFX_GAME_TIMEALARM:
			channel_group = m_channels_timealarm;
			break;
		default:
			break;
	}
	
	Sint32 available_channel = Mix_GroupAvailable(channel_group);
	if(available_channel >=0)
	{
		m_samples[type]->play(available_channel);
	}
}



Sample_Manager* Sample_Manager::_instance = 0;

Sample_Manager* Sample_Manager::instance()
{
	if(_instance==0)
	{
		_instance=new Sample_Manager();
		_instance->init();
	}
	return _instance;
}

