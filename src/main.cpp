/***************************************************************************
                          main.cpp  -  description
                             -------------------
    begin                : Wed Aug 15 2001
    copyright            : (C) 2001 by Giuseppe "Quobod" D'Aqu�
    email                : kumber@tiscalinet.it
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License, Version 2,      *
 *   as published by the Free Software Foundation.                         *
 *                                                                         *
 ***************************************************************************/

#include "dephine.h"
#include <SDL2/SDL.h>
#include "surface_manager.h"
#include "resource_factory.h"
#include "music_manager.h"
#include "sfx.h"
#include "input.h"
#include "fonts/font_manager.h"
#include "game.h"
#include "screen.h"




#include "commandline_configuration.h"



	const char* get_title()
	{
		
		return PACKAGE;
	
	}

	void init_modules()
	{
	
		SDL_Init ( SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER );
		
		SDL_Delay(1000);

		Input::instance()->init();
		
		Screen::instance();
		
		Resource_Factory::instance();
			
		Sample_Manager::instance();
		
		Music_Manager::instance();

		Screen::instance()->set_window_title(get_title());
	
	}
	
	void deinit_modules()
	{
		
		Surface_Manager::instance()->deinit();
		
		Music_Manager::instance()->deinit();
		
		Sample_Manager::instance()->deinit();
		
		Font_Manager::instance()->deinit();
		
		Resource_Factory::instance()->deinit();
		
		Screen::instance()->deinit();
		
		SDL_Quit();
	
	}	
		

	int main(int argc, char* argv[])
	{
				
		bool disable_frame_limiter = false;
		
		bool using_another_map = false;
		
		bool disable_music = false;
		
		bool print_help = false;
		
		Uint32 frame_skip = 0;
		
		CommandlineConfiguration* cmdconf = new CommandlineConfiguration(argc, argv);
		
		if(cmdconf->get_bool(std::string("cmd"), std::string("help"), print_help))
		{
			printf("Epiphany 0.8.0\n");
			printf("Options:\n");
			printf("\t--help\t\t\t\tprint this help\n");
			printf("\t--frame-skip <n>\t\tskip <n> frames\n");
			printf("\t--disable-frame-limiter\t\tdisable frame limiter\n");
			printf("\t--map <map_path>\t\tplay <map_path> as level\n");
			printf("\t--disable-music\t\tDon't play music\n");
			//printf("\t--disable-sound\t\tDon't play sounds\n");
			printf("\t--virtual-screen\t\tUse a double buffer when drawing (experimental)");
			return 0;
			
		}
		
		init_modules();	

		std::string map_name; 
		
		using_another_map = cmdconf->get_string(std::string("cmd"), std::string("map"), map_name);
			
		
		
		cmdconf->get_bool(std::string("cmd"), std::string("disable-frame-limiter"), disable_frame_limiter);
			
		if(cmdconf->get_int(std::string("cmd"), std::string("frame-skip"), frame_skip) == false)
		{
			frame_skip = 1;
		}
		
		cmdconf->get_bool(std::string("cmd"), std::string("disable-music"), disable_music);
		
		if(disable_music == true)
		{
			Music_Manager::instance()->disable_music();
		}
		
		Game* game = Game::instance();
		
		game->set_frame_skip(frame_skip);
		
		if(disable_frame_limiter == true)
		{
			game->set_frame_limiter_enabled(false);
		}
		
		if(using_another_map == true)
		{
			printf("Map name: %s\n", map_name.c_str());
			
			game->play_level(map_name.c_str());
		}
		else
		{
			game->setup();
			Uint32 current_frame_time=SDL_GetTicks();
			Uint32 past_frame_time = SDL_GetTicks();
			Sint32 buffer_frame_time = 0;
			while(1){
				current_frame_time=SDL_GetTicks();
				game->update(current_frame_time-past_frame_time);
				buffer_frame_time = 266-(SDL_GetTicks()-current_frame_time);
				if(buffer_frame_time >0)
				{
					DEBOUT("Sleeping for: "<<buffer_frame_time<<"\n");
					SDL_Delay(buffer_frame_time);
				}
				past_frame_time = current_frame_time;
			}
		}
		
		DEBOUT("Exiting game::go().\n");
			
	
		deinit_modules();
		
		delete game;

		
		DEBOUT("\tExiting.\n");
		return 0;
	
	}
	
	

