/***************************************************************************
                          entity_explosion.h  -  description
                             -------------------
    begin                : Fri Apr 12 2002
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

#include "entity_type.h"

#ifndef ENTITY_EXPLOSION
#define ENTITY_EXPLOSION

class Entity_Explosion: public Entity
{
private:
	Entity_Type m_transform_to;
	
	int m_existing_count;
	bool m_is_exploding;
	
public:
	
	Entity_Explosion(Level* level, Uint32 x, Uint32 y);
		
	void check_and_do();
	
	bool pass_on_me(Direction d){return false;};
	
	bool hit_from_up(Entity_Handle){return false;};
	
	~Entity_Explosion();
	
	bool explode();
	
	bool roll_on_me(){return false;};
	
	void set_transform_to(Entity_Type transform_to);
};

#endif //ENTITY_EXPLOSION
