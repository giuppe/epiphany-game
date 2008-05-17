/***************************************************************************
                          entity_brick.h  -  description
                             -------------------
    begin                : Thu Sep 20 2001
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

#ifndef ENTITY_BRICK_H
#define ENTITY_BRICK_H

class Level;
class Sprite;

//A Brick is a brick ;) Unmovable, it can be destroyed by explosions

class Entity_Brick:public Entity
{
public:	

	Entity_Brick(Level* level, Uint32 x, Uint32 y);

	
	//it does nothing: its check_and_do is empty.
	void check_and_do(){}	

	bool hit_from_up(Entity_Handle){return false;};
	
	bool explode();
	
	bool roll_on_me(){return false;};
	
	void refresh_sprite(){};
	
	void move_sprite(){};
	
};

#endif //ENTITY_BRICK_H

