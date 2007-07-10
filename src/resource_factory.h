/***************************************************************************
                          resource_factory.h  -  description
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

#ifndef RESOURCE_MANAGER_H_
#define RESOURCE_MANAGER_H_

#include "dephine.h"
#include "resource.h"
#include <string>
//typedef CL_ResourceManager Resource_Factory;



class Resource_Factory
{
protected:
	
	std::string m_resource_path;
public:
	enum Resource_Type{
		RES_SURFACE,
		RES_FONT,
		RES_SOUND,
		RES_MUSIC
		};
		
	//virtual Resource* create_resource(Resource_Type type, const char* resource_id) = 0;
		
	void init();
	
	void deinit();	
	
	std::string get_resource_path(){return m_resource_path;};
	
	
	
	// begin Singleton stuff

private:

    static Resource_Factory* _instance;

protected:

	Resource_Factory(){};

public:

    static Resource_Factory* instance();

// end Singleton stuff
		
};


#endif /*RESOURCE_MANAGER_H_*/
