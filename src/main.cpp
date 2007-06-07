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
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "dephine.h"
#include "game.h"



class Epiphany_App : public CL_ClanApplication
{
	//class Epiphany_App: contiene tutti i membri necessari all'applicazione
	//come main() e get_title()
	
	char* get_title()
	{
		
		return PACKAGE;
	
	}

	void init_modules()
	{
	
		CL_SetupCore::init();
		
		CL_SetupDisplay::init();
	
		CL_SetupSound::init();

	}

	int main(int, char**)
	{
			
		init_modules();	
		
	
	//	DEBOUT("Calling CL_Display::set_videomode\n");
		try
		{
			Game* game = Game::instance();
		
			game->go();
			DEBOUT("Exiting game::go().\n");
		}
		catch(Common_Ex ex)
		{
			std::cout<<ex.get_message();
		}		
		deinit_modules();
		
		DEBOUT("\tExiting.\n");
		return 0;
	
	}
	
	void deinit_modules()
	{

		CL_SetupSound::deinit();

		CL_SetupDisplay::deinit();		
	
		CL_SetupCore::deinit();
	
	}	
	

	

}app;

