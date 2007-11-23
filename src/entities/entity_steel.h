/***************************************************************************
                          entity_steel.h  -  description
                             -------------------
    begin                : Wed May 1 2002
    copyright            : (C) 2002 by Giuseppe D'Aqui'
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

#ifndef ENTITY_STEEL_H
#define ENTITY_STEEL_H

class Level;
class Sprite;

//A Brick is a brick ;) Unmovable, it can be destroyed by explosions

class Entity_Steel:public Entity
{
public:	

	Entity_Steel(Level* level, Uint32 x, Uint32 y);

	
	//it does nothing: its check_and_do is empty.
	void check_and_do(){}	

	bool pass_on_me(Direction d){return false;}
	
	bool hit_from_up(Entity_Handle){return false;};
	
	bool explode();
	
	bool roll_on_me(){return false;};
	
	void refresh_sprite(){};
	
	void move_sprite(){};
	
};

#endif //ENTITY_STEEL_H
