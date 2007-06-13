#include "font_factory.h"
#include "font.h"
#include "SFont.h"
#include "resource_factory.h"
#include <cassert>
#include <string>

Font* Font_Factory::create_font(Font_Type type)
{
	std::string m_res_factory(Resource_Factory::instance()->get_resource_path());
	
	Font* font = new Font();
	switch(type)
	{
		case GAME_FONT:
			m_res_factory += "/gfx/epifont.bmp";
			break;
		case TIME_FONT:
			m_res_factory += "/gfx/epifont.bmp";
			break;
		case CREDITS_FONT:
			m_res_factory += "/gfx/epifont.bmp";
			break;
		case MENU_FONT:
			m_res_factory += "/gfx/epifont.bmp";
			break;
		default:
			assert(!"Error: Selected non-existing font type.");
	}
	DEBOUT("Loading font: "<<m_res_factory<<"...\n");
	SDL_Surface* temp = SDL_LoadBMP(m_res_factory.c_str());
	if(temp!=NULL)
	{
		font->init(SFont_InitFont (temp));
	}
	else
	{
		DEBOUT("Error: "<<m_res_factory<<" is not a valid font.\n");
	}
	
	//SDL_FreeSurface(temp);
	
	return font;
}


Font_Factory* Font_Factory::_instance = 0;

Font_Factory* Font_Factory::instance()
{
	if(_instance==0)
	{
		_instance=new Font_Factory();
	}
	return _instance;
}
