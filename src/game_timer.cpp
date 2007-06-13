/***************************************************************************
                          game_time.cpp  -  description
                             -------------------
    begin                : Mon Aug 12 2002
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
#include "SDL/SDL.h"
#include <cstdlib>
#include <cstdio>
#include "game_timer.h"



Game_Timer::Game_Timer(Uint32 total_time)
{
	
	m_total_time=total_time;
	m_last_time=0;
}




void Game_Timer::set_total_time(Uint32 total_time)
{
	m_total_time=total_time;
}




void Game_Timer::update()
{
	if(SDL_GetTicks()-m_last_time>1000)
	{
		m_last_time=SDL_GetTicks();
		m_total_time--;
	}
	
}




bool Game_Timer::is_zero()
{
	return(m_total_time==0);
}




void Game_Timer::start()
{
	m_last_time=SDL_GetTicks();
}



const char* Game_Timer::get_time_string()
{
	char  time_string[10];
	
	int minutes=m_total_time/60;
	
	int seconds=m_total_time%60;
	
	if(minutes<10)
	{
		
		strcat(time_string,"0");
		
	}
	
	char minutes_string[2];
	
	sprintf(minutes_string, "%d", minutes);
	
	strcat(time_string, minutes_string);
	
	strcat(time_string,":");
	
	if(seconds<10)
	{
		
		strcat(time_string,"0");
		
	}
	
	char seconds_string[2];
	
	sprintf(seconds_string, "%d", seconds);
	
	
	strcat(time_string, seconds_string);
	
	return time_string;
	
}

Uint32 Game_Timer::get_time()
{
	
	return m_total_time;
	
}

