/***************************************************************************
                          entity_key.cpp  -  description
                             -------------------
    begin                : Thu Apr 18 2002
    copyright            : (C) 2002 by Giuseppe D'Aqui'
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
#include "entity.h"
#include "entity_key.h"
#include <cassert>

Entity_Key::Entity_Key(Level* level, Uint32 x, Uint32 y, Uint32 id)
{
	current_level=level;
	m_position_x=x;
	m_position_y=y;
	m_type=KEY;
	Surface_Manager* surf_man = Surface_Manager::instance();
	
	m_key_id=id;	
	switch(m_key_id)
	{
	case 1:
		m_sprite=Sprite(surf_man->get_surface(Surface_Manager::SRF_KEY_RED));
		break;
	case 2:
		m_sprite=Sprite(surf_man->get_surface(Surface_Manager::SRF_KEY_BLUE));
		break;
	case 4:
		m_sprite=Sprite(surf_man->get_surface(Surface_Manager::SRF_KEY_GREEN));
		break;
	case 8:
		m_sprite=Sprite(surf_man->get_surface(Surface_Manager::SRF_KEY_YELLOW));
		break;
	default:
		assert(!"Error: Selected non existent key type.");
	}
	

	
	m_exists=true;

}

Uint32 Entity_Key::get_key_id()
{
	return m_key_id;
}
	
bool Entity_Key::pass_on_me(Direction d)
{
	current_level->set_key(m_key_id);
	Sample_Manager::instance()->play(SFX_KEY_EAT);
	kill();
	return true;
}


bool Entity_Key::player_pressing_up(Entity_Handle down_entity)
{
	current_level->set_key(m_key_id);
	Sample_Manager::instance()->play(SFX_KEY_EAT);
	kill();
	return true;
}

bool Entity_Key::player_pressing_down(Entity_Handle up_entity)
{
	current_level->set_key(m_key_id);
	Sample_Manager::instance()->play(SFX_KEY_EAT);
	kill();
	return true;
}


bool Entity_Key::player_pressing_left(Entity_Handle right_entity)
{
	current_level->set_key(m_key_id);
	Sample_Manager::instance()->play(SFX_KEY_EAT);
	kill();
	return true;
}


bool Entity_Key::player_pressing_right(Entity_Handle left_entity)
{
	current_level->set_key(m_key_id);
	Sample_Manager::instance()->play(SFX_KEY_EAT);
	kill();
	return true;
}


bool Entity_Key::explode()
{
	kill();
	return true;
}


