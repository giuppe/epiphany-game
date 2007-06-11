/***************************************************************************
                          entity_grass.cpp  -  description
                             -------------------
    begin                : Mon Oct 1 2001
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
#include "sprite.h"
#include "entity.h"
#include "entity_grass.h"

Entity_Grass::Entity_Grass(Level* level, Uint32 x, Uint32 y, Sprite& sprite)
{
	current_level=level;
	m_position_x=x;
	m_position_y=y;
	m_type=GRASS;
	Surface_Manager* surf_man = Surface_Manager::instance();
	m_sprite=Sprite(surf_man->get_surface(Surface_Factory::SRF_GRASS));
	(m_sprite).set_pos_x(m_position_x*k_sprite_size);
	(m_sprite).set_pos_y(m_position_y*k_sprite_size);
	m_sprite.set_state(SP_STOP);
	m_exists=true;
	
		
}

bool Entity_Grass::pass_on_me(Direction d)
{

	//DEBOUT("Entering Entity_Grass::pass_on_me()\n");
	current_level->get_sample(SFX_GRASS_EAT)->play();
	kill();
	return true;
}

bool Entity_Grass::explode()
{
	kill();
	//m_exists=false;
	return true;
}

