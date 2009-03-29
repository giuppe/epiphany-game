/***************************************************************************
                          entity_peperon.cpp  -  description
                             -------------------
    begin                : Tue Apr 23 2002
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
#include "entity_monster.h"
#include "entity_peperon.h"
#include "entity_manager.h"
#include "entity_player.h"

Entity_Peperon::Entity_Peperon(Level* level, Uint32 x, Uint32 y)
{
	current_level=level;
	m_position_x=x;
	m_position_y=y;
	m_type=PEPERON;
	Surface_Manager* surf_man = Surface_Manager::instance();
	m_sprite.init(surf_man->get_surface(Surface_Manager::SRF_PEPERON));
	m_sprite.set_state(SP_STOP);
	m_sprite.start_animation();
	m_exists=true;
	m_is_exploding=false;
	m_state=ST_STOP;

}
	
void Entity_Peperon::check_and_do()
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
	
	Entity_Handle up_entity_id=current_level->get_entity(m_position_x, m_position_y, UP);	
	Entity_Handle right_entity_id=current_level->get_entity(m_position_x, m_position_y, RIGHT);
	Entity_Handle down_entity_id=current_level->get_entity(m_position_x, m_position_y, DOWN);
	Entity_Handle left_entity_id=current_level->get_entity(m_position_x, m_position_y, LEFT);
	
	if(((up_entity_id!=0)&&(Entity_Manager::instance()->get_entity(up_entity_id)->get_type()==PLAYER))||
		((right_entity_id!=0)&&(Entity_Manager::instance()->get_entity(right_entity_id)->get_type()==PLAYER))||
		((down_entity_id!=0)&&(Entity_Manager::instance()->get_entity(down_entity_id)->get_type()==PLAYER))||
		((left_entity_id!=0)&&(Entity_Manager::instance()->get_entity(left_entity_id)->get_type()==PLAYER)))
	{
		kill();
		current_level->do_player_stop();
		return;
	}
	
	switch(m_state)
	{
	case ST_MOVING_UP:
		if(right_entity_id!=0)
		{
			if(up_entity_id!=0)
			{
				m_state=ST_MOVING_LEFT;
			}
		}
		else
		{
			m_state=ST_MOVING_RIGHT;
		}
		break;
		
	case ST_MOVING_RIGHT:
		if(down_entity_id!=0)
		{
			if(right_entity_id!=0)
			{

				m_state=ST_MOVING_UP;
			}

		}
		else
		{
			m_state=ST_MOVING_DOWN;
		}
		break;
		
	case ST_MOVING_DOWN:
		if(left_entity_id!=0)
		{
			if(down_entity_id!=0)
			{

				m_state=ST_MOVING_RIGHT;
			}

		}
		else
		{
			m_state=ST_MOVING_LEFT;
		}
		break;
		
	case ST_MOVING_LEFT:
		if(up_entity_id!=0)
		{
			if(left_entity_id!=0)
			{
		
				m_state=ST_MOVING_DOWN;
			}

		}
		else
		{
			m_state=ST_MOVING_UP;
		}
		break;
		
	default:
		m_sprite.set_state(SP_STOP);
		m_state=ST_STOP;
	}
	if(m_state!=ST_STOP)
	{
		

		Sample_Manager::instance()->play(SFX_MONSTER_MOVE);
		if(can_move()){
			move();
		}
	}
		
	m_just_checked=true;
}
	
bool Entity_Peperon::hit_from_up(Entity_Handle smasher)
{
	if(Entity_Manager::instance()->get_entity(smasher)->get_type()==BOULDER)
	{
		kill();
		
	}
	return false;

}
	


void Entity_Peperon::kill()
{

	current_level->explode(m_position_x, m_position_y);

	
}	

void Entity_Peperon::explode_all_around()
{
	Entity::kill();
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


bool Entity_Peperon::explode()
{
	//explodes all entities around ;)
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
