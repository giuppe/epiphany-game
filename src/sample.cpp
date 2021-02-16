/***************************************************************************
                          sample.cpp  -  description
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
#include "sample.h"

Sample::Sample(Mix_Chunk* soundbuffer)
{
	m_soundbuffer=soundbuffer;
	
}

Sample::~Sample()
{
	Mix_FreeChunk(m_soundbuffer);
}

void Sample::play(Uint32 channel)
{
	
  	if(Mix_PlayChannel(channel, m_soundbuffer, 0) == -1)
	{
		printf("Mix_PlayChannel: %s\n",Mix_GetError());
	}
	
}


