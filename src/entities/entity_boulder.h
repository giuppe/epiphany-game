/***************************************************************************
                          entity_boulder.h  -  description
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

#include "entity_falling.h"

#ifndef ENTITY_BOULDER_H
#define ENTITY_BOULDER_H

//A Boulder is a heavy rock. It smash player and Sapphires if
// it falls over them
class Entity_Boulder: public Entity_Falling
{
public:

	Entity_Boulder(Level* level, Uint32 x, Uint32 y);
	
	
	void check_and_do();
	
	bool pass_on_me(Direction d);
	
	bool hit_from_up(Entity_Handle){return false;};
	
	bool explode();
	
	bool player_pressing_left(Entity_Handle right_entity);
	
	bool player_pressing_right(Entity_Handle left_entity);
	
//	bool roll_on_me(){return true;};
	
	
};

#endif //ENTITY_BOULDER_H


