/***************************************************************************
                          entity_gem.h  -  description
                             -------------------
    begin                : Thu Sep 27 2001
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

#ifndef ENTITY_GEM_H
#define ENTITY_GEM_H

//Self-explaining class ;)

class Entity_Gem
{

protected:
	
	Sint32 m_value;
		
public:
	
	Sint32 get_value() const;
	
};

#endif //ENTITY_GEM_H
