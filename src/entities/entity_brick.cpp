/***************************************************************************
                          entity_brick.cpp  -  description
                             -------------------
    begin                : Mon Oct 22 2001
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
 
#include "level.h"
#include "sprite.h"
#include "entity.h"
#include "entity_brick.h"

Entity_Brick::Entity_Brick(Level* level, Uint32 x, Uint32 y)
{
	current_level=level;
	m_position_x=x;
	m_position_y=y;
	m_type=BRICK;
	Surface_Manager* surf_man = Surface_Manager::instance();
	m_sprite.init(surf_man->get_surface(Surface_Manager::SRF_BRICK));
	m_sprite.set_state(SP_STOP);
	m_sprite.start_animation();
	
	m_exists=true;
}

bool Entity_Brick::explode()
{
	kill();
	return true;
}
