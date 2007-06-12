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
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "dephine.h"
#include <ClanLib/sound.h>
#include "sample.h"
#include <vector>


#ifndef SFX_H
#define SFX_H

class Game;

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
	
public:
	
	//Sampleset(Game* game);
	void load_samples();
	
	void init();
	
	void play(Sample_Type type);
	
	void stop(Sample_Type type);
	
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
