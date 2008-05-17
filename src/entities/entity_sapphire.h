/***************************************************************************
                          entity_sapphire.h  -  description
                             -------------------
    begin                : Mon Oct 1 2001
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
#include "entity_gem.h"
#include "entity_falling.h"

#ifndef ENTITY_SAPPHIRE_H
#define ENTITY_SAPPHIRE_H


class Entity_Sapphire: /*public Entity,*/public Entity_Falling, public Entity_Gem
{
public:

	Entity_Sapphire(Level* level,Uint32 x, Uint32 y);

	//valore dello smeraldo quando preso dal giocatore
	//static const Uint32 value=1;
	
	void check_and_do();

	bool hit_from_up(Entity_Handle);
	
	bool explode();
	
//	bool roll_on_me(){return true;};

	bool player_pressing_left(Entity_Handle right_entity);
	
	bool player_pressing_right(Entity_Handle left_entity);
	
	bool player_pressing_up(Entity_Handle down_entity);
	
	bool player_pressing_down(Entity_Handle up_entity);

	
	
};

#endif //ENTITY_SAPPHIRE_H

