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
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "dephine.h"
#include "sample.h"

Sample::Sample(CL_SoundBuffer* soundbuffer, bool dont_play_several)
{
	m_soundbuffer=soundbuffer;
	m_dont_play_several=dont_play_several;
}

void Sample::play()
{
	if(m_dont_play_several==true)
	{
		if(!(this->is_playing()))
		{
			try
			{
				m_soundbuffer_session = m_soundbuffer->play();
			}
			catch(CL_Error ex)
			{
				std::cout<<ex.message<<endl;
			}
		}
	}
	else
	{
		try
		{
			m_soundbuffer_session = m_soundbuffer->play();
		}
		catch(CL_Error ex)
		{
			std::cout<<ex.message<<endl;
		}
  }
}

void Sample::stop()
{
	m_soundbuffer->stop();
}

bool Sample::is_playing()
{
	return m_soundbuffer_session.is_playing();
}

bool Sample::set_frequency(int frequency)
{
	return m_soundbuffer->set_frequency(frequency);
}

int Sample::get_frequency()
{
	return m_soundbuffer->get_frequency();
}

