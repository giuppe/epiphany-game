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

#ifndef SAMPLE_H
#define SAMPLE_H

class Sample
{
private:
	CL_SoundBuffer* m_soundbuffer;
	CL_SoundBuffer_Session m_soundbuffer_session;
	int m_frequency;
	bool m_dont_play_several;
public:
//	Sample(){};
	Sample(CL_SoundBuffer* soundbuffer, bool dont_play_several=false);
	void play();
	void stop();
	bool is_playing();
	bool set_frequency(int frequency);
	int get_frequency();
};

#endif //SAMPLE_H
