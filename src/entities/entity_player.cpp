/***************************************************************************
                          entity_player.cpp  -  description
                             -------------------
    begin                : Thu Sep 20 2001
    copyright            : (C) 2001 by Giuseppe D'Aquì
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
#include "entity_manager.h"

#include "entity_all.h"


Entity_Player::Entity_Player(Level* level, Uint32 x, Uint32 y)
{
	
	m_type=PLAYER;
	
	current_level=level;
	

	
	if((x<current_level->get_size_x())&&(x>=0))
		m_position_x=x;
	else
		m_position_x=0;
		
	if((y<current_level->get_size_y())&&(y>=0))
		m_position_y=y;
	else
		m_position_y=0;
	
	Surface_Manager* surf_man = Surface_Manager::instance();
	m_sprite=Sprite(surf_man->get_surface(Surface_Manager::SRF_PLAYER));
	m_sprite.set_state(SP_STOP);
	m_score=0;
		
	m_exists=true;
		
	m_is_exited=false;
		
	m_is_alive=true;
	
	m_is_snapping=false;
	
	m_direction=STOP;
	
}

void Entity_Player::set_direction(Direction d)
{
	m_direction=d;
}

void Entity_Player::set_snap(bool snap)
{
	m_is_snapping=snap;

}

void Entity_Player::inc_score(int score)
{
	m_score+=score;
}

void Entity_Player::check_and_do()
{
	if(m_just_checked==true)
	{
	//	m_just_moved=false;
		
		return;
	}
	if(m_is_exited)	
	{
		kill();
		return;
	}
	
	//adesso controlla che di lato ci sia una casella vuota
	//oppure un oggetto passabile
	if(m_direction==STOP)
	{
		m_sprite.set_state(SP_STOP);
	}
	
	if(current_level->player_push(m_position_x, m_position_y, m_direction))
	{
		if(!m_is_snapping)
			move(m_direction);
	}
	else
	{
		m_sprite.set_state(SP_STOP);
	}

/*	Entity* neigh_entity;	
	
	Entity_Handle neigh_entity_id=current_level->get_entity(m_position_x,m_position_y, m_direction);
	if(neigh_entity_id!=0)
	{
		neigh_entity=Entity_Manager::instance()->get_entity(neigh_entity_id);
		if(neigh_entity->pass_on_me(m_direction))
		{
			if(!m_is_snapping)
				move(m_direction);
		}
		else
		{
			m_sprite.set_state(SP_STOP);
		}

	}
	else
	{
		if(!m_is_snapping)
		{
			Sample_Manager::instance()->play(SFX_PLAYER_MOVE);
			move(m_direction);
		}
	}
*/		
	m_direction=STOP;

	m_just_checked=true;
	
	m_is_snapping=false;
	

}


bool Entity_Player::pass_on_me(Direction d)
{
	return false;
}

bool Entity_Player::is_alive()
{
	
	return m_is_alive;
	
}

Uint32 Entity_Player::get_score()
{

	return m_score;
	
}

void Entity_Player::win()
{
	m_is_exited=true;

	DEBOUT("Winner!\n");
}

bool Entity_Player::is_exited()
{
	return m_is_exited;
	
}

bool Entity_Player::hit_from_up(Entity_Handle ntt)
{
	current_level->explode(m_position_x,m_position_y);

	kill();
	return false;
}

bool Entity_Player::explode()
{
	kill();
	return true;
}

void Entity_Player::kill()
{
	m_exists=false;
	m_is_alive=false;
	if(!m_is_exited)
	{
		Sample_Manager::instance()->play(SFX_GAME_GAMEOVER);
	}
//	set_position(0,0);

}
