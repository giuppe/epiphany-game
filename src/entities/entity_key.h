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
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "dephine.h"
#include "entity.h"


#ifndef ENTITY_KEY_H
#define ENTITY_KEY_H

class Entity_Key:public Entity
{
private:

	unsigned int m_key_id;
	
public:

	Entity_Key(Level* level, unsigned int x, unsigned int y, Sprite& sprite, unsigned int id);
	
	unsigned int get_key_id();
	
	bool pass_on_me(Direction);
	
	bool smash(Ntt_pointer&){return false;};
	
	void check_and_do(){};
	
	bool explode();
	
	bool roll_on_me(){return false;};
	
};

#endif //ENTITY_KEY_H
