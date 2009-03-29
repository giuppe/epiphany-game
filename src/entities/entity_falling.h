/***************************************************************************
                          entity_falling.h  -  description
                             -------------------
    begin                : Sat Sep 29 2001
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

#include "dephine.h"
#include "entity.h"

#ifndef ENTITY_FALLING_H
#define ENTITY_FALLING_H

//This class contain function needed by falling objects - like
//boulders and gems

class Entity_Falling:public Entity
{
private:
	Entity_Falling(Level* level, Uint32 x, Uint32 y);
protected:
	
	//bool m_is_falling;
	

public:

	

	Entity_Falling();
	
	bool is_falling();
	

	void roll(Direction direction);
	
	void check_and_do();
	
	bool roll_on_me();
	
		
};

#endif //ENTITY_FALLING_H
