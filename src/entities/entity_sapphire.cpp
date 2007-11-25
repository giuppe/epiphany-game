/***************************************************************************
                          entity_sapphire.cpp  -  description
                             -------------------
    begin                : Mon Oct 1 2001
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
#include "entity.h"
#include "entity_sapphire.h"
#include "entity_manager.h"
#include "entity_player.h"
#include "entity_all.h"


Entity_Sapphire::Entity_Sapphire(Level* level, Uint32 x, Uint32 y)
{

	current_level=level;
	
	m_position_x=x;
	
	m_position_y=y;
	
	m_type=SAPPHIRE;
	
	Surface_Manager* surf_man = Surface_Manager::instance();
	m_sprite.init(surf_man->get_surface(Surface_Manager::SRF_SAPPHIRE));
	m_sprite.set_state(SP_STOP);
	m_is_falling=false;
	
	m_exists=true;
	
	m_value=3;
		
}

void Entity_Sapphire::check_and_do()
{

	bool was_falling=m_is_falling;
	Entity_Falling::check_and_do();
	if((was_falling==true)&&(m_is_falling==false))
	{
		Sample_Manager::instance()->play(SFX_SAPPHIRE_FALL);
	}
}
	
bool Entity_Sapphire::pass_on_me(Direction d)
{
	//BEGIN
	//gameplay hack
	//code to avoid player to eat from a column of falling sapphire
	if(m_is_falling==true)
		return false;
		
	Entity_Handle up_entity_id=current_level->get_entity(m_position_x, m_position_y, UP);
	if(up_entity_id!=0)
	{
		//Ntt_pointer up_entity=current_level->get_entity(up_entity_id);
		Entity_Falling* up_fall_entity=dynamic_cast<Entity_Falling*>(Entity_Manager::instance()->get_entity(up_entity_id));
		if((up_fall_entity)&&(up_fall_entity->is_falling()))
			return false;
	}
	//END
	current_level->get_player().inc_score(m_value);
	Sample_Manager::instance()->play(SFX_SAPPHIRE_EAT);
	kill();
	return true;
	
}

bool Entity_Sapphire::player_pressing_right(Entity_Handle left_entity)
{
	if(m_is_falling==true)
		return false;
	
		current_level->get_player().inc_score(m_value);
	Sample_Manager::instance()->play(SFX_SAPPHIRE_EAT);
	kill();
	return true;
}

bool Entity_Sapphire::player_pressing_left(Entity_Handle right_entity)
{
	if(m_is_falling==true)
		return false;
	
		current_level->get_player().inc_score(m_value);
	Sample_Manager::instance()->play(SFX_SAPPHIRE_EAT);
	kill();
	return true;
}

bool Entity_Sapphire::player_pressing_up(Entity_Handle down_entity)
{
	if(m_is_falling==true)
		return false;
	
		current_level->get_player().inc_score(m_value);
	Sample_Manager::instance()->play(SFX_SAPPHIRE_EAT);
	kill();
	return true;
}

bool Entity_Sapphire::player_pressing_down(Entity_Handle up_entity)
{
	if(m_is_falling==true)
		return false;
	
		current_level->get_player().inc_score(m_value);
	Sample_Manager::instance()->play(SFX_SAPPHIRE_EAT);
	kill();
	return true;
}


bool Entity_Sapphire::hit_from_up(Entity_Handle ntt)
{
	if(Entity_Manager::instance()->get_entity(ntt)->get_type()==BOULDER)
	{
		current_level->explode(m_position_x,m_position_y);

		kill();
		return false;
	//old function (w/o explosions)
	// m_exists=false;
//		return true;
	}
	return false;
}

bool Entity_Sapphire::explode()
{
	kill();
	return true;
}


