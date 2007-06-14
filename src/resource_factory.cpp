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
	m_resource_path= RESOURCE_PATH;
	#endif
	DEBOUT("Resource_path: "<<m_resource_path<<"\n");

	FILE * pFile;
	
	std::string res_path_string(m_resource_path);
	
	
  	pFile = fopen ((res_path_string+"/epiphany.scr").c_str(),"r");
 	 if (pFile==NULL)
  	{
   		DEBWARN("Warning: %s not found.\n", res_path_string);
		res_path_string="./data";
		pFile = fopen ((res_path_string+"/epiphany.scr").c_str(),"r");
 	 	if (pFile==NULL)
  		{
   			DEBWARN("Warning: %s not found.\n", res_path_string);
			res_path_string="../data";
			pFile = fopen ((res_path_string+"/epiphany.scr").c_str(),"r");
 	 		if (pFile==NULL)
  			{
   				DEBWARN("Warning: %s not found.\n", res_path_string);
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
