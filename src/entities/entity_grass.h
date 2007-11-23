/***************************************************************************
                          entity_grass.h  -  description
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

#ifndef ENTITY_GRASS_H
#define ENTITY_GRASS_H

class Entity_Grass:public Entity
{
public:	

	Entity_Grass(Level* level, Uint32 x, Uint32 y);

	
	bool pass_on_me(Direction d);
	
	void check_and_do(){};
	
	bool hit_from_up(Entity_Handle){return false;};
	
	bool explode();
	
	bool roll_on_me(){return false;};
	
	bool player_pressing_left(Entity_Handle right_entity);
	
	bool player_pressing_right(Entity_Handle left_entity);
	
	bool player_pressing_up(Entity_Handle down_entity);
	
	bool player_pressing_down(Entity_Handle up_entity);
	
	void refresh_sprite(){};
	
	void move_sprite(){};
	
};

#endif //ENTITY_GRASS_H
