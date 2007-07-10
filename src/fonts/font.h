/***************************************************************************
                          font.h  -  description
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
 
#ifndef FONT_H_
#define FONT_H_

#include "dephine.h"
#include "resource.h"
#include "SFont.h"

class Font : public Resource
{
private:
	SFont_Font* m_font;
	bool m_initialized;
public:
	Font(): m_initialized(false){};
	~Font(){deinit();};
	void init(SFont_Font* font);
    void deinit(){if(m_initialized==true) SFont_FreeFont(m_font);};
    void write(Sint32 x, Sint32 y, const char* text);
    void write_center(Sint32 y, const char* text);
};
#endif /*FONT_H_*/
