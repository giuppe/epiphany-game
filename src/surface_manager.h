#ifndef SURFACE_MANAGER_H_
#define SURFACE_MANAGER_H_

#include "dephine.h"
#include "surface.h"






#include <vector>


									

typedef Uint32 Surface_Handle;

class Surface_Manager
{
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
									SRF_MENU_BACKGROUND=23,
									SRF_KEY_RED_THUMB=24,
									SRF_KEY_BLUE_THUMB=25,
									SRF_KEY_GREEN_THUMB=26,
									SRF_KEY_YELLOW_THUMB=27,
									SRF_MENU_BACK_TILE,
									SRF_MENU_TITLE
									};
private:
	bool m_is_initialized;
	
    std::vector <Surface*> m_surfaces;
    
    void add_surface(Surface_Handle handle, Surface* surface);

    Surface_Handle load_surface(const char* path);
    
    Surface* create_surface(Surface_Manager::Surface_Type type);
    
    
public:

	void init();
	
    Surface* get_surface(Surface_Handle handle);

    // Since all surfaces in game should be inited and flushed by Surface_Manager
    // We do not support loading images by others
	

    // this should free all surfaces
    void deinit();


    // begin Singleton stuff

private:

    static Surface_Manager* _instance;

protected:

    Surface_Manager():m_is_initialized(false){};

public:

    static Surface_Manager* instance();

// end Singleton stuff

};

#endif /*SURFACE_MANAGER_H_*/
