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
	
	bool smash(Entity_Handle){return false;};
	
	void check_and_do(){};
	
	bool explode();
	
	bool roll_on_me(){return false;};
	
};

#endif //ENTITY_KEY_H
