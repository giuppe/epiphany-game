/***************************************************************************
                          game_time.h  -  description
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

#ifndef GAME_TIMER_H
#define GAME_TIMER_H


class Game_Timer
{
private:
	//total countdown time
	Uint32 m_total_time;
	//last acquired time
	Uint32 m_last_time;
public:
	Game_Timer(Uint32 total_time = 0);
	
	void update();
	
	void start();
	
	void set_total_time(Uint32 total_time);
	
	bool is_zero();
	
	const char* get_time_string();
	
	Uint32 get_time();
	


};

#endif //GAME_TIMER_H
