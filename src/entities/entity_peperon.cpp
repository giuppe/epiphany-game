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
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "dephine.h"
#include "entity.h"
#include "entity_monster.h"
#include "entity_peperon.h"
#include "entity_player.h"

Entity_Peperon::Entity_Peperon(Level* level, unsigned int x, unsigned int y, Sprite& sprite, Direction direction)
{
	current_level=level;
	m_position_x=x;
	m_position_y=y;
	m_type=PEPERON;
	m_sprite=(sprite);
	(m_sprite).set_pos_x(m_position_x*k_sprite_size);
	(m_sprite).set_pos_y(m_position_y*k_sprite_size);
	m_sprite.set_state(SP_STOP);
	m_exists=true;
	m_direction=direction;

}
	
void Entity_Peperon::check_and_do()
{
	if(m_just_checked==true)
	{
	//	m_just_moved=false;
		
		return;
	}
	
	if(m_is_exploding==true)
	{

		explode_all_around();	
		return;
	}
	
	unsigned int up_entity_id=current_level->get_entity_id(m_position_x, m_position_y, UP);	
	unsigned int right_entity_id=current_level->get_entity_id(m_position_x, m_position_y, RIGHT);
	unsigned int down_entity_id=current_level->get_entity_id(m_position_x, m_position_y, DOWN);
	unsigned int left_entity_id=current_level->get_entity_id(m_position_x, m_position_y, LEFT);
	
	if(((up_entity_id!=0)&&(current_level->get_entity(up_entity_id)->get_type()==PLAYER))||
		((right_entity_id!=0)&&(current_level->get_entity(right_entity_id)->get_type()==PLAYER))||
		((down_entity_id!=0)&&(current_level->get_entity(down_entity_id)->get_type()==PLAYER))||
		((left_entity_id!=0)&&(current_level->get_entity(left_entity_id)->get_type()==PLAYER)))
	{
		kill();
		current_level->get_player().set_direction(STOP);
		return;
	}
	
	switch(m_direction)
	{
	case UP:
		if(right_entity_id!=0)
		{
			if(up_entity_id==0)
			{
			//		move(UP);
			}
			else
			{
				m_direction=LEFT;
			}
		}
		else
		{
			m_direction=RIGHT;
		}
		break;
		
	case RIGHT:
		if(down_entity_id!=0)
		{
			if(right_entity_id==0)
			{
			//		move(RIGHT);
			}
			else
			{
				m_direction=UP;
			}
		}
		else
		{
			m_direction=DOWN;
		}
		break;
		
	case DOWN:
		if(left_entity_id!=0)
		{
			if(down_entity_id==0)
			{
			//		move(DOWN);
			}
			else
			{
				m_direction=RIGHT;
			}
		}
		else
		{
			m_direction=LEFT;
		}
		break;
		
	case LEFT:
		if(up_entity_id!=0)
		{
			if(left_entity_id==0)
			{
			//		move(LEFT);
			}
			else
			{
				m_direction=DOWN;
			}
		}
		else
		{
			m_direction=UP;
		}
		break;
		
	default:
		m_sprite.set_state(SP_STOP);
	}
	if(current_level->get_entity_id(m_position_x, m_position_y, m_direction)==0)
	{
		if(!(current_level->get_sample(SFX_MONSTER_MOVE)->is_playing()))
		{
			current_level->get_sample(SFX_MONSTER_MOVE)->play();
		}
		move(m_direction);

	}
		
	m_just_checked=true;
}
	
bool Entity_Peperon::smash(Ntt_pointer& smasher)
{
	if(smasher->get_type()==BOULDER)
	{
		kill();
		
	}
	return false;

}
	
bool Entity_Peperon::pass_on_me(Direction d)
{
	return false;
}

void Entity_Peperon::kill()
{
//	m_exists=false;
//    Entity::kill();
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
	
//	m_exists=false;
//	current_level->explode(m_position_x-1,m_position_y-1);
//	current_level->explode(m_position_x,m_position_y-1);
//	current_level->explode(m_position_x+1,m_position_y-1);
//	current_level->explode(m_position_x-1,m_position_y);
//	current_level->explode(m_position_x,m_position_y);
//	current_level->explode(m_position_x+1,m_position_y);
//	current_level->explode(m_position_x-1,m_position_y+1);
//	current_level->explode(m_position_x,m_position_y+1);
//	current_level->explode(m_position_x+1,m_position_y+1);
	return true;
}
