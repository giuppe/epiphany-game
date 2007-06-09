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
#include "game_timer.h"



Game_Timer::Game_Timer(unsigned int total_time)
{
	
	m_total_time=total_time;
	m_last_time=0;
}




void Game_Timer::set_total_time(unsigned int total_time)
{
	m_total_time=total_time;
}




void Game_Timer::update()
{
	if(CL_System::get_time()-m_last_time>1000)
	{
		m_last_time=CL_System::get_time();
		m_total_time--;
	}
	
}




bool Game_Timer::is_zero()
{
	return(m_total_time==0);
}




void Game_Timer::start()
{
	m_last_time=CL_System::get_time();
}



const char* Game_Timer::get_time_string()
{
	CL_String time_string="";
	
	int minutes=m_total_time/60;
	
	int seconds=m_total_time%60;
	
	if(minutes<10)
	{
		
		time_string+="0";
		
	}
	
	time_string+=minutes;
	
	time_string+=":";
	
	if(seconds<10)
	{
		
		time_string+="0";
		
	}
	
	time_string+=seconds;
	
	return time_string;
	
}

unsigned int Game_Timer::get_time()
{
	
	return m_total_time;
	
}

