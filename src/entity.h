/***************************************************************************
                          entity.h  -  description
                             -------------------
    begin                : Wed Aug 15 2001
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
#include "direction.h"
#include "entity_type.h"
#include "level.h"

#include "sprite.h"

#ifndef ENTITY_H
#define ENTITY_H

//Abstract class Entity is the base for creating whatever game object

class Entity
{
private:

	void m_set_position_x(unsigned int x);
	
	void m_set_position_y(unsigned int y);
	
protected:

	bool m_just_checked;

	Entity_Handle m_id;
	
	Entity_Type m_type;
	
	unsigned int m_position_x;
	
	unsigned int m_position_y;
	
	unsigned int m_speed;
	
	Sprite m_sprite;
	
	//true if player can pass it
//	bool m_is_passable;
		
	//True if an entity exists - not used
	bool m_exists;
	
	Level* current_level;
public:

	Entity();	

	Entity_Handle get_id();
	
	void set_id(Entity_Handle handle);

	unsigned int get_position_x();
	
	unsigned int get_position_y();
	
	Entity_Type get_type()
  {return m_type;};

	Sprite& get_sprite()
  {
	  return m_sprite;
	
  }
	
	void set_speed(unsigned int speed);
	
	void set_checked(bool check){m_just_checked=check;};
	
//	bool is_passable();
		
	void set_type(Entity_Type type);

	//moving function: calls the correct move_<dir>() function
	void move(Direction direction);	
	
	bool set_position(unsigned int x, unsigned int y);

	bool set_initial_position(unsigned int x, unsigned int y);
	// Moving functions - one for every direction
	
	void move_up();
	
	void move_down();
	
	void move_right();
	
	void move_left();
	
	bool exists(){return m_exists;};
	
	void kill();
		
	// Virtual functions
	
	// this function need to be overloaded in the derivative classes.
	//It is called by Game::move_all() for every existing object
	//and generally it contains some checks and calling to moving_functions
		virtual void check_and_do()=0;
		virtual bool pass_on_me(Direction d=STOP)=0;
		virtual bool smash(Entity_Handle ntt)=0;
		virtual bool explode()=0;
		virtual bool roll_on_me()=0;
		
		virtual ~Entity(){}
};
	



#endif //ENTITY_H
