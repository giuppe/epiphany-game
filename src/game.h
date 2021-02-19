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
#include "runnable.h"



#ifndef GAME_H
#define GAME_H
class Menu;
class Level;



class Game : public Runnable
{

private:

	enum Game_State{
		GAME_NONE,
		GAME_MENU,
		GAME_MENU_OPTIONS,
		GAME_READY,
		GAME_PLAY,
		GAME_PAUSE,
		GAME_POSTPLAY,
		GAME_CREDITS,
		GAME_QUIT
	};

	enum{
		GAME_RESULT_NONE,
		GAME_RESULT_LOSE,
		GAME_RESULT_WIN
	};

	Game_State m_state;

	Game_State m_next_state;

	Game_Timer m_time;
	
	Level* m_level;
	
	Font_Handle m_game_font;
	
	Font_Handle m_time_font;
	
	Font_Handle m_credits_font;
	
	bool m_frame_limiter_enabled;

	Epiconfig* m_config;
	
	Uint32 m_unsolved_level;
	
	Uint32 m_max_num_of_levels;
	
	char m_ini_path[255];
	
	Uint32 m_frame_skip;

	
	Uint32 find_levels_in_dir();

	Menu* m_main_menu;

	Sint32 m_main_menu_result = 0;

	Sint32 m_game_result = 0;

	Uint32 m_current_level_number = 0;

	std::vector<std::string> m_credits;

	double m_current_elapsed = 0;

	double m_ready_screen_duration = 0;

	bool m_is_game_paused = false;

	Uint32 m_current_frame = 0;


public:

	
	void init();
	
	void go();
	
	Level* get_current_level(){return m_level;}

	Uint32 get_current_level_number(){return m_current_level_number;}

	Sint32 get_game_result() const {return m_game_result;}
	
	~Game();
	
	void get_keys();
	
	//carica gli sprites e li immagazzina in m_sprites
	void load_fonts();
	
	void load_config();
	
	void load_surfaces();
	
	void play_level(const char *);
	
	void move_all();
	
	void draw(Uint32 frame_number, bool update_only=false);
	
	void draw_score();
	
	void show_credits();
	
	void save_last_level(Uint32 last_level);
	
	bool is_frame_limiter_enabled(){return m_frame_limiter_enabled;}
	
	void set_frame_limiter_enabled(bool enable){m_frame_limiter_enabled = enable;}
	
	Uint32 get_frame_skip(){return m_frame_skip;}
	
	void set_frame_skip(Uint32 frame_skip){m_frame_skip = frame_skip;}
	
	void setup();

	void update(double elapsed);

	void destroy();

	void effect_change_state();

	void set_next_state(Game_State next_state);

	void game_state_menu_update();
	
	void game_state_menu_options_update();

	void game_state_ready_update();

	void game_state_play_update();

	void game_state_credits_update();

	void game_state_quit_update();

	void game_state_menu_setup();
	
	void game_state_menu_options_setup();

	void game_state_ready_setup();

	void game_state_play_setup();

	void game_state_credits_setup();

	void game_state_quit_setup();

	void game_state_menu_destroy();
	
	void game_state_menu_options_destroy();

	void game_state_ready_destroy();

	void game_state_play_destroy();

	void game_state_credits_destroy();

	void game_state_quit_destroy();

	void game_state_postplay_destroy();

	void game_state_postplay_setup();

	void game_state_postplay_update();

	// begin Singleton stuff

private:

	static Game* _instance;

protected:

	Game(){};

public:

	static Game* instance();

};

#endif //GAME_H

