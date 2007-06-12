/***************************************************************************
                          entity_wood.cpp  -  description
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
#include "entity_wood.h"

Entity_Wood::Entity_Wood(Level* level, Uint32 x, Uint32 y)
{
	current_level=level;
	m_position_x=x;
	m_position_y=y;
	m_type=WOOD;
	Surface_Manager* surf_man = Surface_Manager::instance();
	m_sprite=Sprite(surf_man->get_surface(Surface_Factory::SRF_WOOD));
	(m_sprite).set_pos_x(m_position_x*k_sprite_size);
	(m_sprite).set_pos_y(m_position_y*k_sprite_size);
	m_sprite.set_state(SP_STOP);
	
	m_exists=true;
}

bool Entity_Wood::explode()
{
	kill();
	return true;
}

bool Entity_Wood::smash(Entity_Handle)
{
	Sample_Manager::instance()->play(SFX_WOOD_SMASH);
	return false;
}

