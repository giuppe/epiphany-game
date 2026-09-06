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
#include "game_manager.h"
#include "game.h"
#include "screen.h"
#include "menu_state.h"
#include "input.h"
#include "level.h"
#include "game_timer.h"
#include "credits_state.h"
#include <cstdlib>
#include <cstdio>
#include <SDL2/SDL.h>
#include <string>
#include <cassert>

#include "sfx.h"



bool Game::main_loop()
{
	
	

	
	
}




void Game::get_keys()
{

	
	//direzione iniziale
	
	Input* input = Input::instance();
	input->update();
	Direction direction=STOP;
	
	if((input->get_quit())&&(m_level->is_player_alive()))
	{
			
		m_level->do_explode_player();
		return;
				
	}
	
  //questi if settano la direzione a seconda del tasto premuto
	if(input->get_up())
	{
			
		direction=UP;
				
	}
	else if(input->get_down())
	{
			
		direction=DOWN;
		
	}
	else if(input->get_right())
	{
	
		direction=RIGHT;
		
	}
	else if(input->get_left())
	{
	
		direction=LEFT;
		
	}
	if((direction>=UP)&&(direction<=LEFT))
	{
		m_level->get_player().set_direction(direction);
		//DEBOUT("Setting direction: "<<direction<<"\n");
	}
	
	if(input->get_fire())
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
	
	Entity_Manager* entity_manager = Entity_Manager::instance();
	
	Uint32 entity_manager_size = entity_manager->size();

	Epiconfig* m_config = Epiconfig::instance();

	std::vector< std::vector<Entity_Handle> >& matrix=m_level->get_entities_matrix();

	m_level->do_set_player_speed(1);

	Uint32 i,x,y;
	for(x=0;x<m_config->get_map_size_x();x++)
	{
		for(y=0;y<m_config->get_map_size_y();y++)
		{
			matrix[x][y]=0;
		}
	}
	Entity* curr_entity;
	for(i=1; i<entity_manager_size; i++)
	{	
		curr_entity = entity_manager->get_entity(i);
		if(curr_entity->exists())
		{
			curr_entity->set_checked(false);
			matrix[curr_entity->get_position_x()][curr_entity->get_position_y()]=i;
		}
	}
	
	
	for(i=1; i<entity_manager_size; i++)
	{
		curr_entity = entity_manager->get_entity(i);
		
		if(curr_entity->exists())
		{
			if((curr_entity->get_type()!=PLAYER)||(curr_entity->get_type()!=STEEL)||(curr_entity->get_type()!=GRASS))
				curr_entity->check_and_do();
		}
	}
	Entity* player = &m_level->get_player();
	if(player->exists())
	{
		player->check_and_do();
	}
	
}




void Game::_draw(Uint32 frame_number, bool update_only)
{

	Entity* curr_ntt;
	Screen* screen = Screen::instance();
	//screen->clear();
	
	Entity* player = &m_level->get_player();
	
	Entity_Manager* entity_manager = Entity_Manager::instance();
	
	Uint32 entity_manager_size = entity_manager->size();
	
	//centering screen on player
//	screen->set_window_center(m_level->get_player().get_sprite().get_pos_x(),m_level->get_player().get_sprite().get_pos_y());

	screen->set_camera_position(m_level->get_player_sprite_position());

	//move sprites
	if(player->exists())
	{
		player->move_sprite();
	}
	for(Uint32 i=1; i<entity_manager_size; i++)
	{
		curr_ntt=entity_manager->get_entity(i);
		if((curr_ntt->exists())&&(curr_ntt->get_type()!=PLAYER))
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
	
	if(player->exists())
	{
		player->draw_on_screen();
	}
	for(Uint32 i=1; i<entity_manager_size; i++)
	{
		curr_ntt=entity_manager->get_entity(i);
		if((curr_ntt->exists())&&(curr_ntt->get_type()!=PLAYER))
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
	if(update_only == false)
	{
		draw_score();
	
		screen->flip_display();
	}
	
}




void Game::draw_score()
{
	Epiconfig* m_config = Epiconfig::instance();

	Sint32 real_game_size_y = m_config->get_base_screen_size_y()-m_config->get_score_size_y();
	Sint32 game_size_x=m_config->get_base_screen_size_x();
	Sint32 game_size_y=m_config->get_base_screen_size_y();
	Screen* screen = Screen::instance(); 
	screen->fill_rect(0, real_game_size_y, game_size_x, game_size_y,0,0,0);
	
	Font_Manager* font_man = Font_Manager::instance();
	
	Font* game_font = font_man->get_font(m_game_font);
	
	Font* time_font = font_man->get_font(m_time_font);
	
	char text[255];
	
	sprintf(text, "Score: %d", (Sint32)m_level->get_current_score());
	
	game_font->write(4,real_game_size_y+5, text);

	// find how many score to complete level
	Sint32 remaining=(Sint32)(m_level->get_min_score()-m_level->get_current_score());

	if(remaining>0)
	{
		sprintf(text,"Remaining:   %d", remaining);
		game_font->write(200,real_game_size_y+5, text);

	}
	else
	{
    if(m_level->is_player_exited())
		{
			game_font->write(200,real_game_size_y+5, "Well done!");
		}
		else
		{
			game_font->write(200,real_game_size_y+5, "Find Exit");
		}

	}

	//draw_time
	char time_string[10];
	sprintf(time_string, "%s", m_time.get_time_string());
	time_font->write(game_size_x-k_sprite_size*2,game_size_y-k_sprite_size, time_string);

	
	if(!m_level->is_player_alive())
	{
		game_font->write(380,real_game_size_y+5, "Press Space");
	}
	
	Surface_Manager* surf_man = Surface_Manager::instance();
	
	ScreenCoord scr_coord;
	
	if(m_level->get_acquired_keys()&1)
	{
		scr_coord.x = game_size_x-k_sprite_size/2;
		scr_coord.y = game_size_y-k_sprite_size/2;
		surf_man->get_surface(Surface_Manager::SRF_KEY_RED_THUMB)->put_screen(scr_coord);
	}
	
	if(m_level->get_acquired_keys()&2)
	{
		scr_coord.x = game_size_x-k_sprite_size;
		scr_coord.y = game_size_y-k_sprite_size/2;
		surf_man->get_surface(Surface_Manager::SRF_KEY_BLUE_THUMB)->put_screen(scr_coord);
	}
	
	if(m_level->get_acquired_keys()&4)
	{
		scr_coord.x = game_size_x-(k_sprite_size+k_sprite_size/2);
		scr_coord.y = game_size_y-k_sprite_size/2;
		surf_man->get_surface(Surface_Manager::SRF_KEY_GREEN_THUMB)->put_screen(scr_coord);
	}
	
	if(m_level->get_acquired_keys()&8)
	{
		scr_coord.x = game_size_x-2*k_sprite_size;
		scr_coord.y =game_size_y-k_sprite_size/2;
		surf_man->get_surface(Surface_Manager::SRF_KEY_YELLOW_THUMB)->put_screen(scr_coord);
	}
	
	//screen->fill_rect(0, real_game_size_y, game_size_x, game_size_y,100,50,10);

}






void Game::play_level(const char *level_path)
{
	m_level=new Level();
        
	m_level->load_map(level_path);
                                                        
        
	main_loop();
	return;
}



void Game::load_fonts()
{
	
	DEBOUT("Loading fonts... ");
	
	Font_Manager::instance();

	m_game_font=Font_Factory::GAME_FONT;

	m_time_font=Font_Factory::TIME_FONT;
	
	m_credits_font=Font_Factory::CREDITS_FONT;
	
	DEBOUT("done.\n");

}


Game::~Game()
{
	
}


void Game::show_loading()
{
	Screen* screen = Screen::instance();
	
	screen->reset_virtual_screen_size();
	
	Font* ready_font = Font_Manager::instance()->get_font(Font_Factory::MENU_FONT);
	
	screen->clear();
	
	ready_font->write_center(100, "Ready!");
	
	screen->flip_display();
	
	Music_Manager::instance()->play(MUS_READY);
	
	//music duration
	SDL_Delay(1940);
	
}

Game::Game(Uint32 level_number)
{
	this->m_current_level_number = level_number;
}

void Game::create()
{
	load_fonts();

	m_level=new Level();
  		
	char current_level_path[255];

	sprintf(current_level_path, "%s/maps/level%d.map",
			Resource_Factory::instance()->get_resource_path().c_str(),
			m_current_level_number);

	DEBOUT("Loading map: "<<current_level_path<<"\n");

	m_level->load_map(current_level_path);
	
	show_loading();

	Music_Manager::instance()->play(MUS_GAME);
	
	Uint32 current_frame_time = 0;
	
	bool exit_state=false;
	
	m_time.set_total_time(m_level->get_max_time());

	m_time.start();

	Screen::instance()->resize_world_screen(m_level->get_size_x()*k_sprite_size, m_level->get_size_y()*k_sprite_size);
	
	Screen::instance()->set_camera_position(m_level->get_player_sprite_position());
	
}

void Game::update(double elapsed)
{
	Input* input = Input::instance();
	
	input->update();

	if((m_level->is_player_alive())||
				((!input->get_fire())&&(!input->get_enter())&&(!input->get_die()))
				)
	{

		if(input->get_pause())
		{
			SDL_Delay(200);
			input->update();
			while(!input->get_pause())
			{
				input->update();
			}
		}
		
		if(m_level->is_player_alive())
		{

			m_time.update();

			if(m_time.get_time()<10)
			{
				
				Sample_Manager::instance()->play(SFX_GAME_TIMEALARM);

			}

			if(m_time.is_zero())
			{

				m_level->do_explode_player();

			}

		}
		
		double current_frame_time=SDL_GetTicks();
		
		get_keys();
		
		move_all();

		Uint32 msec_per_frame = Epiconfig::instance()->get_msec_per_frame();
		
		Uint32 valid_frames = Epiconfig::instance()->get_frame_skip()+1;
		
		for(Uint32 j=0;j < Epiconfig::instance()->get_max_anim_drawn();j++)
		{
			current_frame_time=SDL_GetTicks();
			if((j % valid_frames)==0)
			{
				_draw(j, false);
			}
			else
			{
				_draw(j, true);
			}

			if(Epiconfig::instance()->is_frame_limiter_enabled())
			{
				while(SDL_GetTicks()-current_frame_time<msec_per_frame)
				{
					if((SDL_GetTicks()-current_frame_time)<(msec_per_frame-5))
					{
						SDL_Delay(5);
					}
				}
			}
		
		}
		//input->update();
		return;
	}
	
	bool exit_state=m_level->is_player_exited();	
	
	SDL_Delay(500);
    	 	
	delete m_level;

	switch(exit_state)
	{
	case false:
		DEBWARN("Game_over!...");
		Music_Manager::instance()->play(MUS_MENU);
		GameManager::instance()->change_state(new Menu_State());
		break;
	case true:
		DEBWARN("Winner! ;)");
		Uint32 unsolved_level = Epiconfig::instance()->get_last_level();
		Uint32 total_levels = GameManager::instance()->find_levels_in_dir();
		bool next_level_exists = (unsolved_level==m_current_level_number)&&(unsolved_level+1>total_levels);
		if(next_level_exists)
		{
			Epiconfig::instance()->set_last_level(unsolved_level+1);
		
			GameManager::instance()->change_state(new Game(unsolved_level+1));
		}
		else
		{
			//TODO: maybe a congratulation screen
			Music_Manager::instance()->play(MUS_MENU);
			GameManager::instance()->change_state(new Menu_State());
		}
	
		break;
	}		
}

void Game::deinit()
{
	
}

void Game::draw()
{

}
