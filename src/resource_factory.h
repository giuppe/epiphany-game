#ifndef RESOURCE_MANAGER_H_
#define RESOURCE_MANAGER_H_

#include "dephine.h"
#include "resource.h"

typedef CL_ResourceManager Resource_Factory;


/*
class Resource_Factory
{
protected:
	CL_ResourceManager m_res_manager;
public:
	enum Resource_Type{
		RES_SURFACE,
		RES_FONT,
		RES_SOUND,
		RES_MUSIC
		};
		
	//virtual Resource* create_resource(Resource_Type type, const char* resource_id) = 0;
		
	void init();
		
	const char* get_resource_path(Resource_Type type);
		
	// begin Singleton stuff

private:

    static Resource_Factory* _instance;

protected:

	Resource_Factory(){};

public:

    static Resource_Factory* instance();

// end Singleton stuff
		
};
*/

#endif /*RESOURCE_MANAGER_H_*/
