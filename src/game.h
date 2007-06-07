/***************************************************************************
                          game.h  -  description
                             -------------------
    begin                : Tue Aug 28 2001
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
#include "direction.h"
#include "entity_type.h"
#include "entity.h"
#include "entity_all.h"
#include "game_timer.h"
#include "spriteset.h"
#include "sfx.h"
#include "level.h"
#include <vector>
#include "screen.h"


#ifndef GAME_H
#define GAME_H
class Menu;


class Game
{

private:

	CL_String m_resource_path;
	
	Sampleset m_sampleset;
	
	Spriteset m_spriteset;
	
	Screen m_screen;
	
	Game_Timer m_time;
	
	CL_InputBuffer m_input_buffer;
	
	Level* m_level;
	
	CL_Font* m_game_font;
	
	CL_Font* m_time_font;
	
	CL_Font* m_credits_font;

	Epiconfig* m_config;
	
//CL_String m_map_path;
	unsigned int m_unsolved_level;
	
	unsigned int m_max_num_of_levels;
	
	CL_String m_ini_path;

	CL_ResourceManager* m_res_manag;

public:

	Game(){};
	
	void init();
	
	void go();
	
	bool main_loop();
	
	~Game();
	
	void get_keys();
	
	//carica gli sprites e li immagazzina in m_sprites
	void load_fonts();
	
	void load_config();
	
	void move_all();
	
	void draw(int frame_number);
	
	void draw_score();
	
	void show_credits();
	
	CL_ResourceManager* get_resource_manager();

	void set_resource_manager();
	
//	int menu(); //return false if "quit", else set the number of level
	// begin Singleton stuff

private:

	static Game* _instance;

/*protected:

	Entity_Factory(){};
*/
public:

	static Game* instance();

};

#endif //GAME_H

