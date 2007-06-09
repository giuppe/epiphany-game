/***************************************************************************
                          level.h  -  description
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
#include "direction.h"
#include "entity_type.h"
#include "entity_manager.h"
#include "spriteset.h"
#include <vector>
#include "sfx.h"


#ifndef LEVEL_H
#define LEVEL_H

class Entity;
class Ntt_pointer;

class Screen;
class Sprite;
class Entity_Player;
class Entity_Exit;


class Level
{
private:

	//std::vector<Ntt_pointer> m_entities_list;
	
	std::vector<std::vector<Entity_Handle> > m_entities_matrix;
	Entity_Player* m_player;
	Entity_Exit* m_exit;
	Spriteset& m_spriteset;
	Sampleset& m_sampleset;
	Uint32 m_acquired_keys;
	Uint32 m_min_score;
	Uint32 m_max_time;
	void set_entity(Entity*);
public:
	Level(Spriteset& sprites, Sampleset& samples);
	//int get_entity_id(int x, int y);
	//int get_entity_id(int x, int y, Direction d);
	Entity_Player& get_player();
	//Ntt_pointer& get_entity(int ntt_id);
	Entity_Handle get_entity(int x, int y);
	Entity_Handle get_entity(int x, int y, Direction d);
	void load_map(const char* path);
	int get_size_x();
	int get_size_y();
//	void set_player(Entity_Player*);

	void set_entity(Entity_Type type, Uint32 x, Uint32 y);
	Sprite& get_sprite(Entity*);
	//std::vector<Entity_Handle>& get_entities_list();
	std::vector<std::vector<Entity_Handle> >& get_entities_matrix();
	void set_key(Uint32);
	Uint32 get_acquired_keys();
	Sprite& get_sprite(Entity_Type entity_type);
	Sample* get_sample(Sample_Type sample_type);
	~Level();
	void explode(Uint32 x, Uint32 y, Entity_Type transform_to=UNKNOWN);
	Uint32 get_min_score();
	Uint32 get_max_time();
};

#endif //LEVEL_H
