/***************************************************************************
                          map_editor.h  -  description
                             -------------------
    begin                : Tue Aug 13 2002
    copyright            : (C) 2002 by Giuseppe D'Aqui'
    email                : kumber@tiscalinet.it
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "dephine.h"
#include "levelmap.h"

#ifndef MAP_EDITOR_H
#define MAP_EDITOR_H
class Game;

class Map_Editor
{
private:
	Game* m_game;
	
	Levelmap m_levelmap;

public:
	Map_Editor(Levelmap levelmap);
	void go();
};

#endif //MAP_EDITOR_H
