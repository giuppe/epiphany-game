/***************************************************************************
                          resource_factory.cpp  -  description
                             -------------------
    begin                : Jun 13 2007
    copyright            : (C) 2007 by Giuseppe D'Aqui'
    email                : kumber@tiscalinet.it
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License, Version 2,      *
 *   as published by the Free Software Foundation.                         *
 *                                                                         *
 ***************************************************************************/

#include "resource_factory.h"
#include "dephine.h"
#include <cstdio>
#include <cassert>



void Resource_Factory::init()
{
	//portability "quick hack" :)
	#ifdef _WIN32
	m_resource_path=".";
	#else
	m_resource_path=RESOURCE_PATH;
	#endif
	DEBWARN("Resource_path: "<<m_resource_path<<"\n");

	FILE * pFile;
	
	std::string res_path_string(m_resource_path);
	
	
  	pFile = fopen ((res_path_string+"/epiphany.scr").c_str(),"r");
 	 if (pFile==NULL)
  	{
   		DEBWARN("Warning: "<<res_path_string<<" not found.\n");
		res_path_string="./data";
		pFile = fopen ((res_path_string+"/epiphany.scr").c_str(),"r");
 	 	if (pFile==NULL)
  		{
   			DEBWARN("Warning: "<<res_path_string<<" not found.\n");
			res_path_string="../data";
			pFile = fopen ((res_path_string+"/epiphany.scr").c_str(),"r");
 	 		if (pFile==NULL)
  			{
   				DEBWARN("Warning: "<<res_path_string<<" not found.\n");
				assert(!"Error: epiphany.scr not found.\n");
  			}
  		}
  	}
  	
  	if(pFile!=NULL)
  	{
  		fclose(pFile);
  	}
  	else
  	{
  		assert(!"Error: sprites.scr not found.\n");
  	}
  	
  	m_resource_path = res_path_string.c_str();

	DEBOUT("Using "<<m_resource_path<<"/epiphany.scr"<<" as resource script.\n");
	
	char* line = new char[1024];
	
	FILE* res_file = fopen((res_path_string+"/epiphany.scr").c_str(), "r");
	
	if(res_file != NULL)
	{
		fgets(line, 1024, res_file);
		char* action = new char[255];
		sscanf(line, "%s", action);
		if(strcmp(action, "sprite")==0){
			
			char* sprite_name = new char[255];
			char* sprite_path = new char[512];
			sscanf(line,"%s %s %s", action, sprite_name, sprite_path);
			DEBOUT("Found sprite definition: "<<sprite_name<<" in "<<sprite_path);
			//TODO: do something useful... like loading the sprite
			delete[] sprite_name;
			delete[] sprite_path;
		}
		else if(strcmp(action, "sound")==0){
			DEBOUT("Found sound definition");
			char* sound_name = new char[255];
			char* sound_path = new char[512];
			sscanf(line,"%s %s %s", action, sound_name, sound_path);
			//TODO: do something useful... like loading the sound
			delete[] sound_name;
			delete[] sound_path;
		}
		delete[] action;
	}
	delete[] line;
	
	fclose(res_file);
}

void Resource_Factory::deinit()
{
	
}

// begin Singleton stuff

Resource_Factory* Resource_Factory::_instance = 0;

Resource_Factory* Resource_Factory::instance()
{
	if (_instance == 0)
	{
		_instance = new Resource_Factory();
		_instance->init();
	}
	return _instance;
}

//end Singleton stuff
