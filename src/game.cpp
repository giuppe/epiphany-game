/***************************************************************************
                          game.cpp  -  description
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
#include <SDL/SDL.h>
#include <string>
#include <cassert>

#include "sfx.h"



bool Game::main_loop()
{
	
	Music_Manager::instance()->play(MUS_GAME);
	
	Uint32 current_frame_time=0;
	
	bool exit_state=false;
	
	m_time.set_total_time(m_level->get_max_time());

	m_time.start();

	Screen::instance()->set_window_center(m_level->get_player().get_position_x()*k_sprite_size,m_level->get_player().get_position_y()*k_sprite_size);

	Input* input = Input::instance();
	
	input->update();

	while((m_level->get_player().is_alive())||
				(!input->get_fire())
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
		
		if(m_level->get_player().is_alive())
		{

			m_time.update();

			if(m_time.get_time()<10)
			{
				
				Sample_Manager::instance()->play(SFX_GAME_TIMEALARM);

			}

			if(m_time.is_zero())
			{

				m_level->explode(m_level->get_player().get_position_x(),m_level->get_player().get_position_y());

			}

		}
		
		current_frame_time=SDL_GetTicks();
		
		get_keys();
		
		move_all();

		Uint32 msec_per_frame=m_config->get_msec_per_frame();
		
		Uint32 valid_frames = m_frame_skip+1;
		
		for(Uint32 j=0;j<m_config->get_max_anim_drawn();j++)
		{
			current_frame_time=SDL_GetTicks();
			if((j%valid_frames)==0)
			{
				draw(j, false);
			}
			else
			{
				draw(j, true);
			}

			if(m_frame_limiter_enabled==true)
			{
				while(SDL_GetTicks()-current_frame_time<msec_per_frame)
				{
					if((SDL_GetTicks()-current_frame_time)<(msec_per_frame-10))
					{
						SDL_Delay(10);
					}
				}
			}
		
		}
		input->update();
	}
	
	exit_state=m_level->get_player().is_exited();	
	
	return exit_state;
	
}




void Game::get_keys()
{

	
	//direzione iniziale
	
	Input* input = Input::instance();
	input->update();
	Direction direction=STOP;
	
	if((input->get_quit())&&(m_level->get_player().is_alive()))
	{
			
		m_level->explode(m_level->get_player().get_position_x(),m_level->get_player().get_position_y());
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
		m_level->get_player().set_snap(true);
	}
	else
	{
		m_level->get_player().set_snap(false);
	}
	
}




void Game::move_all()
{

	std::vector< std::vector<Entity_Handle> >& matrix=m_level->get_entities_matrix();

	m_level->get_player().set_speed(1);

	Uint32 i,x,y;
	for(x=0;x<m_config->get_map_size_x();x++)
	{
		for(y=0;y<m_config->get_map_size_y();y++)
		{
			matrix[x][y]=0;
		}
	}
	Entity* curr_entity;
	for(i=1; i<Entity_Manager::instance()->size(); i++)
	{	
		curr_entity = Entity_Manager::instance()->get_entity(i);
		if(curr_entity->exists())
		{
			curr_entity->set_checked(false);
			matrix[curr_entity->get_position_x()][curr_entity->get_position_y()]=i;
		}
	}
	
	
	for(i=1; i<Entity_Manager::instance()->size(); i++)
	{
		curr_entity = Entity_Manager::instance()->get_entity(i);
		
		if(curr_entity->exists())
		{
			if((curr_entity->get_type()!=PLAYER)||(curr_entity->get_type()!=STEEL)||(curr_entity->get_type()!=GRASS))
				curr_entity->check_and_do();
		}
	}
	
	if(m_level->get_player().exists())
	{
		m_level->get_player().check_and_do();
	}
	
}




void Game::draw(Uint32 frame_number, bool update_only)
{

	Entity* curr_ntt;
	Screen* screen = Screen::instance();
	screen->clear();
	
	//centering screen on player
	screen->set_window_center(m_level->get_player().get_sprite().get_pos_x(),m_level->get_player().get_sprite().get_pos_y());

	//drawing player
	if(m_level->get_player().exists())
	{
		m_level->get_player().get_sprite().update_frame();
		m_level->get_player().get_sprite().move();
		if(update_only == false)
		{
			screen->put(m_level->get_player().get_sprite());
		}
	}

	//draw other entities
	for(Uint32 i=1; i<Entity_Manager::instance()->size(); i++)
	{
		curr_ntt=Entity_Manager::instance()->get_entity(i);
		if((curr_ntt->exists())&&(curr_ntt->get_type()!=PLAYER))
		{
			curr_ntt->get_sprite().update_frame();
			curr_ntt->get_sprite().move();
			if(update_only == false)
			{
				screen->put(curr_ntt->get_sprite());
			}
		}
	}
	if(update_only == false)
	{
	draw_score();
	
	screen->flip_display();
	}
	
}




void Game::draw_score()
{
	
	Sint32 real_game_size_y = m_config->get_screen_size_y()-m_config->get_score_size_y();
	Sint32 game_size_x=m_config->get_screen_size_x();
	Sint32 game_size_y=m_config->get_screen_size_y();
	Screen* screen = Screen::instance(); 
	screen->fill_rect(0, real_game_size_y, game_size_x, game_size_y,0,0,0);
	
	Font_Manager* font_man = Font_Manager::instance();
	
	Font* game_font = font_man->get_font(m_game_font);
	
	Font* time_font = font_man->get_font(m_time_font);
	
	char text[255];
	
	sprintf(text, "%s",("Score: "));
	
	sprintf(text, "%s%d", text,(Sint32)m_level->get_player().get_score());
	
	game_font->write(4,real_game_size_y+5, text);

	// find how many score to complete level
	Sint32 remaining=(Sint32)(m_level->get_min_score()-m_level->get_player().get_score());

	if(remaining>0)
	{
		sprintf(text,"%s","Remaining:   ");
		sprintf(text,"%s%d", text, remaining);
		game_font->write(200,real_game_size_y+5, text);

	}
	else
	{
    if(m_level->get_player().is_exited())
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

	
	if(!m_level->get_player().is_alive())
	{
		game_font->write(380,real_game_size_y+5, "Press Space");
	}
	
	Surface_Manager* surf_man = Surface_Manager::instance();
	
	if(m_level->get_acquired_keys()&1)
	{
		surf_man->get_surface(Surface_Manager::SRF_KEY_RED_THUMB)->put_screen(game_size_x-k_sprite_size/2,game_size_y-k_sprite_size/2, k_sprite_size/2,k_sprite_size/2);
	}
	
	if(m_level->get_acquired_keys()&2)
	{
		surf_man->get_surface(Surface_Manager::SRF_KEY_BLUE_THUMB)->put_screen(game_size_x-k_sprite_size,game_size_y-k_sprite_size/2, k_sprite_size/2,k_sprite_size/2);
	}
	
	if(m_level->get_acquired_keys()&4)
	{
		surf_man->get_surface(Surface_Manager::SRF_KEY_GREEN_THUMB)->put_screen(game_size_x-(k_sprite_size+k_sprite_size/2),game_size_y-k_sprite_size/2, k_sprite_size/2,k_sprite_size/2);
	}
	
	if(m_level->get_acquired_keys()&8)
	{
		surf_man->get_surface(Surface_Manager::SRF_KEY_YELLOW_THUMB)->put_screen(game_size_x-2*k_sprite_size,game_size_y-k_sprite_size/2, k_sprite_size/2,k_sprite_size/2);
	}
	
	//screen->fill_rect(0, real_game_size_y, game_size_x, game_size_y,100,50,10);

}




void Game::go()
{


	Menu menu(m_max_num_of_levels,m_unsolved_level);

	Music_Manager::instance()->play(MUS_MENU);
	
	Sint32 play=menu.go();
	
	while(play!=Menu::MENU_EPIPHANY_QUIT)
	{
		
		if(play==Menu::MENU_EPIPHANY_START)
  		{
  		
			m_level=new Level();
  		
			char current_level_path[255];
  		
			sprintf(current_level_path, "%s", (Resource_Factory::instance()->get_resource_path().c_str()));
  		
			sprintf(current_level_path, "%s%s", current_level_path, "/maps/level");
  	
			sprintf(current_level_path, "%s%d", current_level_path, (menu.get_current_level()));
  		
			sprintf(current_level_path, "%s%s", current_level_path, ".map");
  	
			DEBOUT("Loading map: "<<current_level_path<<"\n");
  	
			m_level->load_map(current_level_path);
  			
  			show_loading();
  			  	
			bool result=main_loop();
  	
			SDL_Delay(500);
    	 	
			//APOI: Might add some Hiscores here...

			delete m_level;
  		
			switch(result)
			{
			case false:
				DEBWARN("Game_over!...");
				Music_Manager::instance()->play(MUS_MENU);
				play=menu.go();
				break;
			case true:
				DEBWARN("Winner! ;)");
  				
  				if((menu.get_unsolved_level()==menu.get_current_level())&&(menu.increase_unsolved_level()))
				{
					save_last_level(menu.get_unsolved_level());
				
					menu.set_current_level(menu.get_unsolved_level());
				
					play=Menu::MENU_EPIPHANY_START;
				}
				else
				{
         			//TODO: maybe a congratulation screen
         			Music_Manager::instance()->play(MUS_MENU);
         			play=menu.go();
				}
  			
  				break;
			}		
		}
 /* 		else if(play==Menu::MENU_EPIPHANY_CREDITS)
  		{
  			show_credits();
  			play=menu.go();
		}
*/		else if(play==Menu::MENU_EPIPHANY_NONE)
		{
			play=menu.go();
		}
  	
	}
	

	
	this->show_credits();
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
	if(user_home=="")
	{
		assert(!"Unable to find HOME environment variable");
	}
	else
	{
		user_home+="/.epiphany";
		sprintf(m_ini_path, "%s", user_home.c_str());
	}
	#endif


	m_config->read_values_from_file(m_ini_path);

	Sample_Manager::instance()->set_volume(m_config->get_volume_sound());
	
	Music_Manager::instance()->set_volume(m_config->get_volume_music());
	
	
	DEBOUT("Loading config...\n");
	load_config();	
	
	
	DEBOUT("Loading fonts...\n");
	load_fonts();
	

	DEBOUT("Initing Screen...\n");
	Screen::instance()->init(m_config->get_screen_size_x(),m_config->get_screen_size_y(),m_config->get_map_size_x(), m_config->get_map_size_y(), k_sprite_size);
	
}


void Game::play_level(const char *level_path)
{
	m_level=new Level();
        
	m_level->load_map(level_path);
                                                        
        
	main_loop();
	return;
}


void Game::load_config()
{
	
	m_unsolved_level = Epiconfig::instance()->get_last_level();
	
	m_max_num_of_levels=find_levels_in_dir();
}

Uint32 Game::find_levels_in_dir()
{
	Uint32 result = 0;
	char base_path[255];
	char level_path[255];
	
	sprintf(base_path, "%s%s", Resource_Factory::instance()->get_resource_path().c_str(), "/maps/level");
	
	sprintf(level_path, "%s%d%s", base_path, result, ".map");
	FILE* pFile = fopen (level_path,"r");
	while(pFile != NULL)
	{
		DEBOUT("Found "<<level_path<<".\n");
		fclose(pFile);
		result++;
		sprintf(level_path, "%s%d%s", base_path, result, ".map");
		pFile = fopen (level_path,"r");
	}
	return result;
}

void Game::load_fonts()
{
	
	DEBOUT("Loading fonts... ");

	m_game_font=Font_Factory::GAME_FONT;

	m_time_font=Font_Factory::TIME_FONT;
	
	m_credits_font=Font_Factory::CREDITS_FONT;
	
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


void Game::show_credits()
{
	
	
	
	Sint32 current_frame_time=0;

	std::vector<std::string> credits;

	credits.push_back("Epiphany");
	credits.push_back(" ");
	credits.push_back("Giuseppe D'Aqui':");
	credits.push_back("    Coding, Level Design, Graphics, Music");
	credits.push_back(" ");
	credits.push_back("Giuseppe Martino:");
	credits.push_back("    Coding, Level Design");
	//credits.push_back("Antonio Malara: Graphics");
	credits.push_back(" ");
	credits.push_back("Thanks to:");
	credits.push_back("  Joerg Jaspert, for Debian Packages");
	credits.push_back("  Eric Mangold, for Level Editor");
	credits.push_back(" ");
	credits.push_back("Released under General Public License v2");
	credits.push_back("See COPYING for details.");

	//standard method: text scrolling
	
	Uint32 i;
	
	Input* input =Input::instance();
	input->reset_states();
	//input->update(); 
	
	Screen* screen = Screen::instance();
	
	Font* credits_font = Font_Manager::instance()->get_font(m_credits_font);
	
	Music_Manager::instance()->play(MUS_CREDITS);
	
	
	while(!(input->get_quit()||input->get_enter()||input->get_fire()))
	{
		current_frame_time=SDL_GetTicks();
		screen->clear();
		
		for(i=0; i<credits.size(); i++)
		{
			credits_font->write(32, 32+30*i,credits[i].c_str());
			
		}
		
  		// draws two black movie-like bands


		while(SDL_GetTicks()-current_frame_time<20)
		{
			if(SDL_GetTicks()-current_frame_time<15)
			{
				SDL_Delay(5);
			}
		}
		screen->flip_display();
		

		input->update();
	}

}

void Game::show_loading()
{
	Screen* screen = Screen::instance();
	
	Font* ready_font = Font_Manager::instance()->get_font(Font_Factory::MENU_FONT);
	
	screen->clear();
	
	ready_font->write_center(100, "Ready!");
	
	screen->flip_display();
	
	Music_Manager::instance()->play(MUS_READY);
	
	SDL_Delay(1940);
	
}



Game* Game::_instance = 0;

Game* Game::instance()
{
	if(_instance==0)
	{
		_instance=new Game();
		_instance->init();

	}
	return _instance;
}


