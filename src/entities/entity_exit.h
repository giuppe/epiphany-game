/***************************************************************************
                          entity_exit.h  -  description
                             -------------------
    begin                : Mon Oct 1 2001
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
	
	bool pass_on_me(Direction d);
	
	void set_min_score(Uint32 min_score);
	
	Uint32 get_min_score();
	
	bool smash(Entity_Handle){return false;};
	
	bool explode();

	bool roll_on_me(){return false;};	
	
};

#endif //ENTITY_EXIT_H
