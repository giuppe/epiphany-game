/***************************************************************************
                          entity_wood.h  -  description
                             -------------------
    begin                : Wed May 1 2002
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



#include "entity.h"

#ifndef ENTITY_WOOD_H
#define ENTITY_WOOD_H

class Level;
class Sprite;

//A Wood is a slippery brick. Unmovable, it can be destroyed by explosions

class Entity_Wood:public Entity
{
public:	

	Entity_Wood(Level* level, unsigned int x, unsigned int y, Sprite& sprite);

	
	//it does nothing: its check_and_do is empty.
	void check_and_do(){}	

	bool pass_on_me(Direction d){return false;}
	
	bool smash(Entity_Handle);
	
	bool explode();
	
	bool roll_on_me(){return true;};
	
};

#endif //ENTITY_WOOD_H

