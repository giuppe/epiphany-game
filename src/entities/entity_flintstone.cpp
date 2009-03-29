/***************************************************************************
                          entity_flintstone.cpp  -  description
                             -------------------
    begin                : Fri Apr 19 2002
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
#include "sprite.h"
#include "entity.h"
#include "entity_flintstone.h"
#include "entity_manager.h"
#include "entity_player.h"


Entity_Flintstone::Entity_Flintstone(Level* level, Uint32 x, Uint32 y)
{
	current_level=level;
	m_position_x=x;
	m_position_y=y;
	m_type=FLINTSTONE;
	Surface_Manager* surf_man = Surface_Manager::instance();
	m_sprite.init(surf_man->get_surface(Surface_Manager::SRF_FLINTSTONE));
	m_sprite.set_state(SP_STOP);
	m_sprite.start_animation();
	m_state=ST_STOP;
	//m_is_falling=false;
	m_exists=true;
	m_just_checked=false;
	m_is_exploding=false;
		
}

void Entity_Flintstone::explode_all_around()
{
	kill();
	current_level->explode(m_position_x-1,m_position_y-1);
	current_level->explode(m_position_x,m_position_y-1);
	current_level->explode(m_position_x+1,m_position_y-1);
	current_level->explode(m_position_x-1,m_position_y);
	current_level->explode(m_position_x,m_position_y);
	current_level->explode(m_position_x+1,m_position_y);
	current_level->explode(m_position_x-1,m_position_y+1);
	current_level->explode(m_position_x,m_position_y+1);
	current_level->explode(m_position_x+1,m_position_y+1);
}


void Entity_Flintstone::check_and_do()
{
	if(m_just_checked==true)
	{
		return;
	}
	
	if(m_is_exploding==true)
	{

		explode_all_around();	
		return;
	}


	Entity_Handle down_entity_id=current_level->get_entity(m_position_x,m_position_y, DOWN);
	if(down_entity_id!=0)
	{
		if(m_state==ST_MOVING_DOWN)
		{
			current_level->explode(m_position_x, m_position_y);
		}
	}
	bool was_falling=(m_state==ST_MOVING_DOWN);
	Entity_Falling::check_and_do();
	
	if((was_falling==true)&&(m_state==ST_STOP))
	{
		current_level->explode(m_position_x, m_position_y);
	}
	
	
	m_just_checked=true;
}


bool Entity_Flintstone::player_pressing_left(Entity_Handle right_entity)
{
	if((right_entity==0)&&(m_state!=ST_MOVING_DOWN))
	{
		move(RIGHT);
		m_just_checked=true;
		if((current_level->get_entity(get_position_x(), get_position_y(), DOWN))==0)
			m_state=ST_MOVING_DOWN;	
		return true;
	}
	return false;
}

bool Entity_Flintstone::player_pressing_right(Entity_Handle left_entity)
{
	if((left_entity==0)&&(m_state!=ST_MOVING_DOWN))
	{
		move(LEFT);
		m_just_checked=true;
		if((current_level->get_entity(get_position_x(), get_position_y(), DOWN))==0)
			m_state=ST_MOVING_DOWN;	
		return true;
	}
	return false;
}




bool Entity_Flintstone::hit_from_up(Entity_Handle smasher)
{
	//kill();
	if(Entity_Manager::instance()->get_entity(smasher)->get_type()==BOULDER)
		current_level->explode(m_position_x, m_position_y);
	return false;
}

bool Entity_Flintstone::explode()
{
	

	if(m_just_checked==true)
	{
		m_is_exploding=true;
	}
	else
	{
		m_is_exploding=true;
		m_just_checked=true;
	}

			

	return true;
}	
