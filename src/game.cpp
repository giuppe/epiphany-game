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
#include "entity.h"
#include "entities/entity_player.h"
#include "game.h"
#include "menu.h"
#include "level.h"
#include "game_timer.h"
#include <stdlib.h>
#include <string.h>
#include "sfx.h"



bool Game::main_loop()
{
	unsigned int current_frame_time=0;
	
	bool exit_state=false;
	
	m_time.set_total_time(m_level->get_max_time());

	m_time.start();

	m_screen.set_window_center(m_level->get_player().get_position_x()*k_sprite_size,m_level->get_player().get_position_y()*k_sprite_size);


	while((m_level->get_player().is_alive())||
				(!CL_Keyboard::get_keycode(CL_KEY_SPACE))
				
				)
	{
		if((CL_Keyboard::get_keycode(CL_KEY_PAUSE))||(CL_Keyboard::get_keycode(CL_KEY_P)))
		{
			CL_System::sleep(200);
			CL_System::keep_alive();
			while(!((CL_Keyboard::get_keycode(CL_KEY_PAUSE))||(CL_Keyboard::get_keycode(CL_KEY_P))))
			{
				CL_System::keep_alive();
			}
		}
		
		if(m_level->get_player().is_alive())
		{
			m_time.update();
			if(m_time.get_time()<10)
			{
				
				m_sampleset.get_sample(SFX_GAME_TIMEALARM)->play();
			}
			if(m_time.is_zero())
			{
				m_level->explode(m_level->get_player().get_position_x(),m_level->get_player().get_position_y());
			}

		}
		

		current_frame_time=CL_System::get_time();
		
		//m_level->get_player().set_direction(STOP);
		
		get_keys();
		
		move_all();

//		unsigned int current_frame_time=0;

		unsigned int msec_per_frame=m_config->get_msec_per_frame();

		for(unsigned int j=0;j<m_config->get_max_anim_drawn();j++)
		{
			current_frame_time=CL_System::get_time();
		
			draw(j);

			if(j==m_config->get_max_anim_drawn()/2)
			{
				get_keys();
			}

			while(CL_System::get_time()-current_frame_time<msec_per_frame);
			{
				if(CL_System::get_time()-current_frame_time<msec_per_frame-10)
				{
					CL_System::sleep(10);
				}
			}

		CL_System::keep_alive();
		}

	}
	
	exit_state=m_level->get_player().is_exited();	
	
	return exit_state;
	
}

void Game::get_keys()
{

	
	//direzione iniziale
	CL_System::keep_alive();
	
	Direction direction=STOP;
	
	if((CL_Keyboard::get_keycode(CL_KEY_ESCAPE))&&(m_level->get_player().is_alive()))
	{
			
		m_level->explode(m_level->get_player().get_position_x(),m_level->get_player().get_position_y());
		return;
				
	}
	
  //questi if settano la direzione a seconda del tasto premuto
	if(CL_Keyboard::get_keycode(CL_KEY_UP))
	{
			
		direction=UP;
				
	}
	else if(CL_Keyboard::get_keycode(CL_KEY_DOWN))
	{
			
		direction=DOWN;
		
	}
	else if(CL_Keyboard::get_keycode(CL_KEY_RIGHT))
	{
	
		direction=RIGHT;
		
	}
	else if(CL_Keyboard::get_keycode(CL_KEY_LEFT))
	{
	
		direction=LEFT;
		
	}
	if((direction>=UP)&&(direction<=LEFT))
	{
		m_level->get_player().set_direction(direction);
		//DEBOUT("Setting direction: "<<direction<<"\n");
	}
	
	if(CL_Keyboard::get_keycode(CL_KEY_SPACE))
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
	//std::vector<Ntt_pointer>& list=m_level->get_entities_list();
	std::vector< std::vector<Entity_Handle> >& matrix=m_level->get_entities_matrix();

	m_level->get_player().set_speed(1);

	unsigned int i,x,y;
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

	m_screen.clear();
	
	//centering screen on player
	m_screen.set_window_center(m_level->get_player().get_sprite().get_pos_x(),m_level->get_player().get_sprite().get_pos_y());

	//drawing player
	if(m_level->get_player().exists())
	{
		m_level->get_player().get_sprite().set_curr_frame(frame_number*(k_sprite_size/m_config->get_max_anim_drawn())/4);
		m_level->get_player().get_sprite().move(k_sprite_size/m_config->get_max_anim_drawn());
		m_screen.put(m_level->get_player().get_sprite());
	}

	//draw other entities
	for(unsigned int i=1; i<Entity_Manager::instance()->size(); i++)
	{
		curr_ntt=Entity_Manager::instance()->get_entity(i);
		if((curr_ntt->exists())&&(curr_ntt->get_type()!=PLAYER))
		{
			curr_ntt->get_sprite().set_curr_frame(frame_number*(k_sprite_size/m_config->get_max_anim_drawn())/4);
			curr_ntt->get_sprite().move(k_sprite_size/m_config->get_max_anim_drawn());
			m_screen.put(curr_ntt->get_sprite());
		}
	}
	
	draw_score();
	
	m_screen.flip_display();

}




void Game::draw_score()
{
	
	int real_game_size_y = m_config->get_game_size_y()-m_config->get_score_size_y();
	int game_size_x=m_config->get_game_size_x();
	int game_size_y=m_config->get_game_size_y();

	m_screen.fill_rect(0, real_game_size_y, game_size_x, game_size_y,0,0,0,1.0);
	
	m_game_font->print_left(4,real_game_size_y+5, CL_String("Score:   ")+CL_String((int)m_level->get_player().get_score()));

	// find how many score to complete level
	int remaining=(int)(m_level->get_min_score()-m_level->get_player().get_score());

	if(remaining>0)
	{

		m_game_font->print_left(200,real_game_size_y+5, CL_String("Remaining:   ")+CL_String(remaining));

	}
	else
	{
    if(m_level->get_player().is_exited())
		{
			m_game_font->print_left(200,real_game_size_y+5, CL_String("Well done!"));
		}
		else
		{
			m_game_font->print_left(200,real_game_size_y+5, CL_String("Find Exit"));
		}

	}

	//draw_time
	CL_String time_string=m_time.get_time_string();
	m_time_font->print_left(game_size_x-k_sprite_size*2,game_size_y-k_sprite_size, time_string);

	
	if(!m_level->get_player().is_alive())
	{
		m_game_font->print_left(380,real_game_size_y+5, CL_String("Press Space"));
	}
	
	
	if(m_level->get_acquired_keys()&1)
		m_spriteset.get_sprite(KEY).put_screen(game_size_x-k_sprite_size/2,game_size_y-k_sprite_size/2, k_sprite_size/2,k_sprite_size/2,0);
	
	if(m_level->get_acquired_keys()&2)
		m_spriteset.get_sprite(KEY).put_screen(game_size_x-k_sprite_size,game_size_y-k_sprite_size/2, k_sprite_size/2,k_sprite_size/2,8);

	if(m_level->get_acquired_keys()&4)
		m_spriteset.get_sprite(KEY).put_screen(game_size_x-(k_sprite_size+k_sprite_size/2),game_size_y-k_sprite_size/2, k_sprite_size/2,k_sprite_size/2,16);

	if(m_level->get_acquired_keys()&8)
		m_spriteset.get_sprite(KEY).put_screen(game_size_x-2*k_sprite_size,game_size_y-k_sprite_size/2, k_sprite_size/2,k_sprite_size/2,24);

	m_screen.draw_rect(0, real_game_size_y, game_size_x, game_size_y,1,0.5,0,1.0);

}

void Game::go()
{

//	DEBOUT("Entering Game::go()...\n");
	
//	DEBOUT("Entering main loop...\n");
	Menu menu(m_max_num_of_levels,m_unsolved_level);

	int play=menu.go();
	
  while(play!=3)
  {
  	if(play==0)
  	{
  		
  		m_level=new Level(m_spriteset, m_sampleset);
  		
  		CL_String current_level_path(m_resource_path);
  		
  		current_level_path=current_level_path+"/maps/level";
  	


  		current_level_path=current_level_path+((const int)menu.get_current_level());
  		
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
  	
  		CL_System::sleep(500);
    	
  		CL_System::keep_alive();	
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

void Game::set_resource_manager()
{
	//portability "quick hack" :)
	#ifdef _WIN32
	m_resource_path=".";
	#else
	m_resource_path= RESOURCE_PATH;
	#endif
	DEBOUT("Resource_path: "<<m_resource_path<<"\n");

	try
	{
		m_res_manag=new CL_ResourceManager(m_resource_path+"/sprites.scr", false);
	}
	catch(CL_Error ex)
	{
		std::cout<<ex.message<<"\n";
		m_resource_path="./data";

		try
		{
			m_res_manag=new CL_ResourceManager(m_resource_path+"/sprites.scr", false);
		}
		catch(CL_Error ex)
		{
			throw Common_Ex(ex.message.c_str() );
			m_resource_path="../data";

			try
			{
				m_res_manag=new CL_ResourceManager(m_resource_path+"/sprites.scr", false);
			}
			catch(CL_Error ex)
			{
				throw Common_Ex(ex.message.c_str());
				exit(1);
			}
		}
	}
	DEBOUT("Using "<<(m_resource_path+"/sprites.scr")<<" as resource script.\n");


}

void Game::init()
{

	DEBOUT("Entering Game::init()...\n");
	DEBOUT("Loading default configuration values...\n");
	m_config = Epiconfig::instance();
	m_config->set_default_values();

	set_resource_manager();
	
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
	DEBOUT("Loading fonts...\n");
	try
	{
		load_fonts();
	}
	catch(CL_Error ex)
	{
		throw Common_Ex(ex.message.c_str());
	}
	
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
	DEBOUT("Loading samples...\n");
	
	m_sampleset=Sampleset();
	try
	{
		m_sampleset.load_samples();
	}
	catch(CL_Error ex)
	{
		throw Common_Ex(ex.message.c_str()) ;
	}
	

	DEBOUT("Initing Screen...\n");
	m_screen.init(m_config->get_game_size_x(),m_config->get_game_size_y(),m_config->get_level_size_x(), m_config->get_level_size_y(), k_sprite_size);
	
	Entity_Factory* entity_factory = Entity_Factory::instance();
	entity_factory->set_spriteset(this->m_spriteset);
	//DEBOUT("Exiting Game ctor... \n");
	
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
	CL_DirectoryScanner dirscan;
	unsigned int i=0;
	if(dirscan.scan(m_resource_path+"/maps", "level*.map"))
	{
		//;
		while(dirscan.next()==true)
		{
			i++;
		}
	}
	m_max_num_of_levels=i;
}
	

void Game::load_fonts()
{
	DEBOUT("Loading fonts... ");
	try
	{
		m_game_font=CL_Font::load("Fonts/FNT_Game", m_res_manag);

		m_time_font=CL_Font::load("Fonts/FNT_Time", m_res_manag);

		m_credits_font=CL_Font::load("Fonts/FNT_Credits", m_res_manag);
	}
	catch(CL_Error ex)
	{
		throw Common_Ex(ex.message.c_str());
	}
	
	DEBOUT("done.\n");

}

Game::~Game()
{

	delete m_game_font;

	delete m_credits_font;

}


void Game::show_credits()
{
	
	int current_frame_time=0;

	vector<CL_String> credits;

	credits.push_back("Epiphany");
	credits.push_back(" ");
	credits.push_back("Coding:");
	credits.push_back("Giuseppe D'Aquì");
	credits.push_back("Giuseppe Martino");
	credits.push_back(" ");
	credits.push_back("Level Designing:");
	credits.push_back("Giuseppe D'Aquì");
	credits.push_back("Giuseppe Martino");
	credits.push_back(" ");
	credits.push_back("Graphics:");
	credits.push_back("Giuseppe D'Aquì");
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

	int draw_pos=m_config->get_game_size_y();

//standard method: text scrolling
	
	unsigned int i;
	
	while(!CL_Keyboard::get_keycode(CL_KEY_ESCAPE))
	{
		current_frame_time=CL_System::get_time();
		CL_Display::clear_display(0,0,0,1);
		for(i=0; i<credits.size(); i++)
		{
			m_credits_font->print_center(m_config->get_game_size_x()/2,draw_pos+50*i,credits[i]);
			
		}
		
    if(draw_pos+50*credits.size()>0)
		{
			draw_pos-=(int)(((CL_System::get_time()-current_frame_time)/20)+1);
		}
		else
		{
			draw_pos=m_config->get_game_size_y();
		}

  //alpha blending too slow
//		srf_top->put_screen(0,0);
//		srf_bottom->put_screen(0,k_game_size_y-100);

		while(CL_System::get_time()-current_frame_time<20)
		{
			if(CL_System::get_time()-current_frame_time<15)
			{
				CL_System::sleep(5);
			}
		}
		CL_Display::flip_display(true);
		

		CL_System::keep_alive();
	}

}


CL_ResourceManager* Game::get_resource_manager()
{
	return m_res_manag;
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


