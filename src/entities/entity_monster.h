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
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "dephine.h"
#include "entity.h"

#ifndef ENTITY_MONSTER_H
#define ENTITY_MONSTER_H


class Entity_Monster:public Entity
{
protected:
	
	Direction m_direction;
	
	bool m_is_exploding;

public:

	Entity_Monster(Level* level, Uint32 x, Uint32 y);

	Entity_Monster();
	
	Direction get_direction();
	
};

#endif //ENTITY_MONSTER_H
