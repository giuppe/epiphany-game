/***************************************************************************
                          entity_player.h  -  description
                             -------------------
    begin                : Thu Sep 20 2001
    copyright            : (C) 2001 by Giuseppe D'Aquì
    email                : kumber@tiscalinet.it
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License, Version 2, as published by  *
 *   the Free Software Foundation.                                   *
 *                                                                         *
 ***************************************************************************/

#include "entity.h"

#ifndef ENTITY_PLAYER_H
#define ENTITY_PLAYER_H

class Entity_Player:public Entity
{
private:

	bool m_is_alive;
	
	bool m_is_exited;

	Uint32 m_score;
	
	Direction m_direction;
	
	bool m_is_snapping;
	
public:
	
	Entity_Player(Level* level, Uint32 x, Uint32 y);

	void check_and_do();
	
	bool is_alive();
	
	bool pass_on_me(Direction d);
	
	void win();
	
	bool is_exited();
	
	void set_direction(Direction d);
	
	void set_snap(bool snap);
	
	Uint32 get_score();		
	
	bool smash(Entity_Handle);
	
	void inc_score(int score);
	
	bool explode();
	
	void kill();
	
	bool roll_on_me(){return false;};
	
};

#endif //ENTITY_PLAYER_H
