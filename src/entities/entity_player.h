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
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
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

	unsigned int m_score;
	
	Direction m_direction;
	
	bool m_is_snapping;
	
public:
	
	Entity_Player(Level* level, unsigned int x, unsigned int y, Sprite& sprite);

	void check_and_do();
	
	bool is_alive();
	
	bool pass_on_me(Direction d);
	
	void win();
	
	bool is_exited();
	
	void set_direction(Direction d);
	
	void set_snap(bool snap);
	
	unsigned int get_score();		
	
	bool smash(Ntt_pointer&);
	
	void inc_score(int score);
	
	bool explode();
	
	void kill();
	
	bool roll_on_me(){return false;};
	
};

#endif //ENTITY_PLAYER_H
