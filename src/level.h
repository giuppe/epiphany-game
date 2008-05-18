/***************************************************************************
                          level.h  -  description
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
#include "direction.h"
#include "entity_type.h"
#include "entity_manager.h"
#include "world_coord.h"
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
	Entity_Player& get_player();
	friend class Game;
public:
	Level();
	

	
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
	
	void do_inc_player_score(Sint32 value);
	
	Uint32 get_current_score();
	
	void do_win_level();
	
	void do_player_stop();
	
	void do_set_player_speed(Uint32 speed);
	
	void do_player_move(Direction d);
	
	bool is_player_alive();

	bool is_player_exited();
	
	void do_set_player_snap(bool snap);
	
	WorldCoord get_player_sprite_position();
	
	void do_explode_player();
	
	bool do_hit(Entity_Handle sender, Entity_Handle receiver);
	
};

#endif //LEVEL_H
