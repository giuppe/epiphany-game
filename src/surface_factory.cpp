
#include "surface_factory.h"
#include "surface.h"
#include "game.h"
#include <cassert>
#include <cstring>



Surface* Surface_Factory::create_surface(Surface_Type type)
{
	
	
	std::string surface_path(Resource_Factory::instance()->get_resource_path());
	
	surface_path+= "/gfx/";
	
	Surface* surface = new Surface();
	
	Uint32 frame_size_x = 32;
	Uint32 frame_size_y = 32;
	
	
	switch(type)
	{
		case SRF_UNKNOWN:
			surface_path+= "unknown.bmp";
			break;
		case SRF_PLAYER:
			surface_path+= "player.bmp";
			break;
	case SRF_GRASS:
			surface_path+=  "grass.bmp";
			break;
	case SRF_STEEL:
			surface_path+= "steel.bmp";
			break;
	case SRF_EMERALD:
			surface_path+= "emerald.bmp";
			break;
	case SRF_BOULDER:
			surface_path+= "boulder.bmp";
		break;
	case SRF_SAPPHIRE:
			surface_path+= "sapphire.bmp";
				break;
	case SRF_EXIT:
			surface_path+= "exit.bmp";
			break;
	case SRF_EXPLOSION:
			surface_path+=  "explosion.bmp";
			break;
	case SRF_DOOR_RED:
			surface_path+=  "door_red.bmp";
			break;
	case SRF_DOOR_BLUE:
			surface_path+=  "door_blue.bmp";
		break;
	case SRF_DOOR_GREEN:
			surface_path+=  "door_green.bmp";
			break;
	case SRF_DOOR_YELLOW:
			surface_path+=  "door_yellow.bmp";
		break;
	case SRF_KEY_RED:
			surface_path+=  "key_red.bmp";
		break;
	case SRF_KEY_BLUE:
			surface_path+=  "key_blue.bmp";
		break;
	case SRF_KEY_GREEN:
			surface_path+=  "key_green.bmp";
		break;
	case SRF_KEY_YELLOW:
			surface_path+=  "key_yellow.bmp";
		break;
	case SRF_FLINTSTONE:
			surface_path+=  "flintstone.bmp";
			break;
	case SRF_PEPERON:
			surface_path+=  "peperon.bmp";
			break;
	case SRF_BRICK:
			surface_path+=  "brick.bmp";
			break;
	case SRF_WOOD:
			surface_path+=  "wood.bmp";
		break;
	case SRF_TOMATO:
			surface_path+=  "tomato.bmp";
		break;
	case SRF_MENU_SELECTOR:
	surface_path+=  "menu_selector.bmp";
		break;
	case SRF_MENU_BACKGROUND:
	surface_path+=  "menu_background.bmp";
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
	
	surface->init(temp, frame_size_x, frame_size_y);
	
	//SDL_FreeSurface(temp);
	
	return surface;
}

Surface_Factory* Surface_Factory::_instance = 0;

Surface_Factory* Surface_Factory::instance()
{
	if(_instance==0)
	{
		_instance=new Surface_Factory();
	}
	return _instance;
}
