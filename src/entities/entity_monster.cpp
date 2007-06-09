/***************************************************************************
                          entity_monster.cpp  -  description
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

Entity_Monster::Entity_Monster(Level* level, Uint32 x, Uint32 y)
{
	current_level=level;
	m_position_x=x;
	m_position_y=y;
	m_type=UNKNOWN;
//	m_sprite=current_level.get_sprite(UNKNOWN);
	m_exists=true;
	m_is_exploding=false;
		
}

Entity_Monster::Entity_Monster()
{
	current_level=0;
	m_position_x=0;
	m_position_y=0;
	m_type=UNKNOWN;
	m_sprite=0;
	m_exists=true;
		
}



