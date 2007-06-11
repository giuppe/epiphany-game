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
#include "surface_manager.h"
#include "surface_factory.h"

Spriteset::Spriteset()
{
}




Spriteset::Spriteset(const char* spriteset_name)
{
  DEBOUT("Entering Spriteset ctor...\n");

	
	m_spriteset_name=spriteset_name;
	
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
	
	
	Surface_Manager* surf_man = Surface_Manager::instance();

	m_sprites[UNKNOWN]=(Sprite(surf_man->get_surface(Surface_Factory::SRF_UNKNOWN)));
	
	m_sprites[PLAYER]=(Sprite(surf_man->get_surface(Surface_Factory::SRF_PLAYER)));

	m_sprites[GRASS]=(Sprite(surf_man->get_surface(Surface_Factory::SRF_GRASS)));
	
	m_sprites[STEEL]=(Sprite(surf_man->get_surface(Surface_Factory::SRF_STEEL)));
	
	m_sprites[EMERALD]=(Sprite(surf_man->get_surface(Surface_Factory::SRF_EMERALD)));
	
	m_sprites[BOULDER]=(Sprite(surf_man->get_surface(Surface_Factory::SRF_BOULDER)));

	m_sprites[SAPPHIRE]=(Sprite(surf_man->get_surface(Surface_Factory::SRF_SAPPHIRE)));
		
	m_sprites[EXIT]=(Sprite(surf_man->get_surface(Surface_Factory::SRF_EXIT)));
	
	m_sprites[EXPLOSION]=(Sprite(surf_man->get_surface(Surface_Factory::SRF_EXPLOSION)));
	
	m_sprites[DOOR_RED]=(Sprite(surf_man->get_surface(Surface_Factory::SRF_DOOR_RED)));

	m_sprites[DOOR_BLUE]=(Sprite(surf_man->get_surface(Surface_Factory::SRF_DOOR_BLUE)));

	m_sprites[DOOR_GREEN]=(Sprite(surf_man->get_surface(Surface_Factory::SRF_DOOR_GREEN)));

	m_sprites[DOOR_YELLOW]=(Sprite(surf_man->get_surface(Surface_Factory::SRF_DOOR_GREEN)));

	//m_sprites[KEY]=(Sprite(surf_man->get_surface(KEY)));	

	m_sprites[KEY_RED]=(Sprite(surf_man->get_surface(Surface_Factory::SRF_KEY_RED)));

	m_sprites[KEY_BLUE]=(Sprite(surf_man->get_surface(Surface_Factory::SRF_KEY_BLUE)));

	//m_sprites[KEY_BLUE].set_state(SP_UP);
	
	m_sprites[KEY_GREEN]=(Sprite(surf_man->get_surface(Surface_Factory::SRF_KEY_GREEN)));

	//m_sprites[KEY_GREEN].set_state(SP_RIGHT);
	
	m_sprites[KEY_YELLOW]=(Sprite(surf_man->get_surface(Surface_Factory::SRF_KEY_YELLOW)));

	//m_sprites[KEY_YELLOW].set_state(SP_DOWN);
	

	m_sprites[FLINTSTONE]=(Sprite(surf_man->get_surface(Surface_Factory::SRF_FLINTSTONE)));	
	
	m_sprites[PEPERON]=(Sprite(surf_man->get_surface(Surface_Factory::SRF_PEPERON)));	
	
	m_sprites[BRICK]=(Sprite(surf_man->get_surface(Surface_Factory::SRF_BRICK)));
	
	m_sprites[WOOD]=(Sprite(surf_man->get_surface(Surface_Factory::SRF_WOOD)));

	m_sprites[TOMATO]=(Sprite(surf_man->get_surface(Surface_Factory::SRF_TOMATO)));
}
