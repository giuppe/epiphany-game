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


class Resourcecomp_App : public CL_ClanApplication
{
		
	char* get_title()
	{
		
		return "Epiphany rescomp0.2.2 ";
	
	}

	void init_modules()
	{
	
		CL_SetupCore::init();
		
		CL_SetupDisplay::init();

	}

	int main(int, char**)
	{
			

		init_modules();	


		CL_DatafileCompiler::write("./sprites.scr", "./sprites.dat");	
	
		deinit_modules();
		
		DEBOUT("\tExiting.\n");
		return 0;
	
	}
	
	void deinit_modules()
	{
		
		CL_SetupDisplay::deinit();		
	
		CL_SetupCore::deinit();
	
	}	
	

	

}app;
