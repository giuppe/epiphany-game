/***************************************************************************
                          entity_boulder.cpp  -  description
                             -------------------
    begin                : Thu Sep 20 2001
    copyright            : (C) 2001 by Giuseppe D'Aquì
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
#include "sprite.h"
#include "surface_manager.h"
#include "entity.h"
#include "entity_boulder.h"
#include "entity_player.h"


Entity_Boulder::Entity_Boulder(Level* level, Uint32 x, Uint32 y)
{
	current_level=level;
	m_position_x=x;
	m_position_y=y;
	m_type=BOULDER;
	Surface_Manager* surf_man = Surface_Manager::instance();
	m_sprite=Sprite(surf_man->get_surface(Surface_Manager::SRF_BOULDER));
	(m_sprite).set_pos_x(m_position_x*k_sprite_size);
	(m_sprite).set_pos_y(m_position_y*k_sprite_size);
	m_sprite.set_state(SP_STOP);
	m_is_falling=false;
	m_exists=true;

		
}

void Entity_Boulder::check_and_do()
{
  bool was_falling=m_is_falling;
	Entity_Falling::check_and_do();
	if((was_falling==true)&&(m_is_falling==false))
	{
		Sample_Manager::instance()->play(SFX_BOULDER_FALL);
	}
}

bool Entity_Boulder::pass_on_me(Direction d)
{

	if(((d==RIGHT)||(d==LEFT))&&(m_is_falling==false))
	{
		if((current_level->get_entity(get_position_x(), get_position_y(), d))==0)
		{
			move(d);
			m_just_checked=true;
				if((current_level->get_entity(get_position_x(), get_position_y(), DOWN))==0)
					m_is_falling=true;		
			return true;
		}
	}
	return false;
	
}

bool Entity_Boulder::explode()
{
	m_exists=false;
	return true;
}
