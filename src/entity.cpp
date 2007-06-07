/***************************************************************************
                          entity.cpp  -  description
                             -------------------
    begin                : Tue Aug 28 2001
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
#include "pointer.h"

//int glb_curr_id=1;

Entity::Entity()
{
	//m_id=glb_curr_id;
	//glb_curr_id++;
	set_speed(1);
	m_just_checked=false;
	
}

void Entity::set_id(Entity_Handle handle)
{
	m_id = handle;
}

Entity_Handle Entity::get_id()
{
	return m_id;
}

/*
void Entity::m_set_position_x(unsigned int x)
{

	if((x>=current_level->get_size_x())||(x<0))
		Common_Ex::throw_common("Entity x position outside level.\n");
	
	m_position_x=x;
//	m_sprite.set_pos_x(x*k_sprite_size);

}

void Entity::m_set_position_y(unsigned int y)
{

	if((y>=current_level->get_size_y())||(y<0))
		Common_Ex::throw_common("Entity y position outside level.\n");
	
	m_position_y=y;
	//	m_sprite.set_pos_y(y*k_sprite_size);

}
*/
unsigned int Entity::get_position_x()
{

	return m_position_x;	

}

unsigned int Entity::get_position_y()
{

	return m_position_y;	

}
/*
Entity_Type Entity::get_type()
{
	//DEBOUT("Entering get_type()...\n");
	return m_type;	
}
*/
void Entity::set_type(Entity_Type type)
{
	
	m_type=type;
	
}

void Entity::set_speed(unsigned int speed)
{
	m_speed=speed;
	m_sprite.set_speed(m_speed);
}

void Entity::kill()
{
		m_exists=false;
//		set_position(0,0);
		current_level->get_entities_matrix()[m_position_x][m_position_y]=0;
}

bool Entity::set_position(unsigned int x, unsigned int y)
{
	if(((x>=current_level->get_size_x())||(x<0))||((y>=current_level->get_size_y())||(y<0)))
			return false;	
//	current_level->get_entities_matrix()[m_position_x][m_position_y]=0;
				
//	m_set_position_x(x);
//	m_set_position_y(y);
	m_position_x=x;
	m_position_y=y;
	
	current_level->get_entities_matrix()[m_position_x][m_position_y]=m_id;
//	current_level->set_entity(this);

	return true;
	
}

bool Entity::set_initial_position(unsigned int x, unsigned int y)
{
	if(((x>=current_level->get_size_x())||(x<0))||((y>=current_level->get_size_y())||(y<0)))
			return false;	
//	current_level->get_entities_matrix()[m_position_x][m_position_y]=0;
				
//	m_set_position_x(x);
//	m_set_position_y(y);
	m_position_x=x;
	m_position_y=y;
	
	(m_sprite).set_pos_x(m_position_x*k_sprite_size);
	(m_sprite).set_pos_y(m_position_y*k_sprite_size);
	m_sprite.set_state(SP_STOP);
	
	//current_level->get_entities_matrix()[m_position_x][m_position_y]=m_id;
//	current_level->set_entity(this);

	return true;
	
}

	
//la funzione move() serve a scegliere la funzione adatta a muoversi
void Entity::move(Direction direction)
{
	#ifdef DEBUG_MODE
		if(current_level->get_entity(m_position_x, m_position_y, direction)!=0)
			DEBOUT("Alert: moving over a referenced entity: from ("<<m_position_x<<", "<<m_position_y<<"), dir: "<<direction<<"\n");
	#endif
		switch(direction)
		{
	
		case UP:
			move_up();
			break;

		case RIGHT:
			move_right();
			break;
	
		case DOWN:
			move_down();
			break;
		
		case LEFT:
			move_left();
			break;	
		
		default:
			break;
		
	
		
	}
	
}

//C'è una funzione per ogni movimento poichè poi bisogna aggiungere le animazioni
void Entity::move_up()
{
	unsigned int new_position_x=m_position_x;
	unsigned int new_position_y=m_position_y-1;	

	set_position(new_position_x, new_position_y);
	m_sprite.move_to_pos(new_position_x*k_sprite_size, new_position_y*k_sprite_size);
	m_sprite.set_state(SP_UP);
		
}

void Entity::move_down()
{
	
	unsigned int new_position_x=m_position_x;
	unsigned int new_position_y=m_position_y+1;	

	set_position(new_position_x, new_position_y);
	m_sprite.move_to_pos(new_position_x*k_sprite_size, new_position_y*k_sprite_size);
	m_sprite.set_state(SP_DOWN);
}

void Entity::move_right()
{
	
	unsigned int new_position_x=m_position_x+1;
	unsigned int new_position_y=m_position_y;	

	set_position(new_position_x, new_position_y);
	m_sprite.move_to_pos(new_position_x*k_sprite_size, new_position_y*k_sprite_size);
	m_sprite.set_state(SP_RIGHT);
}

void Entity::move_left()
{
	unsigned int new_position_x=m_position_x-1;
	unsigned int new_position_y=m_position_y;	

	set_position(new_position_x, new_position_y);
	m_sprite.move_to_pos(new_position_x*k_sprite_size, new_position_y*k_sprite_size);
	m_sprite.set_state(SP_LEFT);
}


/*
Sprite& Entity::get_sprite()
{
	return m_sprite;
	
}
*/
/*
bool Entity::exists()
{
	return m_exists;
}
 */
