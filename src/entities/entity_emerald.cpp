/***************************************************************************
                          entity_emerald.cpp  -  description
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
#include "entity.h"
#include "entity_emerald.h"
#include "entity_manager.h"
#include "entity_player.h"
#include "entity_falling.h"


Entity_Emerald::Entity_Emerald(Level* level,Uint32 x, Uint32 y)
{
	
	current_level=level;
	
	m_position_x=x;
	
	m_position_y=y;
	
	m_type=EMERALD;
	
	Surface_Manager* surf_man = Surface_Manager::instance();
	m_sprite.init(surf_man->get_surface(Surface_Manager::SRF_EMERALD));
	m_sprite.set_state(SP_STOP);
	m_sprite.start_animation();
	m_state=ST_STOP;
	
	m_exists=true;
	
	m_value=1;
		
}

void Entity_Emerald::check_and_do()
{

	bool was_falling=(m_state==ST_MOVING_DOWN);
	Entity_Falling::check_and_do();
	
	if((was_falling==true)&&(m_state==ST_STOP))
	{
		Sample_Manager::instance()->play(SFX_EMERALD_FALL);
	}
	
}
	


bool Entity_Emerald::player_pressing_right(Entity_Handle left_entity)
{
	if(m_state==ST_MOVING_DOWN)
		return false;
	
	current_level->do_inc_player_score(m_value);
	Sample_Manager::instance()->play(SFX_EMERALD_EAT);
	kill();
	return true;
}

bool Entity_Emerald::player_pressing_left(Entity_Handle right_entity)
{
	if(m_state==ST_MOVING_DOWN)
		return false;
	
	current_level->do_inc_player_score(m_value);
	Sample_Manager::instance()->play(SFX_EMERALD_EAT);
	kill();
	return true;
}

bool Entity_Emerald::player_pressing_up(Entity_Handle down_entity)
{
	if(m_state==ST_MOVING_DOWN)
		return false;
	
	current_level->do_inc_player_score(m_value);
	Sample_Manager::instance()->play(SFX_EMERALD_EAT);
	kill();
	return true;
}

bool Entity_Emerald::player_pressing_down(Entity_Handle up_entity)
{
	if(m_state==ST_MOVING_DOWN)
		return false;
	
	current_level->do_inc_player_score(m_value);
	Sample_Manager::instance()->play(SFX_EMERALD_EAT);
	kill();
	return true;
}
	

bool Entity_Emerald::explode()
{
	kill();
	return true;
}

