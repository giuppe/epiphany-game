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
		
		Font_Manager::instance();
		
		SDL_WM_SetCaption(get_title(), NULL);
	
	}
	
	void deinit_modules()
	{
		
		Surface_Manager::instance()->deinit();
		
		Sample_Manager::instance()->deinit();
		
		Font_Manager::instance()->deinit();
		
		Resource_Factory::instance()->deinit();
		
		SDL_Quit();
	
	}	
		

	int main(int argc, char* argv[])
	{
			
		init_modules();	
		
		bool disable_frame_limiter = false;
		
		bool using_another_map = false;
		
		Uint32 frame_skip = 0;
		
		// command line arguments manipulation
		cmdl::CmdLine C;
		
		C.Init( --argc, ++argv); 

		        // retrieve and print an integer set with option "--set-int"
		char* map_name= new char[255]; 
		using_another_map = C.GetSingleValue("--map", map_name);
			printf("Map name: %s\n", map_name);
		
			C.GetSingleValue("--disable-frame-limiter", disable_frame_limiter);
			
			if(C.GetSingleValue("--frame-skip", frame_skip) == false)
			{
				frame_skip = 0;
			}
			
			C.Done(); // check for unused options
			
			
			/*
        if (argc == 2) 
        {
			Game* game = Game::instance();
			game->play_level(argv[1]);
			return 0;
		}
		else if (argc > 2)
		{
			printf("Cannot supply more than one command line argument.\n");
			return 1;
		}
	*/

		Game* game = Game::instance();
		
		game->set_frame_skip(frame_skip);
		
		if(disable_frame_limiter == true)
		{
			game->set_frame_limiter_enabled(false);
		}
		
		if(using_another_map == true)
		{
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
	
	

