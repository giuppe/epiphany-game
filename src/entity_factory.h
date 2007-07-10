/***************************************************************************
                          entity_factory.h  -  description
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

#ifndef ENTITY_FACTORY_H_
#define ENTITY_FACTORY_H_
#include "entity_type.h"


class Entity;
class Level;


class Entity_Factory
{
private:

public:

	Entity* create_entity(Entity_Type type, Level* level);


// begin Singleton stuff

private:

	static Entity_Factory* _instance;

protected:

	Entity_Factory(){};

public:

	static Entity_Factory* instance();

// end Singleton stuff

};

#endif /*ENTITY_FACTORY_H_*/
