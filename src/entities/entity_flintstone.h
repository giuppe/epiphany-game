/***************************************************************************
                          entity_flintstone.h  -  description
                             -------------------
    begin                : Fri Apr 19 2002
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



#include "entity.h"

#include "entity_falling.h"

#ifndef ENTITY_FLINTSTONE_H
#define ENTITY_FLINTSTONE_H

//A Flintstone is an explosive rock. It explodes after falling.

class Entity_Flintstone: public Entity_Falling
{
private:
	bool m_is_exploding;
	
//	bool m_just_checked;

public:

	Entity_Flintstone(Level* level, Uint32 x, Uint32 y);
	
	
	void check_and_do();
	
	bool pass_on_me(Direction d);
	
	bool smash(Entity_Handle);
	
	bool explode();
	
	void explode_all_around();
	
//	bool roll_on_me(){return true;};
	
};

#endif //ENTITY_FLINTSTONE_H
