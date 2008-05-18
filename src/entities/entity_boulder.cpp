/***************************************************************************
                          entity_boulder.cpp  -  description
                             -------------------
    begin                : Thu Sep 20 2001
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
	m_sprite.init(surf_man->get_surface(Surface_Manager::SRF_BOULDER));
	m_sprite.set_state(SP_STOP);
	m_state=ST_STOP;
	m_sprite.start_animation();
	//m_is_falling=false;
	m_exists=true;

		
}

void Entity_Boulder::check_and_do()
{
  bool was_falling=(m_state==ST_MOVING_DOWN);
	Entity_Falling::check_and_do();
	if((was_falling==true)&&(m_state==ST_STOP))
	{
		Sample_Manager::instance()->play(SFX_BOULDER_FALL);
	}
}


bool Entity_Boulder::player_pressing_left(Entity_Handle right_entity)
{
	if((right_entity==0)&&(m_state!=ST_MOVING_DOWN))
	{
		move(RIGHT);
		m_just_checked=true;
		m_state=ST_MOVING_DOWN;
		return true;
	}
	return false;
}

bool Entity_Boulder::player_pressing_right(Entity_Handle left_entity)
{
	if((left_entity==0)&&(m_state!=ST_MOVING_DOWN))
	{
		move(LEFT);
		m_just_checked=true;
		m_state=ST_MOVING_DOWN;
	
		return true;
	}
	return false;
}

bool Entity_Boulder::explode()
{
	m_exists=false;
	return true;
}
