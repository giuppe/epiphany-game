/***************************************************************************
                          entity_gem.h  -  description
                             -------------------
    begin                : Thu Sep 27 2001
    copyright            : (C) 2001 by Giuseppe D'Aquì
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

#ifndef ENTITY_GEM_H
#define ENTITY_GEM_H

//Self-explaining class ;)

class Entity_Gem
{

protected:
	
	int m_value;
		
public:
	
	int get_value() const;
	
};

#endif //ENTITY_GEM_H
