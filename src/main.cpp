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
#include "fonts/font_manager.h"
#include "game.h"
#include "input.h"
#include "screen.h"



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
	
	//	DEBOUT("Calling CL_Display::set_videomode\n");
		Game* game = Game::instance();
	
			game->go();
			DEBOUT("Exiting game::go().\n");
			
	
		deinit_modules();
		
		delete game;
		
		DEBOUT("\tExiting.\n");
		return 0;
	
	}
	
	

