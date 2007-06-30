/***************************************************************************
                          main.cpp  -  description
                             -------------------
    begin                : Wed Aug 15 2001
    copyright            : (C) 2001 by Giuseppe "Quobod" D'Aquì
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
#include <SDL/SDL.h>
#include "surface_manager.h"
#include "resource_factory.h"
#include "music_manager.h"
#include "sfx.h"
#include "input.h"
#include "fonts/font_manager.h"
#include "game.h"
#include "screen.h"
#include "cmdline.h"



	const char* get_title()
	{
		
		return PACKAGE;
	
	}

	void init_modules()
	{
	
		SDL_Init ( SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER );

		Input::instance()->init();
		
		Screen::instance();
		
		Resource_Factory::instance();
		
		Surface_Manager::instance();
		
		Sample_Manager::instance();
		
		Music_Manager::instance();
		
		Font_Manager::instance();
		
		SDL_WM_SetCaption(get_title(), NULL);
	
	}
	
	void deinit_modules()
	{
		
		Surface_Manager::instance()->deinit();
		
		Music_Manager::instance()->deinit();
		
		Sample_Manager::instance()->deinit();
		
		Font_Manager::instance()->deinit();
		
		Resource_Factory::instance()->deinit();
		
		SDL_Quit();
	
	}	
		

	int main(int argc, char* argv[])
	{
				
		bool disable_frame_limiter = false;
		
		bool using_another_map = false;
		
		bool print_help = false;
		
		Uint32 frame_skip = 0;
		
		cmdl::CmdLine C;
		
		C.Init( --argc, ++argv); 

		if(C.GetSingleValue("--help", print_help))
		{
			printf("Epiphany 0.7.0\n");
			printf("Options:\n");
			printf("\t--help\t\t\t\tprint this help\n");
			printf("\t--frame-skip <n>\t\tskip <n> frames\n");
			printf("\t--disable-frame-limiter\t\tdisable frame limiter\n");
			return 0;
			
		}
		
		init_modules();	

		char* map_name= new char[255]; 
		
		using_another_map = C.GetSingleValue("--map", map_name);
			
		
		
		C.GetSingleValue("--disable-frame-limiter", disable_frame_limiter);
			
		if(C.GetSingleValue("--frame-skip", frame_skip) == false)
		{
			frame_skip = 0;
		}
			
		C.Done();			

		Game* game = Game::instance();
		
		game->set_frame_skip(frame_skip);
		
		if(disable_frame_limiter == true)
		{
			game->set_frame_limiter_enabled(false);
		}
		
		if(using_another_map == true)
		{
			printf("Map name: %s\n", map_name);
			
			game->play_level(map_name);
		}
		else
		{
			game->go();
		}
		
		DEBOUT("Exiting game::go().\n");
			
	
		deinit_modules();
		
		delete game;
		delete map_name;
		
		DEBOUT("\tExiting.\n");
		return 0;
	
	}
	
	

