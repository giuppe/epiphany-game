/***************************************************************************
                          entity_emerald.h  -  description
                             -------------------
    begin                : Thu Sep 20 2001
    copyright            : (C) 2001 by Giuseppe D'Aqu�
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
#include "entity_gem.h"
#include "entity_falling.h"

#ifndef ENTITY_EMERALD_H
#define ENTITY_EMERALD_H

//An Emerald is the less valuable Gem (1 point)

class Entity_Emerald: public Entity_Falling, public Entity_Gem
{
public:

	Entity_Emerald(Level* level, unsigned int x, unsigned int y, Sprite& sprite);

	void check_and_do();
	
	bool pass_on_me(Direction d);
	
	bool smash(Ntt_pointer&){return false;};
	
	bool explode();

//	bool roll_on_me(){return true;};
	
	
};

#endif //ENTITY_EMERALD_H
