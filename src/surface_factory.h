#ifndef SURFACE_FACTORY_H_
#define SURFACE_FACTORY_H_

#include "resource_factory.h"

class Surface;


class Surface_Factory
{
private:
	Resource_Factory* m_res_factory;
public:
	enum Surface_Type{	SRF_UNKNOWN=0,
									SRF_PLAYER=1,
									SRF_GRASS=2,
									SRF_STEEL=3,
									SRF_EMERALD=4,
									SRF_BOULDER=5,
									SRF_SAPPHIRE=6,
									SRF_EXIT=7,
									SRF_EXPLOSION=8,
									SRF_DOOR_RED=9,
									SRF_DOOR_BLUE=10,
									SRF_DOOR_GREEN=11,
									SRF_DOOR_YELLOW=12,
									SRF_KEY_RED=13,
									SRF_KEY_BLUE=14,
									SRF_KEY_GREEN=15,
									SRF_KEY_YELLOW=16,
									SRF_FLINTSTONE=17,
									SRF_PEPERON=18,
									SRF_BRICK=19,
									SRF_WOOD=20,
									SRF_TOMATO=21,
									SRF_MENU_SELECTOR=22,
									SRF_MENU_BACKGROUND=23
									};
									
	Surface* create_surface(Surface_Type type);
	
	//void set_resource_factory(Resource_Factory* res_factory){m_res_factory=res_factory;};

// begin Singleton stuff

private:

	static Surface_Factory* _instance;

protected:

	Surface_Factory(){};

public:

	static Surface_Factory* instance();

// end Singleton stuff
	
	
};


#endif /*SURFACE_FACTORY_H_*/
