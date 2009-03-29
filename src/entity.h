/***************************************************************************
                          entity.h  -  description
                             -------------------
    begin                : Wed Aug 15 2001
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
#include "direction.h"
#include "entity_type.h"
#include "level.h"
#include "surface_manager.h"
#include "sprite.h"
#include <vector>

#ifndef ENTITY_H
#define ENTITY_H
using namespace std;
/*
 * Abstract class Entity is the base for creating game objects
*/
class Entity
{
private:

	void m_set_position_x(Uint32 x);
	
	void m_set_position_y(Uint32 y);
	
protected:

	bool m_just_checked;

	Entity_Handle m_id;
	
	Entity_Type m_type;
	
	Uint32 m_position_x;
	
	Uint32 m_position_y;
	
	Uint32 m_speed;
	
	Sprite m_sprite;
	
	vector<Sprite> m_sprites;
	friend class Entity_Factory;
	enum Entity_State{ST_STOP, 
		ST_MOVING_UP, 
		ST_MOVING_LEFT, 
		ST_MOVING_DOWN, 
		ST_MOVING_RIGHT,
		ST_DISAPPEARING,
		ST_EXPLODING
	};
	Entity_State m_state;
	
		
	//True if an entity exists - not used
	bool m_exists;
	
	Level* current_level;
	
	Sprite& get_sprite()
	{
		return m_sprite;
	}
	
	Sprite& get_sprite(Entity_State state);
	
	//void refresh_sprite();
	
public:

	Entity();	

	Entity_Handle get_id();
	
	void set_id(Entity_Handle handle);

	Uint32 get_position_x();
	
	Uint32 get_position_y();
	
	Entity_Type get_type()
	{
		return m_type;
	}

	


	
	void move_sprite()
	{
		m_sprite.move();
	}
	
	WorldCoord get_sprite_position()
	{
		return m_sprite.get_position();
	}

	void set_speed(Uint32 speed);
	
	void set_checked(bool check){m_just_checked=check;};
	
		
	void set_type(Entity_Type type);

	//moving function: calls the correct move_<dir>() function
	void move(Direction direction);	
	
	bool set_position(Uint32 x, Uint32 y);

	bool set_initial_position(Uint32 x, Uint32 y);
	// Moving functions - one for every direction
	
	void move();

	bool can_move();
	
	void move_up();
	
	void move_down();
	
	void move_right();
	
	void move_left();
	
	bool exists(){return m_exists;};
	
	void kill();
	
	void clear_bg();
	
	void update_bg();
	
	void draw_on_screen();
	
	Entity_State get_state();
	
	void set_state(Entity_State state);
	// Virtual functions
	
	// this function need to be overloaded in the derivative classes.
	//It is called by Game::move_all() for every existing object
	//and generally it contains some checks and calling to moving_functions
		virtual void check_and_do()=0;

		virtual bool player_pressing_up(Entity_Handle down_entity);
		virtual bool player_pressing_left(Entity_Handle right_entity);
		virtual bool player_pressing_right(Entity_Handle left_entity);
		virtual bool player_pressing_down(Entity_Handle up_entity);
		virtual bool hit_from_up(Entity_Handle ntt)=0;
		virtual bool explode()=0;
		virtual bool roll_on_me()=0;
		
		virtual ~Entity(){}
};
	



#endif //ENTITY_H
