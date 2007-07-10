/***************************************************************************
                          font_factory.cpp  -  description
                             -------------------
    begin                : Jun 13 2007
    copyright            : (C) 2007 by Giuseppe D'Aqui'
    email                : kumber@tiscalinet.it
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License, Version 2,      *
 *   as published by the Free Software Foundation.                         *
 *                                                                         *
 ***************************************************************************/

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
			m_res_factory += "/gfx/game_font.bmp";
			break;
		case TIME_FONT:
			m_res_factory += "/gfx/time_font.bmp";
			break;
		case CREDITS_FONT:
			m_res_factory += "/gfx/credits_font.bmp";
			break;
		case MENU_FONT:
			m_res_factory += "/gfx/menu_font.bmp";
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
