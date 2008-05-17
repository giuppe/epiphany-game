/***************************************************************************
                          entity_exit.h  -  description
                             -------------------
    begin                : Mon Oct 1 2001
    copyright            : (C) 2001 by Giuseppe D'Aqu�
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

#ifndef ENTITY_EXIT_H
#define ENTITY_EXIT_H

//The Exit is the last thing player must "eat" to win.
//Become passable only when player collect the right number of gems

class Entity_Exit:public Entity
{

private:
	
	bool m_is_open;
	
	Uint32 m_min_score;
	
public:

	Entity_Exit(Level* level, Uint32 x, Uint32 y, Uint32 min_score);
	
	bool is_open();
	
	void check_and_do();
	

	
	void set_min_score(Uint32 min_score);
	
	Uint32 get_min_score();
	
	bool hit_from_up(Entity_Handle){return false;};
	
	bool explode();

	bool roll_on_me(){return false;};	
	
	bool player_pressing_left(Entity_Handle right_entity);
	
	bool player_pressing_right(Entity_Handle left_entity);
	
	bool player_pressing_up(Entity_Handle down_entity);
	
	bool player_pressing_down(Entity_Handle up_entity);
	
};

#endif //ENTITY_EXIT_H
