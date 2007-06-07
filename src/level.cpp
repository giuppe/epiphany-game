/***************************************************************************
                          level.cpp  -  description
                             -------------------
    begin                : Fri Aug 31 2001
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
#include "entity_all.h"
#include "entity_factory.h"
#include "entity_manager.h"
#include "level.h"
#include "levelmap.h"
#include "screen.h"
#include "sprite.h"
#include "spriteset.h"
#include "sfx.h"
#include <vector>
//#include <map>
#include <fstream>

extern int glb_curr_id;

Level::Level(Spriteset& spriteset, Sampleset& sampleset):m_spriteset(spriteset),m_sampleset(sampleset)
{
	
	//pushing back entity with id=0
	
	//m_entities_list.push_back(Ntt_pointer());
	
	m_entities_matrix.resize(Epiconfig::instance()->get_level_size_x());
	for(int i=0; i<Epiconfig::instance()->get_level_size_x(); i++)
	{
		m_entities_matrix[i].resize(Epiconfig::instance()->get_level_size_y());
		
	}
	
	for(int x=0; x<Epiconfig::instance()->get_level_size_x(); x++)
	for(int y=0; y<Epiconfig::instance()->get_level_size_y(); y++)
	{
		m_entities_matrix[x][y] = 0;
	}
	
	Entity_Manager::instance()->reset();
	
	//glb_curr_id=1;
	m_acquired_keys=0;
	m_min_score=0;
	
}

void Level::set_key(unsigned int key)
{
	m_acquired_keys=m_acquired_keys|key;
}

/*
 int Level::get_entity_id(int x, int y)
{
	//HCKSMTHNGHR
	//check limits
	if((x<0)||(y<0))
	{
		DEBOUT("Something outside limits...\n");
		return 0;
	}
	return m_entities_matrix[x][y];
}

int Level::get_entity_id(int x, int y, Direction d)
{
	int dx, dy;
	
	switch(d)
	{
	case STOP:
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
	
	return get_entity_id(x+dx, y+dy);
}
*/
/*Ntt_pointer& Level::get_entity(int ntt_id)
{
	//return m_entities_list[ntt_id];
	return Entity_Manager::instance()->get_entity(ntt_id);
}*/

Entity_Handle Level::get_entity(int x, int y)
{
	return m_entities_matrix[x][y];
}

Entity_Handle Level::get_entity(int x, int y, Direction d)
{
	int dx, dy;
	
	switch(d)
	{
	case STOP:
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

/*
std::vector<Entity_Handle>& Level::get_entities_list()
{
	return m_entities_list;
}
*/
void Level::load_map(const char* map_path)
{
	Entity_Player* pl;	
	
//	Entity_Exit* ex;
	Levelmap levelmap;
	levelmap.load_map(CL_String(map_path));
	unsigned int i,j;
	for(j=0; j<levelmap.get_size_y(); j++)
		for(i=0; i<levelmap.get_size_x(); i++)
		{
			set_entity(levelmap.get_map_element(i,j),i,j);
		}
	m_exit->set_min_score(levelmap.get_min_score());
	m_min_score=levelmap.get_min_score();
	m_max_time=levelmap.get_max_time();
}

void Level::set_entity(Entity_Type type, unsigned int x, unsigned int y)
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
	/*
	//DEBOUT(type<<"\n");
	switch(type)
	{
	case UNKNOWN:
	//do nothing
		break;
	case PLAYER:
		m_player=new Entity_Player(this,x,y,m_spriteset.get_sprite(PLAYER));
		set_entity(m_player);
		DEBOUT("Setting player...\n");
		break;
	case GRASS:
		set_entity(new Entity_Grass(this,x,y,m_spriteset.get_sprite(GRASS)));
		break;
	case STEEL:
		set_entity(new Entity_Steel(this,x,y,m_spriteset.get_sprite(STEEL)));
		break;
	case EMERALD:
		set_entity(new Entity_Emerald(this,x,y,m_spriteset.get_sprite(EMERALD)));
		break;
	case BOULDER:
		set_entity(new Entity_Boulder(this,x,y,m_spriteset.get_sprite(BOULDER)));
		break;
	case SAPPHIRE:
		set_entity(new Entity_Sapphire(this,x,y,m_spriteset.get_sprite(SAPPHIRE)));
		break;
	case EXIT:
		m_exit=new Entity_Exit(this,x,y,m_spriteset.get_sprite(EXIT),1);
		set_entity(m_exit);
		DEBOUT("Setting Exit...\n");
		break;
	case DOOR_RED:
		set_entity(new Entity_Door(this,x,y,m_spriteset.get_sprite(DOOR),1));
		break;
	case DOOR_BLUE:
		set_entity(new Entity_Door(this,x,y,m_spriteset.get_sprite(DOOR),2));
		break;
	case DOOR_GREEN:
		set_entity(new Entity_Door(this,x,y,m_spriteset.get_sprite(DOOR),4));
		break;
	case DOOR_YELLOW:
		set_entity(new Entity_Door(this,x,y,m_spriteset.get_sprite(DOOR),8));
		break;
	case KEY_RED:
		set_entity(new Entity_Key(this,x,y,m_spriteset.get_sprite(KEY),1));
		break;
	case KEY_BLUE:
		set_entity(new Entity_Key(this,x,y,m_spriteset.get_sprite(KEY),2));
		break;
	case KEY_GREEN:
		set_entity(new Entity_Key(this,x,y,m_spriteset.get_sprite(KEY),4));
		break;
	case KEY_YELLOW:
		set_entity(new Entity_Key(this,x,y,m_spriteset.get_sprite(KEY),8));
		break;
	case FLINTSTONE:
		set_entity(new Entity_Flintstone(this,x,y,m_spriteset.get_sprite(FLINTSTONE)));
		break;
	case PEPERON_UP:
		set_entity(new Entity_Peperon(this,x,y,m_spriteset.get_sprite(PEPERON),UP));
		break;
	case PEPERON_RIGHT:
		set_entity(new Entity_Peperon(this,x,y,m_spriteset.get_sprite(PEPERON),RIGHT));
		break;
	case PEPERON_DOWN:
		set_entity(new Entity_Peperon(this,x,y,m_spriteset.get_sprite(PEPERON),DOWN));
		break;
	case PEPERON_LEFT:
		set_entity(new Entity_Peperon(this,x,y,m_spriteset.get_sprite(PEPERON),LEFT));
		break;
	case BRICK:
		set_entity(new Entity_Brick(this,x,y,m_spriteset.get_sprite(BRICK)));
		break;
	case WOOD:
		set_entity(new Entity_Wood(this,x,y,m_spriteset.get_sprite(WOOD)));
		break;
	case TOMATO_UP:
		set_entity(new Entity_Tomato(this,x,y,m_spriteset.get_sprite(TOMATO),UP));
		break;
	case TOMATO_RIGHT:
		set_entity(new Entity_Tomato(this,x,y,m_spriteset.get_sprite(TOMATO),RIGHT));
		break;
	case TOMATO_DOWN:
		set_entity(new Entity_Tomato(this,x,y,m_spriteset.get_sprite(TOMATO),DOWN));
		break;
	case TOMATO_LEFT:
		set_entity(new Entity_Tomato(this,x,y,m_spriteset.get_sprite(TOMATO),LEFT));
		break;
	default:
		//do nothing
		break;
	}
	*/
}
/*
void Level::set_player(Entity_Player* pl)
{
	m_player=pl;
//	m_entities_list[m_player->get_id()]=Ntt_pointer(*m_player);
	m_entities_list.push_back(Ntt_pointer(*m_player));
	m_entities_matrix[pl->get_position_x()][pl->get_position_y()]=m_player->get_id();
}
*/
void Level::set_entity(Entity* ntt)
{
	//m_entities_list.push_back(Ntt_pointer(*ntt));
	Entity_Handle e_handle = Entity_Manager::instance()->add_entity(ntt);
	ntt->set_id(e_handle);
	m_entities_matrix[ntt->get_position_x()][ntt->get_position_y()]=e_handle;
  //DEBOUT("setting entity to "<<ntt->get_position_x()<<", "<<ntt->get_position_y()<<"\n");
}

int Level::get_size_x()
{
	return Epiconfig::instance()->get_level_size_x();
}

int Level::get_size_y()
{
	return Epiconfig::instance()->get_level_size_y();
}

std::vector<std::vector<Entity_Handle> >& Level::get_entities_matrix()
{
	return m_entities_matrix;
}

Entity_Player& Level::get_player()
{
	return *m_player;
}

Sprite& Level::get_sprite(Entity_Type entity_type)
{

	return m_spriteset.get_sprite(entity_type);
	
}

Level::~Level()
{
//	for (unsigned int i=0; i<m_entities_list.size(); i++)
//		m_entities_list[i].remove();
}
	
unsigned int Level::get_acquired_keys()
{
	return m_acquired_keys;
}

void Level::explode(unsigned int x, unsigned int y, Entity_Type transform_to)
{

//	Ntt_pointer& curr_ntt=m_entities_list[m_entities_matrix[x][y]];
	Entity_Handle curr_ntt=get_entity(x,y);
 /*
	if(((curr_ntt.is_referenced())&&(curr_ntt->exists()))&&(!curr_ntt->explode()))
	{
	}
	else
	{
		set_entity(new Entity_Explosion(this,x,y,m_spriteset.get_sprite(EXPLOSION), transform_to));	
	}
*/	
	if(curr_ntt != 0)
	{
		Entity* curr_entity = Entity_Manager::instance()->get_entity(curr_ntt);
	//	DEBOUT("Entering Level::explode("<<x<<", "<<y<<")\n");
	//	DEBOUT("id: "<<m_entities_matrix[x][y]<<"\n");
	//	DEBOUT("curr_ntt: id="<<curr_ntt->get_id()<<")\n");
		if(curr_entity->exists())
		{
	
			bool result=curr_entity->explode();
	//		DEBOUT("result of explode="<<result<<"\n");
			if(result)
			{
				Entity_Explosion* explosion = new Entity_Explosion(this,x,y,m_spriteset.get_sprite(EXPLOSION));
				explosion->set_transform_to(transform_to); 
				set_entity(explosion);
			}
		}
		else
		{
			Entity_Explosion* explosion = new Entity_Explosion(this,x,y,m_spriteset.get_sprite(EXPLOSION));
				explosion->set_transform_to(transform_to); 
			set_entity(explosion);
		}
	}
	else
	{
		Entity_Explosion* explosion = new Entity_Explosion(this,x,y,m_spriteset.get_sprite(EXPLOSION));
				explosion->set_transform_to(transform_to); 
			set_entity(explosion);
	}
		
}

unsigned int Level::get_min_score()
{
	return m_min_score;
}

unsigned int Level::get_max_time()
{
	return m_max_time;
}

Sample* Level::get_sample(Sample_Type sample_type)
{
	return m_sampleset.get_sample(sample_type);
}

