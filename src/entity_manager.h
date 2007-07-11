/***************************************************************************
                          entity_manager.h  -  description
                             -------------------
    begin                : Jun 13 2007
    copyright            : (C) 2007 by Giuseppe D'Aqui'
    email                : kumber@tiscalinet.it
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License, Version 2,      *
 *   as published by the Free Software Foundation.                         *
 *                                                                         *
 ***************************************************************************/

#ifndef ENTITY_MANAGER_H_
#define ENTITY_MANAGER_H_

#include "dephine.h"
#include <vector>
#include <string>

class Entity;

typedef Uint32 Entity_Handle;

class Entity_Manager
{
private:
	std::vector<Entity*> m_entities;
	void init();

	
public:
	
	Entity* get_entity(Entity_Handle handle);
	
	Entity_Handle add_entity(Entity* entity);
	
	Uint32 size() {return m_entities.size();};
	
	void reset();
	
	    // begin Singleton stuff

private:

    static Entity_Manager* _instance;

protected:

    Entity_Manager(){};

public:

    static Entity_Manager* instance();

// end Singleton stuff
	
};
	

#endif /*ENTITY_MANAGER_H_*/
