/***************************************************************************
                          spriteset.cpp  -  description
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
#include "spriteset.h"
#include "sprite.h"
#include "game.h"


Spriteset::Spriteset()
{
}




Spriteset::Spriteset(Game* game, CL_String spriteset)
{
  DEBOUT("Entering Spriteset ctor...\n");
	m_game=game;
	
	m_spriteset=spriteset;
	
	m_sprites.resize(256);
  DEBOUT("Exiting Spriteset ctor...\n");
}




Sprite& Spriteset::get_sprite(Entity_Type n_type)
{
	//TODO: Something to check if sprite exist
	return m_sprites[n_type];
	
}




void Spriteset::load_sprites()
{
	
	CL_ResourceManager* res_manag=m_game->get_resource_manager();
	
	CL_String surface_path=CL_String("Surfaces/")+m_spriteset+CL_String("_");

	m_sprites[UNKNOWN]=(Sprite(new CL_Surface(surface_path+"Unknown", res_manag)));
	
	m_sprites[PLAYER]=(Sprite(new CL_Surface(surface_path+"Player", res_manag)));

	m_sprites[GRASS]=(Sprite(new CL_Surface(surface_path+"Grass", res_manag)));
	
	m_sprites[STEEL]=(Sprite(new CL_Surface(surface_path+"Steel", res_manag)));
	
	m_sprites[EMERALD]=(Sprite(new CL_Surface(surface_path+"Emerald", res_manag)));
	
	m_sprites[BOULDER]=(Sprite(new CL_Surface(surface_path+"Boulder", res_manag)));

	m_sprites[SAPPHIRE]=(Sprite(new CL_Surface(surface_path+"Sapphire", res_manag)));
		
	m_sprites[EXIT]=(Sprite(new CL_Surface(surface_path+"Exit", res_manag)));
	
	m_sprites[EXPLOSION]=(Sprite(new CL_Surface(surface_path+"Explosion", res_manag)));
	
	m_sprites[DOOR]=(Sprite(new CL_Surface(surface_path+"Door", res_manag)));

	m_sprites[KEY]=(Sprite(new CL_Surface(surface_path+"Key", res_manag)));	

	m_sprites[FLINTSTONE]=(Sprite(new CL_Surface(surface_path+"Flintstone", res_manag)));	
	
	m_sprites[PEPERON]=(Sprite(new CL_Surface(surface_path+"Peperon", res_manag)));	
	
	m_sprites[BRICK]=(Sprite(new CL_Surface(surface_path+"Brick", res_manag)));
	
	m_sprites[WOOD]=(Sprite(new CL_Surface(surface_path+"Wood", res_manag)));

	m_sprites[TOMATO]=(Sprite(new CL_Surface(surface_path+"Tomato", res_manag)));
}
