#include "font_factory.h"
#include "font.h"
#include "resource_factory.h"
#include <cassert>

Font* Font_Factory::create_font(Font_Type type)
{
	Font* font = new Font();
	switch(type)
	{
		case GAME_FONT:
			font->init(CL_Font::load("Fonts/FNT_Game", m_res_factory));
			break;
		case TIME_FONT:
			font->init(CL_Font::load("Fonts/FNT_Time", m_res_factory));
			break;
		case CREDITS_FONT:
			font->init(CL_Font::load("Fonts/FNT_Credits", m_res_factory));
			break;
		case MENU_FONT:
			font->init(CL_Font::load("Fonts/FNT_Menu", m_res_factory));
			break;
		default:
			assert(0 && "Error: Selected non-existing font type.");
	}
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
