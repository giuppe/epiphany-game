/***************************************************************************
                          entity_monster.h  -  description
                             -------------------
    begin                : Tue Apr 23 2002
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

#ifndef ENTITY_MONSTER_H
#define ENTITY_MONSTER_H


class Entity_Monster:public Entity
{
protected:
	
//	Direction m_direction;
	
	bool m_is_exploding;
	Direction get_direction();

public:

	Entity_Monster(Level* level, Uint32 x, Uint32 y);

	Entity_Monster();
	

	
};

#endif //ENTITY_MONSTER_H
