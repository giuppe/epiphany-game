/***************************************************************************
                          entity_exit.cpp  -  description
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
#include "sprite.h"
#include "entity.h"
#include "entity_exit.h"
#include "entity_player.h"
#include "level.h"

Entity_Exit::Entity_Exit(Level* level, Uint32 x, Uint32 y, Uint32 min_score)
{
	current_level=level;

	m_is_open=false;
	
	m_type=EXIT;
	
	m_exists=true;

	m_position_x=x;
	
	m_position_y=y;
		
	Surface_Manager* surf_man = Surface_Manager::instance();
	m_sprite.init(surf_man->get_surface(Surface_Manager::SRF_EXIT));
	m_sprite.set_state(SP_STOP);
	m_sprite.start_animation();

	
	m_min_score=min_score;
	
}

bool Entity_Exit::is_open()
{

	return m_is_open;
	
}

void Entity_Exit::check_and_do()
{
	if(m_just_checked==true)
		return;
	
	if(current_level->get_current_score()>=m_min_score)
	{
		m_is_open=true;
		m_sprite.set_state(SP_UP);
	}
	else
		m_is_open=false;
		
	m_just_checked=true;
		
}



bool Entity_Exit::player_pressing_up(Entity_Handle down_entity)
{

	if(m_is_open)
	{
		kill();
		// player wins...
		current_level->do_win_level();
		return true;
	}
	return false;
}


bool Entity_Exit::player_pressing_down(Entity_Handle up_entity)
{

	if(m_is_open)
	{
		kill();
		// player wins...
		current_level->do_win_level();
		return true;
	}
	return false;
}


bool Entity_Exit::player_pressing_left(Entity_Handle right_entity)
{

	if(m_is_open)
	{
		kill();
		// player wins...
		current_level->do_win_level();
		return true;
	}
	return false;
}


bool Entity_Exit::player_pressing_right(Entity_Handle left_entity)
{

	if(m_is_open)
	{
		kill();
		// player wins...
		current_level->do_win_level();
		return true;
	}
	return false;
}


void Entity_Exit::set_min_score(Uint32 min_score)
{
	m_min_score=min_score;
}

Uint32 Entity_Exit::get_min_score()
{

	return m_min_score;
	
}
	
bool Entity_Exit::explode()
{
	return false;
}


