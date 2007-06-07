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
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "dephine.h"
#include "sfx.h"
#include "sample.h"
#include <vector>
#include "game.h"


Sampleset::Sampleset()
{

	m_samples.resize(25);
}

void Sampleset::load_samples()
{

	CL_ResourceManager* res_manager=Game::instance()->get_resource_manager();

	try
	{
		m_samples[SFX_BOULDER_FALL]=new Sample(CL_SoundBuffer::load("Samples/SFX_Boulder_Fall", res_manager),true);
		m_samples[SFX_EMERALD_EAT]=new Sample(CL_SoundBuffer::load("Samples/SFX_Emerald_Eat", res_manager));
		m_samples[SFX_SAPPHIRE_EAT]=new Sample(CL_SoundBuffer::load("Samples/SFX_Sapphire_Eat", res_manager));
		m_samples[SFX_GAME_GAMEOVER]=new Sample(CL_SoundBuffer::load("Samples/SFX_Gameover", res_manager));
		m_samples[SFX_DOOR_PASS]=new Sample(CL_SoundBuffer::load("Samples/SFX_Door_Pass", res_manager));
		m_samples[SFX_EMERALD_FALL]=new Sample(CL_SoundBuffer::load("Samples/SFX_Emerald_Fall", res_manager));
		m_samples[SFX_SAPPHIRE_FALL]=new Sample(CL_SoundBuffer::load("Samples/SFX_Sapphire_Fall", res_manager));
		m_samples[SFX_GRASS_EAT]=new Sample(CL_SoundBuffer::load("Samples/SFX_Grass_Eat", res_manager));
		m_samples[SFX_KEY_EAT]=new Sample(CL_SoundBuffer::load("Samples/SFX_Key_Eat", res_manager));
		m_samples[SFX_PLAYER_MOVE]=new Sample(CL_SoundBuffer::load("Samples/SFX_Player_Move", res_manager));
		m_samples[SFX_MONSTER_MOVE]=new Sample(CL_SoundBuffer::load("Samples/SFX_Monster_Move", res_manager),true);
		m_samples[SFX_WOOD_SMASH]=new Sample(CL_SoundBuffer::load("Samples/SFX_Wood_Smash", res_manager));
		m_samples[SFX_GAME_TIMEALARM]=new Sample(CL_SoundBuffer::load("Samples/SFX_Timealarm", res_manager),true);
		m_samples[SFX_EXPLOSION]=new Sample(CL_SoundBuffer::load("Samples/SFX_Explosion", res_manager), true);
	}
	catch(CL_Error ex)
	{
		std::cout<<ex.message;
	}

}

Sample* Sampleset::get_sample(Sample_Type sfx)
{
	
	return m_samples[sfx];
	
}
