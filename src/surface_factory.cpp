
#include "surface_factory.h"
#include "surface.h"
#include "game.h"
#include <cassert>



Surface* Surface_Factory::create_surface(Surface_Type type)
{
	
	CL_String surface_path=CL_String("Surfaces/SPT_");
	
	Resource_Factory* m_res_factory = Game::instance()->get_resource_manager();
	
	Surface* surface = new Surface();
	
	switch(type)
	{
		case SRF_UNKNOWN:
			surface->init(new CL_Surface(surface_path+"Unknown", m_res_factory));
			break;
		case SRF_PLAYER:
			surface->init(new CL_Surface(surface_path+"Player", m_res_factory));
			break;
	case SRF_GRASS:
			surface->init(new CL_Surface(surface_path+"Grass", m_res_factory));
			break;
	case SRF_STEEL:
			surface->init(new CL_Surface(surface_path+"Steel", m_res_factory));
			break;
	case SRF_EMERALD:
			surface->init(new CL_Surface(surface_path+"Emerald", m_res_factory));
			break;
	case SRF_BOULDER:
			surface->init(new CL_Surface(surface_path+"Boulder", m_res_factory));
		break;
	case SRF_SAPPHIRE:
			surface->init(new CL_Surface(surface_path+"Sapphire", m_res_factory));
				break;
	case SRF_EXIT:
			surface->init(new CL_Surface(surface_path+"Exit", m_res_factory));
			break;
	case SRF_EXPLOSION:
			surface->init(new CL_Surface(surface_path+"Explosion", m_res_factory));
			break;
	case SRF_DOOR_RED:
			surface->init(new CL_Surface(surface_path+"Door_Red", m_res_factory));
			break;
	case SRF_DOOR_BLUE:
			surface->init(new CL_Surface(surface_path+"Door_Blue", m_res_factory));
		break;
	case SRF_DOOR_GREEN:
			surface->init(new CL_Surface(surface_path+"Door_Green", m_res_factory));
			break;
	case SRF_DOOR_YELLOW:
			surface->init(new CL_Surface(surface_path+"Door_Yellow", m_res_factory));
		break;
	case SRF_KEY_RED:
			surface->init(new CL_Surface(surface_path+"Key_Red", m_res_factory));	
		break;
	case SRF_KEY_BLUE:
			surface->init(new CL_Surface(surface_path+"Key_Blue", m_res_factory));	
		break;
	case SRF_KEY_GREEN:
			surface->init(new CL_Surface(surface_path+"Key_Green", m_res_factory));	
		break;
	case SRF_KEY_YELLOW:
			surface->init(new CL_Surface(surface_path+"Key_Yellow", m_res_factory));	
		break;

	case SRF_FLINTSTONE:
			surface->init(new CL_Surface(surface_path+"Flintstone", m_res_factory));	
			break;
	case SRF_PEPERON:
			surface->init(new CL_Surface(surface_path+"Peperon", m_res_factory));	
			break;
	case SRF_BRICK:
			surface->init(new CL_Surface(surface_path+"Brick", m_res_factory));
			break;
	case SRF_WOOD:
			surface->init(new CL_Surface(surface_path+"Wood", m_res_factory));
		break;
	case SRF_TOMATO:
			surface->init(new CL_Surface(surface_path+"Tomato", m_res_factory));
		break;
	case SRF_MENU_SELECTOR:
	surface->init(new CL_Surface("Surfaces/MNU_Selector", m_res_factory));
		break;
	case SRF_MENU_BACKGROUND:
	surface->init(new CL_Surface("Surfaces/MNU_Background", m_res_factory));
		break;
	default:
		assert(!"Trying to access a missing surface.");
	}
	
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
