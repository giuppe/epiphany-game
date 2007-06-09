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
	unsigned int m_version;
	unsigned int m_size_x;
	unsigned int m_size_y;
	const char* m_name;
	const char* m_author;
	unsigned int m_min_score;
	unsigned int m_max_time;
	std::vector< std::vector<Entity_Type> > m_map;
	//bool m_error;
//	Epimap m_epimap;
public:
	Levelmap(const char* map_path);
	Levelmap();
	void load_map(const char* map_path);
	unsigned int get_min_score();
	unsigned int get_max_time();
	const char* get_name();
	const char* get_author();
	unsigned int get_size_x();
	unsigned int get_size_y();
	//bool error();
	std::vector< std::vector<Entity_Type> >& get_map();
	Entity_Type get_map_element(unsigned int x, unsigned int y);

};

#endif //LEVELMAP_H

