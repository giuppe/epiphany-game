/***************************************************************************
                          entity_steel.cpp  -  description
                             -------------------
    begin                : Wed May 1 2002
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

#include "level.h"
#include "sprite.h"
#include "entity.h"
#include "entity_steel.h"

Entity_Steel::Entity_Steel(Level* level, Uint32 x, Uint32 y, Sprite& sprite)
{
	current_level=level;
	m_position_x=x;
	m_position_y=y;
	m_type=STEEL;
	m_sprite=sprite;
	(m_sprite).set_pos_x(m_position_x*k_sprite_size);
	(m_sprite).set_pos_y(m_position_y*k_sprite_size);
	m_sprite.set_state(SP_STOP);
	
	m_exists=true;
}

bool Entity_Steel::explode()
{
	return false;
}

