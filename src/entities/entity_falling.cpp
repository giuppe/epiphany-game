/***************************************************************************
                          entity_falling.cpp  -  description
                             -------------------
    begin                : Mon Oct 1 2001
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
#include "entity.h"
#include "pointer.h"
#include "entity_falling.h"
#include "entity_player.h"
#include "entity_emerald.h"
#include "entity_boulder.h"
#include "level.h"


Entity_Falling::Entity_Falling(Level* level, unsigned int x, unsigned int y)
{
	current_level=level;
	m_position_x=x;
	m_position_y=y;
	m_type=UNKNOWN;
//	m_sprite=current_level.get_sprite(UNKNOWN);

	m_is_falling=false;
	m_exists=true;
		
}

Entity_Falling::Entity_Falling()
{
	current_level=0;
	m_position_x=0;
	m_position_y=0;
	m_type=UNKNOWN;
	m_sprite=0;

	m_is_falling=false;
	m_exists=true;
		
}

void Entity_Falling::check_and_do()
{
	if(m_just_checked==true)
	{
		return;
	}
	//HACKSOMETHINGHERE
	//WIN32 complains if these are set as references,
	//while in linux it runs smoothly
	Ntt_pointer down_entity=current_level->get_entity(m_position_x,m_position_y, DOWN);
	Ntt_pointer up_entity=current_level->get_entity(m_position_x,m_position_y, UP);

	if(down_entity.is_referenced())
	{
		if(m_is_falling)
		{
			Ntt_pointer temp(*this);
			m_is_falling=down_entity->smash(temp);
		}
	}
	else
	{
		m_is_falling=true;
	}
	
	if(m_is_falling)
	{
		move(DOWN);
		
	}
	else
	{
	//	if(((current_level->get_entity(m_position_x, m_position_y, RIGHT).is_referenced()==false)&&
	//		(current_level->get_entity(m_position_x,m_position_y, Direction(DOWN+RIGHT)).is_referenced()==false))||
	//		((current_level->get_entity(m_position_x, m_position_y, LEFT).is_referenced()==false)&&
	//						(current_level->get_entity(m_position_x, m_position_y, Direction(DOWN+LEFT)).is_referenced()==false)))
			
		if((down_entity.is_referenced())&&(down_entity->roll_on_me()))
		{
			Ntt_pointer upright_entity=current_level->get_entity(m_position_x,m_position_y, UPRIGHT);
			Ntt_pointer upleft_entity=current_level->get_entity(m_position_x,m_position_y, UPLEFT);
				
			if((current_level->get_entity(m_position_x, m_position_y, RIGHT).is_referenced()==false)&&
				 (current_level->get_entity(m_position_x,m_position_y, Direction(DOWN+RIGHT)).is_referenced()==false)&&
				 ((upright_entity.is_referenced()==false)||
				 (!dynamic_cast<Entity_Falling*>(upright_entity.get_pointer()))))
				
			{
				roll(RIGHT);
			}
			else if((current_level->get_entity(m_position_x, m_position_y, LEFT).is_referenced()==false)&&
							(current_level->get_entity(m_position_x, m_position_y, Direction(DOWN+LEFT)).is_referenced()==false)&&
							((upleft_entity.is_referenced()==false)||
							(!dynamic_cast<Entity_Falling*>(upleft_entity.get_pointer()))))
			{
				roll(LEFT);
			
			}
		}
				
	}
	
	if(m_is_falling==false)
	{
		m_sprite.set_state(SP_STOP);

	}
	
	set_position(m_position_x, m_position_y);
	
	m_just_checked=true;

}



bool Entity_Falling::is_falling()
{

	return m_is_falling;
	
}


void Entity_Falling::roll(Direction direction)
{
//	if(current_level->get_entity_id(m_position_x, m_position_y, direction)==0)
//	{
	m_is_falling=true;
	move(direction);	
//		switch(direction)
//		{
//		case LEFT:
//			move_left();
//			break;
//		case RIGHT:
//			move_right();
//		break;
			
//		}
	//}
}

bool Entity_Falling::roll_on_me()
{
	if(m_is_falling)
		return false;
//	m_just_checked=true;
	return true;
}
