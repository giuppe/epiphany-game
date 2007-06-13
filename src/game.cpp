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
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
#include "dephine.h"
#include "sprite.h"
#include <vector>
#include <cmath>
#include <fstream>
#include "entity_type.h"
#include "entity_factory.h"
#include "fonts/font_factory.h"
#include "entity.h"
#include "entities/entity_player.h"
#include "surface_manager.h"
#include "surface_factory.h"
#include "game.h"
#include "menu.h"
#include "input.h"
#include "level.h"
#include "game_timer.h"
#include <cstdlib>
#include <SDL/SDL.h>
#include <cstring>

#include "sfx.h"



bool Game::main_loop()
{
	
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
		
		//m_level->get_player().set_direction(STOP);
		
		get_keys();
		
		move_all();

//		Uint32 current_frame_time=0;

		Uint32 msec_per_frame=m_config->get_msec_per_frame();

		for(Uint32 j=0;j<m_config->get_max_anim_drawn();j++)
		{
			current_frame_time=SDL_GetTicks();
		
			draw(j);

			if(j==m_config->get_max_anim_drawn()/2)
			{
				get_keys();
			}

			while(SDL_GetTicks()-current_frame_time<msec_per_frame);
			{
				if(SDL_GetTicks()-current_frame_time<msec_per_frame-10)
				{
					SDL_Delay(10);
				}
			}
		
			input->update();
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
	for(x=0;x<m_config->get_level_size_x();x++)
	{
		for(y=0;y<m_config->get_level_size_y();y++)
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

void Game::draw(int frame_number)
{


	//std::vector<Ntt_pointer>& list=m_level->get_entities_list();

	//Ntt_pointer curr_ntt;
	Entity* curr_ntt;
	Screen* screen = Screen::instance();
	screen->clear();
	
	//centering screen on player
	screen->set_window_center(m_level->get_player().get_sprite().get_pos_x(),m_level->get_player().get_sprite().get_pos_y());

	//drawing player
	if(m_level->get_player().exists())
	{
		//m_level->get_player().get_sprite().set_curr_frame(frame_number*(k_sprite_size/m_config->get_max_anim_drawn())/4);
		m_level->get_player().get_sprite().update_frame();
		//m_level->get_player().get_sprite().move(k_sprite_size/m_config->get_max_anim_drawn());
		m_level->get_player().get_sprite().move();
		screen->put(m_level->get_player().get_sprite());
	}

	//draw other entities
	for(Uint32 i=1; i<Entity_Manager::instance()->size(); i++)
	{
		curr_ntt=Entity_Manager::instance()->get_entity(i);
		if((curr_ntt->exists())&&(curr_ntt->get_type()!=PLAYER))
		{
			//curr_ntt->get_sprite().set_curr_frame(frame_number*(k_sprite_size/m_config->get_max_anim_drawn())/4);
			//curr_ntt->get_sprite().move(k_sprite_size/m_config->get_max_anim_drawn());
			curr_ntt->get_sprite().update_frame();
			curr_ntt->get_sprite().move();
			screen->put(curr_ntt->get_sprite());
		}
	}
	
	draw_score();
	
	screen->flip_display();

}




void Game::draw_score()
{
	
	Sint32 real_game_size_y = m_config->get_game_size_y()-m_config->get_score_size_y();
	Sint32 game_size_x=m_config->get_game_size_x();
	Sint32 game_size_y=m_config->get_game_size_y();
	Screen* screen = Screen::instance(); 
	screen->fill_rect(0, real_game_size_y, game_size_x, game_size_y,0,0,0);
	
	Font_Manager* font_man = Font_Manager::instance();
	
	Font* game_font = font_man->get_font(m_game_font);
	
	Font* time_font = font_man->get_font(m_time_font);
	
	std::string text("Score: ");
	text+=(Sint32)m_level->get_player().get_score();
	game_font->write(4,real_game_size_y+5, text.c_str());

	// find how many score to complete level
	Sint32 remaining=(Sint32)(m_level->get_min_score()-m_level->get_player().get_score());

	if(remaining>0)
	{

		game_font->write(200,real_game_size_y+5, CL_String("Remaining:   ")+CL_String(remaining));

	}
	else
	{
    if(m_level->get_player().is_exited())
		{
			game_font->write(200,real_game_size_y+5, CL_String("Well done!"));
		}
		else
		{
			game_font->write(200,real_game_size_y+5, CL_String("Find Exit"));
		}

	}

	//draw_time
	CL_String time_string=m_time.get_time_string();
	time_font->write(game_size_x-k_sprite_size*2,game_size_y-k_sprite_size, time_string);

	
	if(!m_level->get_player().is_alive())
	{
		game_font->write(380,real_game_size_y+5, CL_String("Press Space"));
	}
	
	Surface_Manager* surf_man = Surface_Manager::instance();
	
	if(m_level->get_acquired_keys()&1)
	{
		surf_man->get_surface(KEY_RED)->put_screen(game_size_x-k_sprite_size/2,game_size_y-k_sprite_size/2, k_sprite_size/2,k_sprite_size/2);
	}
	
	if(m_level->get_acquired_keys()&2)
	{
		surf_man->get_surface(KEY_BLUE)->put_screen(game_size_x-k_sprite_size,game_size_y-k_sprite_size/2, k_sprite_size/2,k_sprite_size/2);
	}
	
	if(m_level->get_acquired_keys()&4)
	{
		surf_man->get_surface(KEY_GREEN)->put_screen(game_size_x-(k_sprite_size+k_sprite_size/2),game_size_y-k_sprite_size/2, k_sprite_size/2,k_sprite_size/2);
	}
	
	if(m_level->get_acquired_keys()&8)
	{
		surf_man->get_surface(KEY_YELLOW)->put_screen(game_size_x-2*k_sprite_size,game_size_y-k_sprite_size/2, k_sprite_size/2,k_sprite_size/2);
	}
	
	screen->draw_rect(0, real_game_size_y, game_size_x, game_size_y,100,50,10);

}

void Game::go()
{

//	DEBOUT("Entering Game::go()...\n");
	
//	DEBOUT("Entering main loop...\n");
	Menu menu(m_max_num_of_levels,m_unsolved_level);

	Sint32 play=menu.go();
	
  while(play!=3)
  {
  	if(play==0)
  	{
  		
  		m_level=new Level();
  		
  		CL_String current_level_path(Resource_Factory::instance()->get_resource_path());
  		
  		current_level_path=current_level_path+"/maps/level";
  	


  		current_level_path=current_level_path+((const Sint32)menu.get_current_level());
  		
  		current_level_path+=".map";
  	
     	try
  		{
  			m_level->load_map(current_level_path);
  			
  		}
  		catch(Common_Ex e)
  		{
  			std::cout<<e.get_message();
  			return;
  		}
  	
  		bool result=main_loop();
  	
  		SDL_Delay(500);
    	
 	
  		//HACKSOMETHINGHERE
  		//Might add some Hiscores here...
  		delete m_level;
  		
  		switch(result)
  		{
   		case false:
  			DEBOUT("Game_over!...");
  			play=menu.go();
  			break;
  		case true:
  			DEBOUT("Winner! ;)");
  			
       if((menu.get_unsolved_level()==menu.get_current_level())&&(menu.increase_unsolved_level()))
       {

           ofstream update_config(m_ini_path);
           update_config<<menu.get_unsolved_level();
           menu.set_current_level(menu.get_unsolved_level());
           play=0;
       }
       else
       {
         //do nothing.. maybe a congratulation screen
         play=menu.go();
       }
  			
  			break;
  		}		
  	}
  	else if(play==2)
  	{
  		show_credits();
  		play=menu.go();
	  }	
  	
  }
}



void Game::init()
{

	DEBOUT("Entering Game::init()...\n");
	DEBOUT("Loading default configuration values...\n");
	m_config = Epiconfig::instance();
	m_config->set_default_values();

	
	
	#ifdef _WIN32
	m_ini_path="./epiphany.ini";
	#else
	CL_String user_home=getenv("HOME");
	if(user_home=="")
	{
		throw Common_Ex("Unable to find HOME environment variable");
	}
	else
	{
		m_ini_path=user_home+"/.epiphany";
	}
	#endif


	
	DEBOUT("Loading config...\n");
	load_config();	
	
	DEBOUT("Loading Surfaces...\n");
	load_surfaces();
	
	
	DEBOUT("Loading fonts...\n");
	try
	{
		load_fonts();
	}
	catch(CL_Error ex)
	{
		throw Common_Ex(ex.message.c_str());
	}
	
	
	/*
	m_spriteset=Spriteset("SPT");
	DEBOUT("Loading sprites...\n");
	try
	{
		m_spriteset.load_sprites();
	}
	catch(CL_Error ex)
	{
		throw Common_Ex(ex.message.c_str());
	}
	*/
	DEBOUT("Loading samples...\n");
	
	Sample_Manager* m_sampleset=Sample_Manager::instance();
	try
	{
		m_sampleset->load_samples();
	}
	catch(CL_Error ex)
	{
		throw Common_Ex(ex.message.c_str()) ;
	}
	

	DEBOUT("Initing Screen...\n");
	Screen::instance()->init(m_config->get_game_size_x(),m_config->get_game_size_y(),m_config->get_level_size_x(), m_config->get_level_size_y(), k_sprite_size);
	/*
	Entity_Factory* entity_factory = Entity_Factory::instance();
	entity_factory->set_spriteset(this->m_spriteset);
	*/
	//DEBOUT("Exiting Game ctor... \n");
	
}

void Game::load_surfaces()
{
	CL_String surface_path=CL_String("Surfaces/SPT_");
	Surface_Manager* surf_man = Surface_Manager::instance();
	surf_man->init();
	/*
	Surface_Factory* surf_factory = Surface_Factory::instance();
	
	surf_man->add_surface(UNKNOWN, new Surface(new CL_Surface(surface_path+"Unknown", m_res_manag)));
	
	surf_man->add_surface(PLAYER, new Surface(new CL_Surface(surface_path+"Player", m_res_manag)));

	surf_man->add_surface(GRASS, new Surface(new CL_Surface(surface_path+"Grass", m_res_manag)));
	
	surf_man->add_surface(STEEL, new Surface(new CL_Surface(surface_path+"Steel", m_res_manag)));
	
	surf_man->add_surface(EMERALD, new Surface(new CL_Surface(surface_path+"Emerald", m_res_manag)));
	
	surf_man->add_surface(BOULDER, new Surface(new CL_Surface(surface_path+"Boulder", m_res_manag)));

	surf_man->add_surface(SAPPHIRE, new Surface(new CL_Surface(surface_path+"Sapphire", m_res_manag)));
		
	surf_man->add_surface(EXIT, new Surface(new CL_Surface(surface_path+"Exit", m_res_manag)));
	
	surf_man->add_surface(EXPLOSION, new Surface(new CL_Surface(surface_path+"Explosion", m_res_manag)));
	
	surf_man->add_surface(DOOR_RED, new Surface(new CL_Surface(surface_path+"Door_Red", m_res_manag)));
	
	surf_man->add_surface(DOOR_BLUE, new Surface(new CL_Surface(surface_path+"Door_Blue", m_res_manag)));

	surf_man->add_surface(DOOR_GREEN, new Surface(new CL_Surface(surface_path+"Door_Green", m_res_manag)));
	
	surf_man->add_surface(DOOR_YELLOW, new Surface(new CL_Surface(surface_path+"Door_Yellow", m_res_manag)));

	surf_man->add_surface(KEY_RED, new Surface(new CL_Surface(surface_path+"Key_Red", m_res_manag)));	

	surf_man->add_surface(KEY_BLUE, new Surface(new CL_Surface(surface_path+"Key_Blue", m_res_manag)));	

	surf_man->add_surface(KEY_GREEN, new Surface(new CL_Surface(surface_path+"Key_Green", m_res_manag)));	

	surf_man->add_surface(KEY_YELLOW, new Surface(new CL_Surface(surface_path+"Key_Yellow", m_res_manag)));	


	surf_man->add_surface(FLINTSTONE, new Surface(new CL_Surface(surface_path+"Flintstone", m_res_manag)));	
	
	surf_man->add_surface(PEPERON, new Surface(new CL_Surface(surface_path+"Peperon", m_res_manag)));	
	
	surf_man->add_surface(BRICK, new Surface(new CL_Surface(surface_path+"Brick", m_res_manag)));
	
	surf_man->add_surface(WOOD, new Surface(new CL_Surface(surface_path+"Wood", m_res_manag)));

	surf_man->add_surface(TOMATO, new Surface(new CL_Surface(surface_path+"Tomato", m_res_manag)));
*/
}

void Game::play_level(const char *level_path)
{
        m_level=new Level();
        
        try
        {
                m_level->load_map(level_path);
                                                        
        }
        catch(Common_Ex e)
        {
                std::cout<<e.get_message();
                return;
		}

        main_loop();
        return;
}


void Game::load_config()
{
	std::ifstream config_file(m_ini_path);
	
	if(!config_file)
	{
		DEBOUT("No "<<m_ini_path<<"; Creating...\n");
		std::ofstream new_config(m_ini_path);
		if(!new_config)
			throw Common_Ex("Unable to write config file!...\n");
		m_unsolved_level=0;
		new_config<<m_unsolved_level;
		return;
	}
	config_file>>m_unsolved_level;
	//find max_num_of_levels
/*	CL_DirectoryScanner dirscan;
	Uint32 i=0;
	if(dirscan.scan(CL_String(Resource_Factory::instance()->get_resource_path())+"/maps", "level*.map"))
	{
		//;
		while(dirscan.next()==true)
		{
			i++;
		}
	}*/
	m_max_num_of_levels=12;
}
	

void Game::load_fonts()
{
	
	
	DEBOUT("Loading fonts... ");
	try
	{
		m_game_font=Font_Factory::GAME_FONT;

		m_time_font=Font_Factory::TIME_FONT;
		m_credits_font=Font_Factory::CREDITS_FONT;
	}
	catch(CL_Error ex)
	{
		throw Common_Ex(ex.message.c_str());
	}
	
	DEBOUT("done.\n");

}

Game::~Game()
{

	

}


void Game::show_credits()
{
	
	Sint32 current_frame_time=0;

	vector<CL_String> credits;

	credits.push_back("Epiphany");
	credits.push_back(" ");
	credits.push_back("Coding:");
	credits.push_back("Giuseppe D'Aqu�");
	credits.push_back("Giuseppe Martino");
	credits.push_back(" ");
	credits.push_back("Level Designing:");
	credits.push_back("Giuseppe D'Aqu�");
	credits.push_back("Giuseppe Martino");
	credits.push_back(" ");
	credits.push_back("Graphics:");
	credits.push_back("Giuseppe D'Aqu�");
	credits.push_back("Antonio Malara");
	credits.push_back(" ");
	credits.push_back("Epiphany Map Definition Language:");
	credits.push_back("Giuseppe Martino");
	credits.push_back(" ");
	credits.push_back("Thanks to:");
	credits.push_back("Antonio Malara");
	credits.push_back("Giuseppe Martino");
	credits.push_back("Kenneth Gangstoe");
	credits.push_back("Joerg Jaspert");
	credits.push_back("All ClanLib developers");
	
	//alpha blending too slow
	//CL_Surface* srf_top = new CL_Surface("Surfaces/MNU_Top", m_res_manag);
	//CL_Surface* srf_bottom = new CL_Surface("Surfaces/MNU_Bottom", m_res_manag);

	Sint32 draw_pos=m_config->get_game_size_y();

//standard method: text scrolling
	
	Uint32 i;
	
	Input* input =Input::instance();
	input->update(); 
	
	Screen* screen = Screen::instance();
	
	Font* credits_font = Font_Manager::instance()->get_font(m_credits_font);
	
	while(!input->get_quit())
	{
		current_frame_time=SDL_GetTicks();
		screen->clear();
		
		for(i=0; i<credits.size(); i++)
		{
			credits_font->write_center(draw_pos+50*i,credits[i]);
			
		}
		
    if(draw_pos+50*credits.size()>0)
		{
			draw_pos-=(Sint32)(((SDL_GetTicks()-current_frame_time)/20)+1);
		}
		else
		{
			draw_pos=m_config->get_game_size_y();
		}

  //alpha blending too slow
//		srf_top->put_screen(0,0);
//		srf_bottom->put_screen(0,k_game_size_y-100);

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

/*
Resource_Factory* Game::get_resource_manager()
{
	return m_res_manag;
}
*/

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


