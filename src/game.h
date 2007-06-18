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
 *   it under the terms of the GNU General Public License, Version 2, as published by  *
 *   the Free Software Foundation.                                   *
 *                                                                         *
 ***************************************************************************/

#include "dephine.h"

#include "sprite.h"
#include "direction.h"
#include "fonts/font.h"
#include "fonts/font_manager.h"
#include "resource_factory.h"
#include "entity_type.h"
#include "entity.h"
#include "entity_all.h"
#include "game_timer.h"

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

	//const char* m_resource_path;
	
	
	//Screen m_screen;
	
	Game_Timer m_time;
	
	//CL_InputBuffer m_input_buffer;
	
	Level* m_level;
	
	Font_Handle m_game_font;
	
	Font_Handle m_time_font;
	
	Font_Handle m_credits_font;

	Epiconfig* m_config;
	
	Uint32 m_unsolved_level;
	
	Uint32 m_max_num_of_levels;
	
	char m_ini_path[255];

	//Resource_Factory* m_res_manag;
	
	Uint32 find_levels_in_dir();

public:

	Game(){};
	
	void init();
	
	void go();
	
	bool main_loop();
	
	Level* get_current_level(){return m_level;}
	
	~Game();
	
	void get_keys();
	
	//carica gli sprites e li immagazzina in m_sprites
	void load_fonts();
	
	void load_config();
	
	void load_surfaces();
	
	void play_level(const char *);
	
	void move_all();
	
	void draw(int frame_number);
	
	void draw_score();
	
	void show_credits();
	
	void save_last_level(Uint32 last_level);
	

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

