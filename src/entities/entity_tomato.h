/***************************************************************************
                          entity_peperon.h  -  description
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
#include "entity_monster.h"

#ifndef ENTITY_TOMATO_H
#define ENTITY_TOMATO_H

class Entity_Tomato:public Entity_Monster
{
public:
	Entity_Tomato(Level* level, unsigned int x, unsigned int y, Sprite& sprite, Direction direction);
	
	void check_and_do();
	
	bool smash(Ntt_pointer&);
	
	bool pass_on_me(Direction);
	
	void kill();
	
	bool explode();
	
	bool roll_on_me(){return false;};
	
	void explode_all_around();

};

#endif //ENTITY_TOMATO_H
