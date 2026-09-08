/***************************************************************************
                          game.h  -  description
                             -------------------
    begin                : Tue Aug 28 2001
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


#include "fonts/font_manager.h"

#include "game_timer.h"
#include "screen_state.h"



#ifndef GAME_H
#define GAME_H
class Menu_State;
class Level;



class Game : public ScreenState
{

private:

	Game_Timer m_time;
	
	Level* m_level;
	
	Font_Handle m_game_font;
	
	Font_Handle m_time_font;
	
	Font_Handle m_credits_font;

	Uint32 m_current_level_number;

	bool m_direct_map_loading = false;

public:
	
	Game(Uint32 level_number);

	Game(const char *level_path);

	void create();

    void update(double elapsed);

	void update_fixed(Uint64 elapsed);

    void deinit();

	void draw();
	
	void init();
	
	Level* get_current_level(){return m_level;}
	
	~Game();
	
	void get_keys();
	
	//carica gli sprites e li immagazzina in m_sprites
	void load_fonts();
	
	void load_config();
	
	void load_surfaces();
	
	void move_all();
	
	void _draw(Uint32 frame_number, bool update_only=false);
	
	void draw_score();
	
	void show_loading();
	

};

#endif //GAME_H

