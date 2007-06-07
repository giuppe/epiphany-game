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
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#include "entity.h"
#include "pointer.h"
#include "entity_falling.h"

#ifndef ENTITY_BOULDER_H
#define ENTITY_BOULDER_H

//A Boulder is a heavy rock. It smash player and Sapphires if
// it falls over them
class Entity_Boulder: public Entity_Falling
{
public:

	Entity_Boulder(Level* level, unsigned int x, unsigned int y, Sprite& sprite);
	
	
	void check_and_do();
	
	bool pass_on_me(Direction d);
	
	bool smash(Entity_Handle){return false;};
	
	bool explode();
	
//	bool roll_on_me(){return true;};
	
	
};

#endif //ENTITY_BOULDER_H


