/***************************************************************************
                          font_manager.h  -  description
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
 
#ifndef FONT_MANAGER_H_
#define FONT_MANAGER_H_
#include "dephine.h"
#include "surface_manager.h"
#include "font.h"
#include <vector>

typedef Uint32 Font_Handle;

class Font_Manager
{
private:

    std::vector<Font*> m_fonts;

public:

	void init();
 
	Font_Handle add_font(Font* font);

	Font* get_font(Font_Handle);
	
	void deinit();

// begin Singleton stuff

private:

    static Font_Manager* _instance;

protected:

    Font_Manager(){};

public:

    static Font_Manager* instance();

// end Singleton stuff

};


#endif /*FONT_MANAGER_H_*/
