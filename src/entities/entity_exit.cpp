/***************************************************************************
                          entity_exit.cpp  -  description
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
	//TODO: check boundaries
	m_position_x=x;
	
	m_position_y=y;
		
	Surface_Manager* surf_man = Surface_Manager::instance();
	m_sprite=Sprite(surf_man->get_surface(Surface_Manager::SRF_EXIT));
	(m_sprite).set_pos_x(m_position_x*k_sprite_size);
	(m_sprite).set_pos_y(m_position_y*k_sprite_size);
	m_sprite.set_state(SP_STOP);

	
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
	
	if(current_level->get_player().get_score()>=m_min_score)
	{
		m_is_open=true;
		m_sprite.set_state(SP_UP);
	}
	else
		m_is_open=false;
		
	m_just_checked=true;
		
}

bool Entity_Exit::pass_on_me(Direction d)
{
	if(m_is_open)
	{
		kill();
		// player wins...
		current_level->get_player().win();
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


