#include "surface_manager.h"
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





Surface* Surface_Manager::create_surface(Surface_Manager::Surface_Type type)
{
	
	
	std::string surface_path(Resource_Factory::instance()->get_resource_path());
	
	surface_path+= "/gfx/";
	
	Surface* surface = new Surface();
	
	Uint32 frame_size_x = 32;
	Uint32 frame_size_y = 32;
	
	
	switch(type)
	{
		case Surface_Manager::SRF_UNKNOWN:
			surface_path+= "unknown.bmp";
			break;
		case Surface_Manager::SRF_PLAYER:
			surface_path+= "player.bmp";
			break;
	case Surface_Manager::SRF_GRASS:
			surface_path+=  "grass.bmp";
			break;
	case Surface_Manager::SRF_STEEL:
			surface_path+= "steel.bmp";
			break;
	case Surface_Manager::SRF_EMERALD:
			surface_path+= "emerald.bmp";
			break;
	case Surface_Manager::SRF_BOULDER:
			surface_path+= "boulder.bmp";
		break;
	case Surface_Manager::SRF_SAPPHIRE:
			surface_path+= "sapphire.bmp";
				break;
	case Surface_Manager::SRF_EXIT:
			surface_path+= "exit.bmp";
			break;
	case Surface_Manager::SRF_EXPLOSION:
			surface_path+=  "explosion.bmp";
			break;
	case Surface_Manager::SRF_DOOR_RED:
			surface_path+=  "door_red.bmp";
			break;
	case Surface_Manager::SRF_DOOR_BLUE:
			surface_path+=  "door_blue.bmp";
		break;
	case Surface_Manager::SRF_DOOR_GREEN:
			surface_path+=  "door_green.bmp";
			break;
	case Surface_Manager::SRF_DOOR_YELLOW:
			surface_path+=  "door_yellow.bmp";
		break;
	case Surface_Manager::SRF_KEY_RED:
			surface_path+=  "key_red.bmp";
		break;
	case Surface_Manager::SRF_KEY_BLUE:
			surface_path+=  "key_blue.bmp";
		break;
	case Surface_Manager::SRF_KEY_GREEN:
			surface_path+=  "key_green.bmp";
		break;
	case Surface_Manager::SRF_KEY_YELLOW:
			surface_path+=  "key_yellow.bmp";
		break;
	case Surface_Manager::SRF_FLINTSTONE:
			surface_path+=  "flintstone.bmp";
			break;
	case Surface_Manager::SRF_PEPERON:
			surface_path+=  "peperon.bmp";
			break;
	case Surface_Manager::SRF_BRICK:
			surface_path+=  "brick.bmp";
			break;
	case Surface_Manager::SRF_WOOD:
			surface_path+=  "wood.bmp";
		break;
	case Surface_Manager::SRF_TOMATO:
			surface_path+=  "tomato.bmp";
		break;
	case Surface_Manager::SRF_MENU_SELECTOR:
		surface_path+=  "menu_selector.bmp";
		break;
	case Surface_Manager::SRF_MENU_BACKGROUND:
		surface_path+=  "menu_background.bmp";
		break;
	case Surface_Manager::SRF_KEY_RED_THUMB:
		surface_path+=  "key_red_thumb.bmp";
		break;
	case Surface_Manager::SRF_KEY_BLUE_THUMB:
		surface_path+=  "key_blue_thumb.bmp";
		break;
	case Surface_Manager::SRF_KEY_GREEN_THUMB:
		surface_path+=  "key_green_thumb.bmp";
		break;
	case Surface_Manager::SRF_KEY_YELLOW_THUMB:
		surface_path+=  "key_yellow_thumb.bmp";
		break;
	case Surface_Manager::SRF_MENU_BACK_TILE:
		surface_path+=  "menu_back_tile.bmp";
		break;
	case Surface_Manager::SRF_MENU_TITLE:
		surface_path+=  "menu_title.bmp";
		break;
	default:
		assert(!"Trying to access a missing surface.");
	}
	
	SDL_Surface* temp = SDL_LoadBMP(surface_path.c_str());
	
	if(temp==NULL)
	{
		DEBOUT("Error: "<<surface_path<<" is not a surface bitmap.\n");
		assert(0);
	}
	//Set pink as transparent color
	SDL_SetColorKey(temp, SDL_SRCCOLORKEY, SDL_MapRGB(temp->format, 255, 0, 255));
	
	surface->init(temp, frame_size_x, frame_size_y);
	
	//SDL_FreeSurface(temp);
	
	return surface;
}





void Surface_Manager::init()
{
	assert(!m_is_initialized&&"Error: attempting to reload surfaces.");
	
	m_is_initialized = true;
	
	DEBOUT("Loading all surfaces...");
		
		
	add_surface(SRF_UNKNOWN, this->create_surface(SRF_UNKNOWN));
	
	add_surface(SRF_PLAYER, this->create_surface(SRF_PLAYER));

	add_surface(SRF_GRASS, this->create_surface(SRF_GRASS));
	
	add_surface(SRF_STEEL, this->create_surface(SRF_STEEL));
	
	add_surface(SRF_EMERALD, this->create_surface(SRF_EMERALD));
	
	add_surface(SRF_BOULDER, this->create_surface(SRF_BOULDER));

	add_surface(SRF_SAPPHIRE, this->create_surface(SRF_SAPPHIRE));
		
	add_surface(SRF_EXIT, this->create_surface(SRF_EXIT));
	
	add_surface(SRF_EXPLOSION, this->create_surface(SRF_EXPLOSION));
	
	add_surface(SRF_DOOR_RED, this->create_surface(SRF_DOOR_RED));
	
	add_surface(SRF_DOOR_BLUE, this->create_surface(SRF_DOOR_BLUE));

	add_surface(SRF_DOOR_GREEN, this->create_surface(SRF_DOOR_GREEN));
	
	add_surface(SRF_DOOR_YELLOW, this->create_surface(SRF_DOOR_YELLOW));

	add_surface(SRF_KEY_RED, this->create_surface(SRF_KEY_RED));	

	add_surface(SRF_KEY_BLUE, this->create_surface(SRF_KEY_BLUE));	

	add_surface(SRF_KEY_GREEN, this->create_surface(SRF_KEY_GREEN));	

	add_surface(SRF_KEY_YELLOW, this->create_surface(SRF_KEY_YELLOW));	

	add_surface(SRF_FLINTSTONE, this->create_surface(SRF_FLINTSTONE));	
	
	add_surface(SRF_PEPERON, this->create_surface(SRF_PEPERON));	
	
	add_surface(SRF_BRICK, this->create_surface(SRF_BRICK));
	
	add_surface(SRF_WOOD, this->create_surface(SRF_WOOD));

	add_surface(SRF_TOMATO, this->create_surface(SRF_TOMATO));
	
	add_surface(SRF_MENU_BACKGROUND, this->create_surface(SRF_MENU_BACKGROUND));
	
	add_surface(SRF_MENU_SELECTOR, this->create_surface(SRF_MENU_SELECTOR));
	
	add_surface(SRF_KEY_RED_THUMB, this->create_surface(SRF_KEY_RED_THUMB));	

	add_surface(SRF_KEY_BLUE_THUMB, this->create_surface(SRF_KEY_BLUE_THUMB));	

	add_surface(SRF_KEY_GREEN_THUMB, this->create_surface(SRF_KEY_GREEN_THUMB));	

	add_surface(SRF_KEY_YELLOW_THUMB, this->create_surface(SRF_KEY_YELLOW_THUMB));
	
	add_surface(SRF_MENU_BACK_TILE, this->create_surface(SRF_MENU_BACK_TILE));	
	
	add_surface(SRF_MENU_TITLE, this->create_surface(SRF_MENU_TITLE));	
}

void Surface_Manager::deinit()
{
    DEBOUT("\nFlushing all surfaces... ");
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
