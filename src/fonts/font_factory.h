/***************************************************************************
                          font_factory.h  -  description
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
 
#ifndef FONT_FACTORY_H_
#define FONT_FACTORY_H_

#include "resource_factory.h"

class Font;



class Font_Factory
{
private:

	//Resource_Factory* m_res_factory;
	
public:

	enum Font_Type
	{
		MENU_FONT,
		GAME_FONT,
		CREDITS_FONT,
		TIME_FONT
	};


	Font* create_font(Font_Type type);

	//void set_resource_factory(Resource_Factory* res_factory){m_res_factory=res_factory;};

// begin Singleton stuff

private:

	static Font_Factory* _instance;

protected:

	Font_Factory(){};

public:

	static Font_Factory* instance();

// end Singleton stuff

};

#endif /*FONT_FACTORY_H_*/
