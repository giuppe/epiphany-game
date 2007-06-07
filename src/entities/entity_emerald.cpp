/***************************************************************************
                          entity_emerald.cpp  -  description
                             -------------------
    begin                : Thu Sep 20 2001
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
#include "entity_emerald.h"
#include "entity_manager.h"
#include "entity_player.h"
#include "entity_falling.h"


Entity_Emerald::Entity_Emerald(Level* level,unsigned int x, unsigned int y, Sprite& sprite)
{
	
	current_level=level;
	
	m_position_x=x;
	
	m_position_y=y;
	
	m_type=EMERALD;
	
	m_sprite=(sprite);
	(m_sprite).set_pos_x(m_position_x*k_sprite_size);
	(m_sprite).set_pos_y(m_position_y*k_sprite_size);
	m_sprite.set_state(SP_STOP);
	m_is_falling=false;
	
	m_exists=true;
	
	m_value=1;
		
}

void Entity_Emerald::check_and_do()
{

  bool was_falling=m_is_falling;
	Entity_Falling::check_and_do();
	if((was_falling==true)&&(m_is_falling==false))
	{
		current_level->get_sample(SFX_EMERALD_FALL)->play();
	}
	
}
	
bool Entity_Emerald::pass_on_me(Direction d)
{
	//DEBOUT("Entering Entity_Emerald::pass_on_me()\n");
	//BEGIN
	//gameplay hack
	//code to avoid player to eat from a column of falling emeralds
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
	current_level->get_sample(SFX_EMERALD_EAT)->play();
	kill();
	return true;
}

bool Entity_Emerald::explode()
{
	kill();
	return true;
}

