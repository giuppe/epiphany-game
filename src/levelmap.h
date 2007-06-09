/***************************************************************************
                        levelmap.h  -  description
                             -------------------
    begin                : Sat Aug 3 2002
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
#include <vector>

#ifndef LEVELMAP_H
#define LEVELMAP_H

class Levelmap
{
protected:
	Uint32 m_version;
	Uint32 m_size_x;
	Uint32 m_size_y;
	const char* m_name;
	const char* m_author;
	Uint32 m_min_score;
	Uint32 m_max_time;
	std::vector< std::vector<Entity_Type> > m_map;
	//bool m_error;
//	Epimap m_epimap;
public:
	Levelmap(const char* map_path);
	Levelmap();
	void load_map(const char* map_path);
	Uint32 get_min_score();
	Uint32 get_max_time();
	const char* get_name();
	const char* get_author();
	Uint32 get_size_x();
	Uint32 get_size_y();
	//bool error();
	std::vector< std::vector<Entity_Type> >& get_map();
	Entity_Type get_map_element(Uint32 x, Uint32 y);

};

#endif //LEVELMAP_H

