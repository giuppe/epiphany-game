/***************************************************************************
                          entity_grass.cpp  -  description
                             -------------------
    begin                : Mon Oct 1 2001
    copyright            : (C) 2001 by Giuseppe D'Aqu�
    email                : kumber@tiscalinet.it
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License, Version 2, as published by  *
 *   the Free Software Foundation.                                   *
 *                                                                         *
 ***************************************************************************/

#include "dephine.h"
#include "sprite.h"
#include "entity.h"
#include "entity_grass.h"

Entity_Grass::Entity_Grass(Level* level, Uint32 x, Uint32 y)
{
	current_level=level;
	m_position_x=x;
	m_position_y=y;
	m_type=GRASS;
	Surface_Manager* surf_man = Surface_Manager::instance();
	m_sprite.init(surf_man->get_surface(Surface_Manager::SRF_GRASS));
	m_state=ST_STOP;
	m_sprite.set_state(SP_STOP);
	m_exists=true;
	
		
}



bool Entity_Grass::player_pressing_up(Entity_Handle down_entity)
{

	Sample_Manager::instance()->play(SFX_GRASS_EAT);
	m_state=ST_DISAPPEARING;
	kill();
	return true;
}


bool Entity_Grass::player_pressing_down(Entity_Handle up_entity)
{

	//DEBOUT("Entering Entity_Grass::pass_on_me()\n");
	Sample_Manager::instance()->play(SFX_GRASS_EAT);
	m_state=ST_DISAPPEARING;
	kill();
	return true;
}


bool Entity_Grass::player_pressing_right(Entity_Handle left_entity)
{

	//DEBOUT("Entering Entity_Grass::pass_on_me()\n");
	Sample_Manager::instance()->play(SFX_GRASS_EAT);
	m_state=ST_DISAPPEARING;
	kill();
	return true;
}


bool Entity_Grass::player_pressing_left(Entity_Handle right_entity)
{

	//DEBOUT("Entering Entity_Grass::pass_on_me()\n");
	Sample_Manager::instance()->play(SFX_GRASS_EAT);
	m_state=ST_DISAPPEARING;
	kill();
	return true;
}

bool Entity_Grass::explode()
{
	kill();
	//m_exists=false;
	return true;
}

