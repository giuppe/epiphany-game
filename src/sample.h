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
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "dephine.h"
#include "SDL/SDL_mixer.h"
 
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
	void play();
	
};

#endif //SAMPLE_H
