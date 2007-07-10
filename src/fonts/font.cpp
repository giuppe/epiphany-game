/***************************************************************************
                          font.cpp  -  description
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

#include "font.h"
#include "SFont.h"
#include "screen.h"
#include "epiconfig.h"
#include <cassert>

void Font::write(Sint32 x, Sint32 y, const char* text)
{
	assert(m_initialized && "Error: using a non initialized font.");	
	SFont_Write(Screen::instance()->get_screen(), m_font, x, y, text);
}

void Font::write_center(Sint32 y, const char* text)
{
	assert(m_initialized && "Error: using a non initialized font.");
	SFont_WriteCenter(Screen::instance()->get_screen(), m_font, y, text);
}

void Font::init(SFont_Font* font)
{
	if(font!=NULL)
	{
		m_font = font;
		m_initialized = true;
	}
	else
	{
		DEBOUT("Warning: trying to initialize a font with NULL\n");
	}
}


