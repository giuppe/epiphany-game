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
 *   it under the terms of the GNU General Public License, Version 2, as published by  *
 *   the Free Software Foundation.                                   *
 *                                                                         *
 ***************************************************************************/
 

#include "dephine.h"
#include "entity.h"
#include "entity_door.h"
#include "entity_all.h"
#include "sfx.h"
#include "surface_manager.h"
#include <cassert>

Entity_Door::Entity_Door(Level* level, Uint32 x, Uint32 y, Uint32 id)
{
	current_level=level;
	m_position_x=x;
	m_position_y=y;
	m_type=DOOR;
	Surface_Manager* surf_man = Surface_Manager::instance();
	

	m_door_id=id;


	switch(m_door_id)
	{
	case 1:
		m_sprite.init(surf_man->get_surface(Surface_Manager::SRF_DOOR_RED));
		break;
	case 2:
		m_sprite.init(surf_man->get_surface(Surface_Manager::SRF_DOOR_BLUE));
		break;
	case 4:
		m_sprite.init(surf_man->get_surface(Surface_Manager::SRF_DOOR_GREEN));
		break;
	case 8:
		m_sprite.init(surf_man->get_surface(Surface_Manager::SRF_DOOR_YELLOW));
		break;
	default:
		assert(!"Error: Selected non existent door type.");
	}
	m_sprite.set_state(SP_STOP);
	m_sprite.start_animation();
	m_exists=true;
	m_is_open=false;

	
}
	
Uint32 Entity_Door::get_door_id()
{
	return m_door_id;
}



bool Entity_Door::player_pressing_up(Entity_Handle down_entity)
{
	if(m_is_open)
	{

		if(down_entity==0)
		{
			current_level->do_set_player_speed(2);
			current_level->do_player_move(DOWN);

			Sample_Manager::instance()->play(SFX_DOOR_PASS);
			return true;
		}
	}
	return false;
}

bool Entity_Door::player_pressing_down(Entity_Handle up_entity)
{
	if(m_is_open)
	{

		if(up_entity==0)
		{
			current_level->do_set_player_speed(2);
			current_level->do_player_move(UP);

			Sample_Manager::instance()->play(SFX_DOOR_PASS);
			return true;
		}
	}
	return false;
}


bool Entity_Door::player_pressing_left(Entity_Handle right_entity)
{
	if(m_is_open)
	{

		if(right_entity==0)
		{
			current_level->do_set_player_speed(2);
			current_level->do_player_move(RIGHT);

			Sample_Manager::instance()->play(SFX_DOOR_PASS);
			return true;
		}
	}
	return false;
}


bool Entity_Door::player_pressing_right(Entity_Handle left_entity)
{
	if(m_is_open)
	{

		if(left_entity==0)
		{
			current_level->do_set_player_speed(2);
			current_level->do_player_move(LEFT);

			Sample_Manager::instance()->play(SFX_DOOR_PASS);
			return true;
		}
	}
	return false;
}

	
void Entity_Door::check_and_do()
{
	if(m_just_checked==true)
	{

		
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

