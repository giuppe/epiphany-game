/***************************************************************************
                          entity_door.h  -  description
                             -------------------
    begin                : Thu Apr 18 2002
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

#include "dephine.h"
#include "entity.h"


#ifndef ENTITY_DOOR_H
#define ENTITY_DOOR_H

class Entity_Door:public Entity
{
private:

	Uint32 m_door_id;
	
	bool m_is_open;

public:

	Entity_Door(Level* level, Uint32 x, Uint32 y, Sprite& sprite, Uint32 id);
	
	Uint32 get_door_id();
	
	bool pass_on_me(Direction);
	
	bool smash(Entity_Handle){return false;};
	
	void check_and_do();
	
	bool explode();
	
	bool roll_on_me(){return false;};
	
};

#endif //ENTITY_DOOR_H
