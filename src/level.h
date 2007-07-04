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
 *   it under the terms of the GNU General Public License, Version 2, as published by  *
 *   the Free Software Foundation.                                   *
 *                                                                         *
 ***************************************************************************/

#include "dephine.h"
#include "direction.h"
#include "entity_type.h"
#include "entity_manager.h"
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


	
	std::vector<std::vector<Entity_Handle> > m_entities_matrix;
	Entity_Player* m_player;
	Entity_Exit* m_exit;

	Uint32 m_acquired_keys;
	Uint32 m_min_score;
	Uint32 m_max_time;
	void set_entity(Entity*);

public:
	Level();
	
	Entity_Player& get_player();
	
	Entity_Handle get_entity(Sint32 x, Sint32 y);
	
	Entity_Handle get_entity(Sint32 x, Sint32 y, Direction d);
	
	Entity_Handle get_entity(Sint32 x, Sint32 y, Direction d, Direction d1);
	
	void load_map(const char* path);
	
	Uint32 get_size_x();
	
	Uint32 get_size_y();

	void set_entity(Entity_Type type, Uint32 x, Uint32 y);

	std::vector<std::vector<Entity_Handle> >& get_entities_matrix();

	void set_key(Uint32);

	Uint32 get_acquired_keys();

	~Level();

	void explode(Uint32 x, Uint32 y, Entity_Type transform_to=UNKNOWN);

	Uint32 get_min_score();

	Uint32 get_max_time();
	
	bool player_push(Uint32 x, Uint32 y, Direction d);

};

#endif //LEVEL_H
