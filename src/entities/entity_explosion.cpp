/***************************************************************************
                          entity_explosion.cpp  -  description
                             -------------------
    begin                : Fri Apr 12 2002
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
#include "entity_explosion.h"
#include "entity_all.h"
#include "pointer.h"
#include "entity_type.h"

Entity_Explosion::Entity_Explosion(Level* level, unsigned int x, unsigned int y, Sprite& sprite, Entity_Type transform_to)
{
	current_level=level;
	m_position_x=x;
	m_position_y=y;
	m_type=EXPLOSION;
	m_sprite=(sprite);
	(m_sprite).set_pos_x(m_position_x*k_sprite_size);
	(m_sprite).set_pos_y(m_position_y*k_sprite_size);
//	m_sprite.move_to_pos(m_position_x*k_sprite_size,m_position_y*k_sprite_size);
	m_sprite.set_state(SP_STOP);
	m_exists=true;
	m_transform_to=transform_to;
	m_existing_count=1;

//	m_is_exploding=false;
//	m_just_checked=true;
}

void Entity_Explosion::check_and_do()
{

	if((m_existing_count==0))
	{
    kill();
		if(m_transform_to!=UNKNOWN)
		{
			current_level->set_entity(m_transform_to,m_position_x, m_position_y);
		}
		if(!(current_level->get_sample(SFX_EXPLOSION)->is_playing()))
		{
			current_level->get_sample(SFX_EXPLOSION)->play();
		}

		m_exists=false;


	}
	else
	{
		m_existing_count--;
	}
		
//	m_just_checked=true;
}

bool Entity_Explosion::explode()
{
//	m_existing_count--;
//	DEBOUT("entity exploding at "<<m_position_x<<", "<<m_position_y<<" with existing_count="<<m_existing_count<<"\n");
//  if(m_existing_count!=0)
	kill();
	

	return true;
}

