/***************************************************************************
                          entity_grass.h  -  description
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

#ifndef ENTITY_GRASS_H
#define ENTITY_GRASS_H

class Entity_Grass:public Entity
{
public:	

	Entity_Grass(Level* level, Uint32 x, Uint32 y);

	
	bool pass_on_me(Direction d);
	
	void check_and_do(){};
	
	bool smash(Entity_Handle){return false;};
	
	bool explode();
	
	bool roll_on_me(){return false;};
	
};

#endif //ENTITY_GRASS_H
