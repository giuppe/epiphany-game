/***************************************************************************
                          sfx.h  -  description
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

#include <vector>


#ifndef SFX_H
#define SFX_H

class Sample;

enum Sample_Type{	SFX_BOULDER_FALL,
									SFX_EMERALD_EAT,
									SFX_SAPPHIRE_EAT,
									SFX_GAME_GAMEOVER,
									SFX_DOOR_PASS,
									SFX_EMERALD_FALL,
									SFX_SAPPHIRE_FALL,
									SFX_GRASS_EAT,
									SFX_KEY_EAT,
									SFX_PLAYER_MOVE,
									SFX_MONSTER_MOVE,
									SFX_WOOD_SMASH,
									SFX_GAME_TIMEALARM,
									SFX_EXPLOSION
								};

class Sample_Manager
{
private:
	std::vector<Sample*> m_samples;
	
	Sample* get_sample(Sample_Type sfx);
	
		void load_samples();
		
	enum{
			m_channels_monsters,
			m_channels_boulders,
			m_channels_gems,
			m_channels_explosions,
			m_channels_timealarm
	};
	
	
public:
	
	
	void init();
	
	void deinit();
	
	void play(Sample_Type type);
	
	Uint32 get_max_volume();
	
	Uint32 get_volume();
	
	void set_volume(Uint32 value);

	
	// begin Singleton stuff

private:

    static Sample_Manager* _instance;

protected:

	Sample_Manager(){};

public:

    static Sample_Manager* instance();

// end Singleton stuff
	
};

#endif //SFX_H
