/***************************************************************************
                          game.cpp  -  description
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

#include <vector>

#include <fstream>
#include "entity_type.h"

#include "fonts/font_factory.h"

#include "entities/entity_player.h"
#include "surface_manager.h"
#include "music_manager.h"
#include "game.h"
#include "screen.h"
#include "menu.h"
#include "input.h"
#include "level.h"
#include "game_timer.h"
#include <cstdlib>
#include <cstdio>
#include <SDL2/SDL.h>
#include <string>
#include <cassert>

#include "sfx.h"


void Game::get_keys()
{
		//direzione iniziale

		Input *input = Input::instance();
		input->update();
		Direction direction = STOP;

		if ((input->get_quit()) && (m_level->is_player_alive()))
		{

			m_level->do_explode_player();
			return;
		}

		//questi if settano la direzione a seconda del tasto premuto
		if (input->get_up())
		{

			direction = UP;
		}
		else if (input->get_down())
		{

			direction = DOWN;
		}
		else if (input->get_right())
		{

			direction = RIGHT;
		}
		else if (input->get_left())
		{

			direction = LEFT;
		}
		if ((direction >= UP) && (direction <= LEFT))
		{
			m_level->get_player().set_direction(direction);
			//DEBOUT("Setting direction: "<<direction<<"\n");
		}

		if (input->get_fire())
		{
			m_level->do_set_player_snap(true);
		}
		else
		{
			m_level->do_set_player_snap(false);
		}
	
}




void Game::move_all()
{
		Entity_Manager *entity_manager = Entity_Manager::instance();

		Uint32 entity_manager_size = entity_manager->size();

		std::vector<std::vector<Entity_Handle>> &matrix = m_level->get_entities_matrix();

		m_level->do_set_player_speed(1);

		Uint32 i, x, y;
		for (x = 0; x < m_config->get_map_size_x(); x++)
		{
			for (y = 0; y < m_config->get_map_size_y(); y++)
			{
				matrix[x][y] = 0;
			}
		}
		Entity *curr_entity;
		for (i = 1; i < entity_manager_size; i++)
		{
			curr_entity = entity_manager->get_entity(i);
			if (curr_entity->exists())
			{
				curr_entity->set_checked(false);
				matrix[curr_entity->get_position_x()][curr_entity->get_position_y()] = i;
			}
		}

		for (i = 1; i < entity_manager_size; i++)
		{
			curr_entity = entity_manager->get_entity(i);

			if (curr_entity->exists())
			{
				if ((curr_entity->get_type() != PLAYER) || (curr_entity->get_type() != STEEL) || (curr_entity->get_type() != GRASS))
					curr_entity->check_and_do();
			}
		}
		Entity *player = &m_level->get_player();
		if (player->exists())
		{
			player->check_and_do();
		}
	
}




void Game::draw(Uint32 frame_number, bool update_only)
{
		Entity *curr_ntt;
		Screen *screen = Screen::instance();
		//screen->clear();

		Entity *player = &m_level->get_player();

		Entity_Manager *entity_manager = Entity_Manager::instance();

		Uint32 entity_manager_size = entity_manager->size();

		//centering screen on player
		//	screen->set_window_center(m_level->get_player().get_sprite().get_pos_x(),m_level->get_player().get_sprite().get_pos_y());

		screen->set_camera_position(m_level->get_player_sprite_position());

		//move sprites
		if (player->exists())
		{
			player->move_sprite();
		}
		for (Uint32 i = 1; i < entity_manager_size; i++)
		{
			curr_ntt = entity_manager->get_entity(i);
			if ((curr_ntt->exists()) && (curr_ntt->get_type() != PLAYER))
			{

				curr_ntt->move_sprite();
			}
		}

		//clearing background
		screen->clear();
		//TODO: we should clear only changed background
#if 0
	if(player->exists())
	{
		player->clear_bg();
	}
	for(Uint32 i=1; i<entity_manager_size; i++)
	{
		curr_ntt=entity_manager->get_entity(i);
		if((curr_ntt->exists())&&(curr_ntt->get_type()!=PLAYER))
		{

			curr_ntt->clear_bg();
			
		}
	}
	//updating background
	if(player->exists())
	{
		player->update_bg();
	}
	for(Uint32 i=1; i<entity_manager_size; i++)
	{
		curr_ntt=entity_manager->get_entity(i);
		if((curr_ntt->exists())&&(curr_ntt->get_type()!=PLAYER))
		{

			curr_ntt->update_bg();
			
		}
	}
#endif
		//drawing sprites

		if (player->exists())
		{
			player->draw_on_screen();
		}
		for (Uint32 i = 1; i < entity_manager_size; i++)
		{
			curr_ntt = entity_manager->get_entity(i);
			if ((curr_ntt->exists()) && (curr_ntt->get_type() != PLAYER))
			{

				curr_ntt->draw_on_screen();
			}
		}
#if 0
	//drawing player
	if(player->exists())
	{
		if(update_only == false)
		{

			player->draw_on_screen();
		}
	}

	//draw other entities
	for(Uint32 i=1; i<entity_manager_size; i++)
	{
		curr_ntt=entity_manager->get_entity(i);
		if((curr_ntt->exists())&&(curr_ntt->get_type()!=PLAYER))
		{
		//	curr_ntt->refresh_sprite();
			curr_ntt->move_sprite();
			if(update_only == false)
			{
				curr_ntt->draw_on_screen();

			}
		}
	}
#endif
		if (update_only == false)
		{
			draw_score();

			screen->flip_display();
		}
	
}




void Game::draw_score()
{
		Sint32 real_game_size_y = m_config->get_screen_size_y() - m_config->get_score_size_y();
		Sint32 game_size_x = m_config->get_screen_size_x();
		Sint32 game_size_y = m_config->get_screen_size_y();
		Screen *screen = Screen::instance();
		screen->fill_rect(0, real_game_size_y, game_size_x, game_size_y, 0, 0, 0);

		Font_Manager *font_man = Font_Manager::instance();

		Font *game_font = font_man->get_font(m_game_font);

		Font *time_font = font_man->get_font(m_time_font);

		char text[255];

		sprintf(text, "Score: %d", (Sint32)m_level->get_current_score());

		game_font->write(4, real_game_size_y + 5, text);

		// find how many score to complete level
		Sint32 remaining = (Sint32)(m_level->get_min_score() - m_level->get_current_score());

		if (remaining > 0)
		{
			sprintf(text, "Remaining:   %d", remaining);
			game_font->write(200, real_game_size_y + 5, text);
		}
		else
		{
			if (m_level->is_player_exited())
			{
				game_font->write(200, real_game_size_y + 5, "Well done!");
			}
			else
			{
				game_font->write(200, real_game_size_y + 5, "Find Exit");
			}
		}

		//draw_time
		char time_string[10];
		sprintf(time_string, "%s", m_time.get_time_string());
		time_font->write(game_size_x - k_sprite_size * 2, game_size_y - k_sprite_size, time_string);

		if (!m_level->is_player_alive())
		{
			game_font->write(380, real_game_size_y + 5, "Press Space");
		}

		Surface_Manager *surf_man = Surface_Manager::instance();

		ScreenCoord scr_coord;

		if (m_level->get_acquired_keys() & 1)
		{
			scr_coord.x = game_size_x - k_sprite_size / 2;
			scr_coord.y = game_size_y - k_sprite_size / 2;
			surf_man->get_surface(Surface_Manager::SRF_KEY_RED_THUMB)->put_screen(scr_coord);
		}

		if (m_level->get_acquired_keys() & 2)
		{
			scr_coord.x = game_size_x - k_sprite_size;
			scr_coord.y = game_size_y - k_sprite_size / 2;
			surf_man->get_surface(Surface_Manager::SRF_KEY_BLUE_THUMB)->put_screen(scr_coord);
		}

		if (m_level->get_acquired_keys() & 4)
		{
			scr_coord.x = game_size_x - (k_sprite_size + k_sprite_size / 2);
			scr_coord.y = game_size_y - k_sprite_size / 2;
			surf_man->get_surface(Surface_Manager::SRF_KEY_GREEN_THUMB)->put_screen(scr_coord);
		}

		if (m_level->get_acquired_keys() & 8)
		{
			scr_coord.x = game_size_x - 2 * k_sprite_size;
			scr_coord.y = game_size_y - k_sprite_size / 2;
			surf_man->get_surface(Surface_Manager::SRF_KEY_YELLOW_THUMB)->put_screen(scr_coord);
		}

		//screen->fill_rect(0, real_game_size_y, game_size_x, game_size_y,100,50,10);

}

void Game::setup()
{
		m_state = GAME_NONE;

}

void Game::update(double elapsed)
{
		DEBOUT("Current Game State: " << m_state << ", elapsed: " << elapsed << "\n");
		m_current_elapsed = elapsed;
		switch (m_state)
		{
		case Game_State::GAME_NONE:
			set_next_state(GAME_MENU);
			break;
		case Game_State::GAME_MENU:
			game_state_menu_update();
			break;
		case Game_State::GAME_MENU_OPTIONS:
			game_state_menu_options_update();
			break;
		case Game_State::GAME_READY:
			game_state_ready_update();
			break;
		case Game_State::GAME_PLAY:
			game_state_play_update();
			break;
		case Game_State::GAME_POSTPLAY:
			game_state_postplay_update();
			break;
		case Game_State::GAME_CREDITS:
			game_state_credits_update();
			break;
		case Game_State::GAME_QUIT:
			game_state_quit_update();
			break;
		}
	effect_change_state();
}

void Game::destroy()
{

}

void Game::set_next_state(Game_State next_state)
{
	DEBOUT("Next game state will be: "<<next_state<<"\n");
	m_next_state = next_state;
}

void Game::effect_change_state()
{
		if (m_state != m_next_state)
		{
			DEBOUT("Effecting change of state from "<<m_state<<" to "<<m_next_state<<"\n");
			switch (m_state)
			{
			case GAME_MENU:
				game_state_menu_destroy();
				break;
			case GAME_MENU_OPTIONS:
				game_state_menu_options_destroy();
				break;
			case GAME_READY:
				game_state_ready_destroy();
				break;
			case GAME_PLAY:
				game_state_play_destroy();
				break;
			case GAME_POSTPLAY:
				game_state_postplay_destroy();
				break;
			case GAME_CREDITS:
				game_state_credits_destroy();
				break;
			case GAME_QUIT:
				game_state_quit_destroy();
				break;
			}
			m_state = m_next_state;
			switch (m_next_state)
			{
			case GAME_MENU:
				game_state_menu_setup();
				break;
			case GAME_MENU_OPTIONS:
				game_state_menu_options_setup();
				break;
			case GAME_READY:
				game_state_ready_setup();
				break;
			case GAME_PLAY:
				game_state_play_setup();
				break;
			case GAME_POSTPLAY:
				game_state_postplay_setup();
				break;
			case GAME_CREDITS:
				game_state_credits_setup();
				break;
			case GAME_QUIT:
				game_state_quit_setup();
				break;
			}
		}
		
}


	void Game::game_state_menu_setup()
	{
		Input::instance()->reset_states();
		m_main_menu = new Menu(m_max_num_of_levels, m_unsolved_level);

		Music_Manager::instance()->play(MUS_MENU);
		m_main_menu->setup();
		
	}

	void Game::game_state_menu_update()
	{
		switch (m_main_menu_result)
		{
		case Menu::MENU_EPIPHANY_QUIT:
			this->set_next_state(Game_State::GAME_QUIT);
			break;
		case Menu::MENU_EPIPHANY_START:
			this->set_next_state(Game_State::GAME_READY);
			break;
		case Menu::MENU_EPIPHANY_NONE:
		default:
			m_main_menu->update(m_current_elapsed);
		}
		m_main_menu_result = m_main_menu->get_result();
		m_current_level_number = m_main_menu->get_current_level();
		
	}

	void Game::game_state_menu_destroy()
	{
		Music_Manager::instance()->stop();
		m_main_menu->destroy();
		delete m_main_menu;
	}

	void Game::game_state_menu_options_setup()
	{

	}

	void Game::game_state_menu_options_update()
	{

	}

	void Game::game_state_menu_options_destroy()
	{

	}

	void Game::game_state_ready_setup()
	{
		m_level = new Level();

		char current_level_path[255];

		sprintf(current_level_path, "%s/maps/level%d.map",
				Resource_Factory::instance()->get_resource_path().c_str(),
				this->get_current_level_number());

		DEBOUT("Loading map: " << current_level_path << "\n");

		m_level->load_map(current_level_path);

		m_ready_screen_duration = 0;
		
	}

	void Game::game_state_ready_update()
	{
		Screen *screen = Screen::instance();

		screen->resize_world_screen(0, 0);

		Font *ready_font = Font_Manager::instance()->get_font(Font_Factory::MENU_FONT);

		screen->clear();

		ready_font->write_center(100, "Ready!");

		screen->flip_display();

		Music_Manager::instance()->play(MUS_READY);

		DEBOUT("Ready screen msec: " << m_ready_screen_duration << "\n");
		if (m_ready_screen_duration > 1940)
		{
			this->set_next_state(GAME_PLAY);
		}
		else
		{
			m_ready_screen_duration += m_current_elapsed;
		}
		//music duration (TODO: riattivare alla fine)
		//SDL_Delay(1940);

	}

	void Game::game_state_ready_destroy()
	{

	}

	void Game::game_state_play_setup()
	{
		Music_Manager::instance()->play(MUS_GAME);

		Uint32 current_frame_time = 0;

		m_game_result = GAME_RESULT_NONE;

		m_time.set_total_time(m_level->get_max_time());

		m_time.start();

		Screen::instance()->resize_world_screen(m_level->get_size_x() * k_sprite_size, m_level->get_size_y() * k_sprite_size);

		Screen::instance()->set_camera_position(m_level->get_player_sprite_position());

		Input *input = Input::instance();

		input->update();
		
	}

	void Game::game_state_play_update()
	{
		Input* input = Input::instance();
		DEBOUT("Game result: "<<m_game_result<<"\n");
		DEBOUT("Is player alive: "<<m_level->is_player_alive()<<"\n");
		if (m_game_result == GAME_RESULT_NONE)
		{
			if (m_is_game_paused == true)
			{
				input->update();
				if (input->get_pause())
				{
					m_is_game_paused = false;
				}
			}
			else if ((m_level->is_player_alive()) /*||
					 ((!input->get_fire()) && (!input->get_enter()) && (!input->get_die()))*/)
			{
				if (input->get_pause())
				{
					m_is_game_paused = true;
				}

				if (m_level->is_player_alive())
				{

					m_time.update();

					if (m_time.get_time() < 10)
					{

						Sample_Manager::instance()->play(SFX_GAME_TIMEALARM);
					}

					if (m_time.is_zero())
					{

						m_level->do_explode_player();
					}
				}

				get_keys();

				move_all();
				if(m_current_frame < m_config->get_max_anim_drawn())
				{
					draw(m_current_frame, false);
					m_current_frame += 1;
				}
				else
				{
					m_current_frame = 0;
				}
				
			}

			else if (m_level->is_player_exited() == true)
			{
				m_game_result = GAME_RESULT_WIN;
			}
			else if ((m_level->is_player_alive()==false) /*&&
					 ((input->get_fire()) || (input->get_enter()) || (input->get_die()))*/)
			{
				m_game_result = GAME_RESULT_LOSE;
			}
		
		}
		else{
			this->set_next_state(GAME_POSTPLAY);		
		}
	}

void Game::game_state_play_destroy()
{
	delete m_level;
}

void Game::game_state_postplay_setup()
{
	if (m_game_result == GAME_RESULT_LOSE)
	{
		DEBWARN("Game_over!...\n");
		this->set_next_state(GAME_MENU);
	}
	else if (m_game_result == GAME_RESULT_WIN)
	{

		DEBWARN("Winner! ;)\n");

		if ((m_main_menu->get_unsolved_level() == m_main_menu->get_current_level()) && (m_main_menu->increase_unsolved_level()))
		{
			save_last_level(m_main_menu->get_unsolved_level());

			m_main_menu->set_current_level(m_main_menu->get_unsolved_level());

			this->set_next_state(GAME_READY);
		}
		else
		{
			this->set_next_state(GAME_MENU);
		}
	}
}

void Game::game_state_postplay_update()
{

}

void Game::game_state_postplay_destroy()
{

}

void Game::game_state_credits_setup()
{

	m_credits.push_back("Epiphany");
	m_credits.push_back(" ");
	m_credits.push_back("Giuseppe D'Aqui':");
	m_credits.push_back("    Coding, Level Design, Graphics, Music");
	m_credits.push_back(" ");
	m_credits.push_back("Giuseppe Martino:");
	m_credits.push_back("    Coding, Level Design");
	//m_credits.push_back("Antonio Malara: Graphics");
	m_credits.push_back(" ");
	m_credits.push_back("Thanks to:");
	m_credits.push_back("  Joerg Jaspert, for Debian Packages");
	m_credits.push_back("  Eric Mangold, for Level Editor");
	m_credits.push_back("  Stefan for gameplay related patches");
	m_credits.push_back(" ");
	m_credits.push_back("Released under General Public License v2");
	m_credits.push_back("See COPYING for details.");

	Input *input = Input::instance();
	input->reset_states();
	//input->update();

	Screen *screen = Screen::instance();

	screen->resize_world_screen(0, 0);

	Music_Manager::instance()->play(MUS_CREDITS);
}

void Game::game_state_credits_update()
{
	Input *input = Input::instance();

	Screen *screen = Screen::instance();

	Font *credits_font = Font_Manager::instance()->get_font(m_credits_font);

	screen->clear();

	for (Uint32 i = 0; i < m_credits.size(); i++)
	{
		credits_font->write(32, 32 + 30 * i, m_credits[i].c_str());
	}
	screen->flip_display();

	input->update();

	if ((input->get_quit() || input->get_enter() || input->get_fire()))
	{
		this->set_next_state(GAME_QUIT);
	}
}

void Game::game_state_credits_destroy()
{
	m_credits.clear();
}

void Game::game_state_quit_setup()
{
}

void Game::game_state_quit_update()
{
}

void Game::game_state_quit_destroy()
{
}

void Game::init()
{

	DEBOUT("Entering Game::init()...\n");
	DEBOUT("Loading default configuration values...\n");

	m_config = Epiconfig::instance();

	m_frame_limiter_enabled = true;

	m_frame_skip = 0;

#ifdef _WIN32
	sprintf(m_ini_path, "%s", "./epiphany.ini");
#else
	std::string user_home(getenv("HOME"));
	if (user_home == "")
	{
		assert(!"Unable to find HOME environment variable");
	}
	else
	{
		user_home += "/.epiphany";
		sprintf(m_ini_path, "%s", user_home.c_str());
	}
#endif

	m_config->read_values_from_file(m_ini_path);

	Sample_Manager::instance()->set_volume(m_config->get_volume_sound());

	Music_Manager::instance()->set_volume(m_config->get_volume_music());

	DEBOUT("Loading config...\n");
	load_config();

	DEBOUT("Initing Screen...\n");
	Screen::instance()->init(m_config->get_screen_size_x(), m_config->get_screen_size_y(), m_config->get_map_size_x() * k_sprite_size, m_config->get_map_size_y() * k_sprite_size);

	DEBOUT("Initing Surface Manager...\n");
	Surface_Manager::instance();

	DEBOUT("Loading fonts...\n");
	load_fonts();
}

void Game::play_level(const char *level_path)
{
	m_level = new Level();

	m_level->load_map(level_path);

	//main_loop();
	return;
}

void Game::load_config()
{

	m_unsolved_level = Epiconfig::instance()->get_last_level();

	m_max_num_of_levels = find_levels_in_dir();
}

Uint32 Game::find_levels_in_dir()
{
	Uint32 result = 0;
	char base_path[255];
	char level_path[255];

	sprintf(base_path, "%s%s", Resource_Factory::instance()->get_resource_path().c_str(), "/maps/level");

	sprintf(level_path, "%s%d%s", base_path, result, ".map");
	FILE *pFile = fopen(level_path, "r");
	while (pFile != NULL)
	{
		DEBOUT("Found " << level_path << ".\n");
		fclose(pFile);
		result++;
		sprintf(level_path, "%s%d%s", base_path, result, ".map");
		pFile = fopen(level_path, "r");
	}
	return result;
}

void Game::load_fonts()
{

	DEBOUT("Loading fonts... ");

	Font_Manager::instance();

	m_game_font = Font_Factory::GAME_FONT;

	m_time_font = Font_Factory::TIME_FONT;

	m_credits_font = Font_Factory::CREDITS_FONT;

	DEBOUT("done.\n");
}

Game::~Game()
{
	Epiconfig::instance()->save_values_to_file(m_ini_path);
}

void Game::save_last_level(Uint32 last_level)
{

	Epiconfig::instance()->set_last_level(last_level);
}

Game *Game::_instance = 0;

Game *Game::instance()
{
	if (_instance == 0)
	{
		_instance = new Game();
		_instance->init();
	}
	return _instance;
}
