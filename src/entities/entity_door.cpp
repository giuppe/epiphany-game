/***************************************************************************
                          entity_door.cpp  -  description
                             -------------------
    begin                : Thu Apr 18 2002
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
#include "entity_door.h"
#include "entity_all.h"

Entity_Door::Entity_Door(Level* level, unsigned int x, unsigned int y, Sprite& sprite, unsigned int id)
{
	current_level=level;
	m_position_x=x;
	m_position_y=y;
	m_type=DOOR;
	m_sprite=sprite;
	(m_sprite).set_pos_x(m_position_x*k_sprite_size);
	(m_sprite).set_pos_y(m_position_y*k_sprite_size);
	m_door_id=id;
	switch(m_door_id)
	{
	case 1:
		m_sprite.set_state(SP_STOP);
		break;
	case 2:
		m_sprite.set_state(SP_UP);
		break;
	case 4:
		m_sprite.set_state(SP_RIGHT);
		break;
	case 8:
		m_sprite.set_state(SP_DOWN);
		break;
	}
	m_exists=true;
	m_is_open=false;

	
}
	
unsigned int Entity_Door::get_door_id()
{
	return m_door_id;
}

bool Entity_Door::pass_on_me(Direction d)
{
	if(m_is_open)
	{
//		kill();
		if(current_level->get_entity(m_position_x, m_position_y, d).is_referenced()==false)
		{
			current_level->get_player().set_speed(2);
			current_level->get_player().move(d);
			//current_level->get_player().set_direction(d);
			current_level->get_sample(SFX_DOOR_PASS)->play();
			return true;
		}
	}
	return false;
}

	
void Entity_Door::check_and_do()
{
	if(m_just_checked==true)
	{
	//	m_just_moved=false;
		
		return;
	}
	if(((current_level->get_acquired_keys())&(m_door_id))==(m_door_id))
		m_is_open=true;
	set_position(m_position_x, m_position_y);
	
	m_just_checked=true;

}

bool Entity_Door::explode()
{
	return false;
}

