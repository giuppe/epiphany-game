/***************************************************************************
                          sample.h  -  description
                             -------------------
    begin                : Mon Aug 26 2002
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
#include <SDL2/SDL_mixer.h>
 
#ifndef SAMPLE_H
#define SAMPLE_H


class Sample
{
private:
	Mix_Chunk* m_soundbuffer;
	
public:
//	Sample(){};
	Sample(Mix_Chunk* soundbuffer);
	~Sample();
	void play(Uint32 channel);
	
};

#endif //SAMPLE_H
