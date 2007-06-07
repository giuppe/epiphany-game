/***************************************************************************
                          entity_brick.h  -  description
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

#ifndef ENTITY_BRICK_H
#define ENTITY_BRICK_H

class Level;
class Sprite;

//A Brick is a brick ;) Unmovable, it can be destroyed by explosions

class Entity_Brick:public Entity
{
public:	

	Entity_Brick(Level* level, unsigned int x, unsigned int y, Sprite& sprite);

	
	//it does nothing: its check_and_do is empty.
	void check_and_do(){}	

	bool pass_on_me(Direction d){return false;}
	
	bool smash(Entity_Handle){return false;};
	
	bool explode();
	
	bool roll_on_me(){return false;};
	
};

#endif //ENTITY_BRICK_H

