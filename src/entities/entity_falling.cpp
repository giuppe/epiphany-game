/***************************************************************************
                          entity_falling.cpp  -  description
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
#include "entity.h"

#include "entity_falling.h"
#include "entity_player.h"
#include "entity_emerald.h"
#include "entity_manager.h"
#include "entity_boulder.h"
#include "level.h"


Entity_Falling::Entity_Falling(Level* level, Uint32 x, Uint32 y)
{
	current_level=level;
	m_position_x=x;
	m_position_y=y;
	m_type=UNKNOWN;
//	m_sprite=current_level.get_sprite(UNKNOWN);
m_state=ST_STOP;
	//m_is_falling=false;
	m_exists=true;
		
}

Entity_Falling::Entity_Falling()
{
	current_level=0;
	m_position_x=0;
	m_position_y=0;
	m_type=UNKNOWN;
	m_state=ST_STOP;

	//m_is_falling=false;
	m_exists=true;
		
}

void Entity_Falling::check_and_do()
{
	if(m_just_checked==true)
	{
		return;
	}
	//FIXME
	//WIN32 complains if these are set as references,
	//while in linux it runs smoothly
	Entity_Handle down_entity=current_level->get_entity(m_position_x,m_position_y, DOWN);
	
	if(down_entity!=0)
	{
		if(m_state==ST_MOVING_DOWN)
		{

			bool should_fall=current_level->do_hit(this->m_id, down_entity);
			m_state=(should_fall==true)?ST_MOVING_DOWN:ST_STOP;
		}
	}
	else
	{
		m_state=ST_MOVING_DOWN;
	}
	
	if(m_state==ST_MOVING_DOWN)
	{
		move(DOWN);
		
	}
	else
	{
			
		if((down_entity!=0)&&(Entity_Manager::instance()->get_entity(down_entity)->roll_on_me()))
		{
			Entity_Handle upright_entity=current_level->get_entity(m_position_x,m_position_y, UPRIGHT);
			Entity_Handle upleft_entity=current_level->get_entity(m_position_x,m_position_y, UPLEFT);
				
			if((current_level->get_entity(m_position_x, m_position_y, RIGHT)==0)&&
				 (current_level->get_entity(m_position_x,m_position_y, Direction(DOWN+RIGHT))==0)&&
				 ((upright_entity==0)||
				 (Entity_Manager::instance()->get_entity(upright_entity)->get_state()!=ST_MOVING_DOWN)))
				
			{
				roll(RIGHT);
			}
			else if((current_level->get_entity(m_position_x, m_position_y, LEFT)==0)&&
							(current_level->get_entity(m_position_x, m_position_y, Direction(DOWN+LEFT))==0)&&
							((upleft_entity==0)||
							(Entity_Manager::instance()->get_entity(upleft_entity)->get_state()!=ST_MOVING_DOWN)))
			{
				roll(LEFT);
			
			}
		}
				
	}
	
	if(m_state!=ST_MOVING_DOWN)
	{
		m_sprite.set_state(SP_STOP);
		m_state=ST_STOP;

	}
	
	set_position(m_position_x, m_position_y);
	
	m_just_checked=true;

}



bool Entity_Falling::is_falling()
{

	return m_state==ST_MOVING_DOWN;
	
}


void Entity_Falling::roll(Direction direction)
{


	move(direction);
	m_just_checked=true;
	m_state=ST_MOVING_DOWN;
}

bool Entity_Falling::roll_on_me()
{
	if(m_state==ST_MOVING_DOWN)
		return false;

	return true;
}
