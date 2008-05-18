/***************************************************************************
                          level.cpp  -  description
                             -------------------
    begin                : Fri Aug 31 2001
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
#include "entity_all.h"
#include "entity_factory.h"
#include "entity_manager.h"
#include "surface_manager.h"
#include "level.h"
#include "levelmap.h"
#include "screen.h"
#include "sprite.h"

#include "sfx.h"
#include <vector>
//#include <map>
#include <fstream>

extern int glb_curr_id;

Level::Level()
{

	m_entities_matrix.resize(Epiconfig::instance()->get_map_size_x());

	for(Uint32 i=0; i<Epiconfig::instance()->get_map_size_x(); i++)
	{

		m_entities_matrix[i].resize(Epiconfig::instance()->get_map_size_y());
		
	}
	
	for(Uint32 x=0; x<Epiconfig::instance()->get_map_size_x(); x++)
	for(Uint32 y=0; y<Epiconfig::instance()->get_map_size_y(); y++)
	{

		m_entities_matrix[x][y] = 0;

	}

	Entity_Manager::instance()->reset();
	
	m_acquired_keys=0;

	m_min_score=0;
	
}

void Level::set_key(Uint32 key)
{
	m_acquired_keys=m_acquired_keys|key;
}



Entity_Handle Level::get_entity(Sint32 x, Sint32 y)
{
	if((x<0)||(y<0)||(x>=(Sint32)m_entities_matrix.size())||(y>=(Sint32)m_entities_matrix[0].size()))
	{
		return 0;
	}
	return m_entities_matrix[x][y];
}

Entity_Handle Level::get_entity(Sint32 x, Sint32 y, Direction d)
{
	Sint32 dx, dy;
	
	switch(d)
	{
	case STOP:
	default:
		dx=0;
		dy=0;
		break;
	case UP:
		dx=0;
		dy=-1;
		break;
	case UPRIGHT:
		dx=1;
		dy=-1;
		break;	
	case RIGHT:
		dx=1;
		dy=0;
		break;
	case DOWNRIGHT:
		dx=1;
		dy=1;
		break;	
	case DOWN:
		dx=0;
		dy=1;
		break;
	case DOWNLEFT:
		dx=-1;
		dy=1;
		break;	
	case LEFT:
		dx=-1;
		dy=0;
		break;
	case UPLEFT:
		dx=-1;
		dy=-1;
		break;	
	
	}
	
	return get_entity(x+dx, y+dy);

}

Entity_Handle Level::get_entity(Sint32 x, Sint32 y, Direction d, Direction d1)
{
	Sint32 dx, dy;
	
	switch(d)
	{
	case STOP:
	default:
		dx=0;
		dy=0;
		break;
	case UP:
		dx=0;
		dy=-1;
		break;
	case UPRIGHT:
		dx=1;
		dy=-1;
		break;	
	case RIGHT:
		dx=1;
		dy=0;
		break;
	case DOWNRIGHT:
		dx=1;
		dy=1;
		break;	
	case DOWN:
		dx=0;
		dy=1;
		break;
	case DOWNLEFT:
		dx=-1;
		dy=1;
		break;	
	case LEFT:
		dx=-1;
		dy=0;
		break;
	case UPLEFT:
		dx=-1;
		dy=-1;
		break;	
	
	}
	
	return get_entity(x+dx, y+dy, d1);

}

void Level::load_map(const char* map_path)
{
	
	Levelmap levelmap;
	levelmap.load_map(map_path);
	Uint32 i,j;
	for(j=0; j<levelmap.get_size_y(); j++)
		for(i=0; i<levelmap.get_size_x(); i++)
		{
			set_entity(levelmap.get_map_element(i,j),i,j);
		}
	m_exit->set_min_score(levelmap.get_min_score());
	m_min_score=levelmap.get_min_score();
	m_max_time=levelmap.get_max_time();
}

void Level::set_entity(Entity_Type type, Uint32 x, Uint32 y)
{
		if(type==UNKNOWN)
	{
		return;
	}
	Entity_Factory* entity_factory = Entity_Factory::instance();
	Entity* entity = entity_factory->create_entity(type, this);
	entity->set_initial_position(x,y);
	set_entity(entity);
	
	if(type == PLAYER)
	{
		m_player = (Entity_Player*)entity;
	}
	else if(type == EXIT)
	{
		m_exit = (Entity_Exit*) entity;
	}
}


void Level::set_entity(Entity* ntt)
{
	//m_entities_list.push_back(Ntt_pointer(*ntt));
	Entity_Handle e_handle = Entity_Manager::instance()->add_entity(ntt);
	ntt->set_id(e_handle);
	m_entities_matrix[ntt->get_position_x()][ntt->get_position_y()]=e_handle;
  //DEBOUT("setting entity to "<<ntt->get_position_x()<<", "<<ntt->get_position_y()<<"\n");
}

Uint32 Level::get_size_x()
{
	return Epiconfig::instance()->get_map_size_x();
}

Uint32 Level::get_size_y()
{
	return Epiconfig::instance()->get_map_size_y();
}

std::vector<std::vector<Entity_Handle> >& Level::get_entities_matrix()
{
	return m_entities_matrix;
}

Entity_Player& Level::get_player()
{
	return *m_player;
}

Level::~Level()
{
}
	
Uint32 Level::get_acquired_keys()
{
	return m_acquired_keys;
}

void Level::explode(Uint32 x, Uint32 y, Entity_Type transform_to)
{

	Entity_Handle curr_ntt=get_entity(x,y);
 
	if(curr_ntt != 0)
	{
		Entity* curr_entity = Entity_Manager::instance()->get_entity(curr_ntt);
	
		
		if(curr_entity->exists())
		{
	
			bool result=curr_entity->explode();
			if(result)
			{
				Entity_Explosion* explosion = new Entity_Explosion(this,x,y);
				
				explosion->set_transform_to(transform_to);
				explosion->set_initial_position(x, y); 
				set_entity(explosion);
			}
		}
		else
		{
			Entity_Explosion* explosion = new Entity_Explosion(this,x,y);
				explosion->set_transform_to(transform_to); 
				explosion->set_initial_position(x, y); 
			set_entity(explosion);
		}
	}
	else
	{
		Entity_Explosion* explosion = new Entity_Explosion(this,x,y);
				explosion->set_transform_to(transform_to); 
				explosion->set_initial_position(x, y); 
			set_entity(explosion);
	}
		
}

Uint32 Level::get_min_score()
{
	return m_min_score;
}

Uint32 Level::get_max_time()
{
	return m_max_time;
}



bool Level::player_push(Uint32 x, Uint32 y, Direction d)
{
	Entity_Handle neigh_entity = this->get_entity(x, y, d);
	if(neigh_entity!=0)
	{
		bool return_value = false;
		switch(d)
		{
			case LEFT:
				return_value = Entity_Manager::instance()->get_entity(neigh_entity)->player_pressing_right(this->get_entity(x,y,d,LEFT));
				break;
			case RIGHT:
				return_value = Entity_Manager::instance()->get_entity(neigh_entity)->player_pressing_left(this->get_entity(x,y,d,RIGHT));
				break;
			case UP:
				return_value = Entity_Manager::instance()->get_entity(neigh_entity)->player_pressing_down(this->get_entity(x,y,d,UP));
				break;
			case DOWN:
				return_value = Entity_Manager::instance()->get_entity(neigh_entity)->player_pressing_up(this->get_entity(x,y,d,DOWN));
				break;
			default:
				return_value = false;
		}
		return return_value;
	}
	return true;
}

void Level::do_inc_player_score(Sint32 value)
{
	m_player->inc_score(value);
}

void Level::do_win_level()
{
	m_player->win();
}

Uint32 Level::get_current_score()
{
	return m_player->get_score();
}

void Level::do_player_stop()
{
	m_player->set_direction(STOP);
}

void Level::do_player_move(Direction d)
{
	m_player->move(d);
}

void Level::do_set_player_speed(Uint32 speed)
{
	m_player->set_speed(speed);
}

bool Level::is_player_alive()
{
	return m_player->is_alive();
}

bool Level::is_player_exited()
{
	return m_player->is_exited();
}

void Level::do_set_player_snap(bool snap)
{
	m_player->set_snap(snap);
}

void Level::do_explode_player()
{
	this->explode(m_player->get_position_x(), m_player->get_position_y());
}

WorldCoord Level::get_player_sprite_position()
{
	return m_player->get_sprite_position();
}

bool Level::do_hit(Entity_Handle sender, Entity_Handle receiver)
{
	return Entity_Manager::instance()->get_entity(receiver)->hit_from_up(sender);
}
