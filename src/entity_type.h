/***************************************************************************
                          entity_type.h  -  description
                             -------------------
    begin                : Fri Aug 31 2001
    copyright            : (C) 2001 by Giuseppe D'Aquì
    email                : kumber@tiscalinet.it
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License, Version 2, as published by  *
 *   the Free Software Foundation.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef ENTITY_TYPE_H
#define ENTITY_TYPE_H

//All types of entities in game
enum Entity_Type{	UNKNOWN=0,
									PLAYER=1,
									GRASS=2,
									STEEL=3,
									EMERALD=4,
									BOULDER=5,
									SAPPHIRE=6,
									EXIT=7,
									EXPLOSION=8,
									DOOR=9,
									DOOR_RED=9,
									DOOR_BLUE=10,
									DOOR_GREEN=11,
									DOOR_YELLOW=12,
									KEY=13,
									KEY_RED=13,
									KEY_BLUE=14,
									KEY_GREEN=15,
									KEY_YELLOW=16,
									FLINTSTONE=17,
									PEPERON=18,
									PEPERON_UP=18,
									PEPERON_RIGHT=19,
									PEPERON_DOWN=20,
									PEPERON_LEFT=21,
									BRICK=22,
									WOOD=23,
									TOMATO=24,
									TOMATO_UP=24,
									TOMATO_RIGHT=25,
									TOMATO_DOWN=26,
									TOMATO_LEFT=27
									};

#endif //ENTITY_TYPE_H
