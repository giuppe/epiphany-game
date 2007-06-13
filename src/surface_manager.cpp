#include "surface_manager.h"
#include "surface_factory.h"
#include "surface.h"
#include "resource_factory.h"
#include <SDL/SDL.h>
#include <string>
#include "game.h"

#include <cassert>
/*
Surface_Handle Surface_Manager::load_surface(const char* path)
{
    Surface_Handle s_h = m_surfaces.size();
    
    //std::string res_path=Resource_Factory::instance()->get_resource_path();

    Surface* temp = new Surface();
    
    SDL_Surface temp2 = SDL_LoadBMP(path)
    
    temp->init();
                     
    m_surfaces.push_back(temp);
    
    return s_h;
}
*/

void Surface_Manager::add_surface(Surface_Handle handle, Surface* surface)
{
    //Surface_Handle s_h = m_surfaces.size();
                        
    m_surfaces[handle]=surface;

}

Surface* Surface_Manager::get_surface(Surface_Handle surface_handle)
{
    if(surface_handle<m_surfaces.size())
    {
        return m_surfaces[surface_handle];
    }
    assert(!"Error: Trying to access a non-initialized surface");
}

void Surface_Manager::init()
{
	DEBOUT("Loading all surfaces...");
	
	
	Surface_Factory* surf_factory = Surface_Factory::instance();
		
	add_surface(Surface_Factory::SRF_UNKNOWN, surf_factory->create_surface(Surface_Factory::SRF_UNKNOWN));
	
	add_surface(Surface_Factory::SRF_PLAYER, surf_factory->create_surface(Surface_Factory::SRF_PLAYER));

	add_surface(Surface_Factory::SRF_GRASS, surf_factory->create_surface(Surface_Factory::SRF_GRASS));
	
	add_surface(Surface_Factory::SRF_STEEL, surf_factory->create_surface(Surface_Factory::SRF_STEEL));
	
	add_surface(Surface_Factory::SRF_EMERALD, surf_factory->create_surface(Surface_Factory::SRF_EMERALD));
	
	add_surface(Surface_Factory::SRF_BOULDER, surf_factory->create_surface(Surface_Factory::SRF_BOULDER));

	add_surface(Surface_Factory::SRF_SAPPHIRE, surf_factory->create_surface(Surface_Factory::SRF_SAPPHIRE));
		
	add_surface(Surface_Factory::SRF_EXIT, surf_factory->create_surface(Surface_Factory::SRF_EXIT));
	
	add_surface(Surface_Factory::SRF_EXPLOSION, surf_factory->create_surface(Surface_Factory::SRF_EXPLOSION));
	
	add_surface(Surface_Factory::SRF_DOOR_RED, surf_factory->create_surface(Surface_Factory::SRF_DOOR_RED));
	
	add_surface(Surface_Factory::SRF_DOOR_BLUE, surf_factory->create_surface(Surface_Factory::SRF_DOOR_BLUE));

	add_surface(Surface_Factory::SRF_DOOR_GREEN, surf_factory->create_surface(Surface_Factory::SRF_DOOR_GREEN));
	
	add_surface(Surface_Factory::SRF_DOOR_YELLOW, surf_factory->create_surface(Surface_Factory::SRF_DOOR_YELLOW));

	add_surface(Surface_Factory::SRF_KEY_RED, surf_factory->create_surface(Surface_Factory::SRF_KEY_RED));	

	add_surface(Surface_Factory::SRF_KEY_BLUE, surf_factory->create_surface(Surface_Factory::SRF_KEY_BLUE));	

	add_surface(Surface_Factory::SRF_KEY_GREEN, surf_factory->create_surface(Surface_Factory::SRF_KEY_GREEN));	

	add_surface(Surface_Factory::SRF_KEY_YELLOW, surf_factory->create_surface(Surface_Factory::SRF_KEY_YELLOW));	


	add_surface(Surface_Factory::SRF_FLINTSTONE, surf_factory->create_surface(Surface_Factory::SRF_FLINTSTONE));	
	
	add_surface(Surface_Factory::SRF_PEPERON, surf_factory->create_surface(Surface_Factory::SRF_PEPERON));	
	
	add_surface(Surface_Factory::SRF_BRICK, surf_factory->create_surface(Surface_Factory::SRF_BRICK));
	
	add_surface(Surface_Factory::SRF_WOOD, surf_factory->create_surface(Surface_Factory::SRF_WOOD));

	add_surface(Surface_Factory::SRF_TOMATO, surf_factory->create_surface(Surface_Factory::SRF_TOMATO));
	
	add_surface(Surface_Factory::SRF_MENU_BACKGROUND, surf_factory->create_surface(Surface_Factory::SRF_MENU_BACKGROUND));
	
	add_surface(Surface_Factory::SRF_MENU_SELECTOR, surf_factory->create_surface(Surface_Factory::SRF_MENU_SELECTOR));
	
}

void Surface_Manager::deinit()
{
    DEBOUT("\n\tFlushing all surfaces... ");
    for(Uint32 i=0; i < m_surfaces.size(); i++)
    {
        delete m_surfaces[i];
    }

    DEBOUT("done.\n");
}

// begin Singleton stuff

Surface_Manager* Surface_Manager::_instance = 0;

Surface_Manager* Surface_Manager::instance()
{
	if (_instance == 0)
	{
		_instance = new Surface_Manager();
		//FIXME: this is for enabling random adding of surfaces
		_instance->m_surfaces.resize(40);
		_instance->init();
	}
	return _instance;
}

//end Singleton stuff
