/***************************************************************************
                          entity_key.h  -  description
                             -------------------
    begin                : Thu Apr 18 2002
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

#include "dephine.h"
#include "entity.h"


#ifndef ENTITY_KEY_H
#define ENTITY_KEY_H

class Entity_Key:public Entity
{
private:

	Uint32 m_key_id;
	
public:

	Entity_Key(Level* level, Uint32 x, Uint32 y, Uint32 id);
	
	Uint32 get_key_id();
	
	bool pass_on_me(Direction);
	
	bool hit_from_up(Entity_Handle){return false;};
	
	void check_and_do(){};
	
	bool explode();
	
	bool roll_on_me(){return false;};
	
	bool player_pressing_left(Entity_Handle right_entity);
	
	bool player_pressing_right(Entity_Handle left_entity);
	
	bool player_pressing_up(Entity_Handle down_entity);
	
	bool player_pressing_down(Entity_Handle up_entity);
	
};

#endif //ENTITY_KEY_H
