/***************************************************************************
                          spriteset.h  -  description
                             -------------------
    begin                : Mon Aug 12 2002
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
#include "entity_type.h"
#include "sprite.h"

#include <vector>

#ifndef SPRITESET_H
#define SPRITESET_H
class Game;


class Spriteset
{
private:
	
	std::vector <Sprite> m_sprites;
	
	Game* m_game;
	
	CL_String m_spriteset;
	
public:
	Spriteset();
	
	Spriteset(Game* game, CL_String spriteset);
	
	Sprite& get_sprite(Entity_Type n_sprite);
	
	void load_sprites();
	
};

#endif //SPRITESET_H

