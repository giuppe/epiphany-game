/***************************************************************************
                          levelmap.cpp  -  description
                             -------------------
    begin                : Thu Aug 8 2002
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
#include "levelmap.h"
#include "myparser.h"
#include "epimap.h"
#include "entity_type.h"
#include <vector>
#include <string>
#include <fstream>

Levelmap::Levelmap()
{

}

Levelmap::Levelmap(const char* map_path)
{

	load_map(map_path);
}

void Levelmap::load_map(const char* map_path)
{
	std::ifstream scriptfile(map_path);

	myparser parsy;
	parsy<<scriptfile;
	DEBOUT("Map parsed.\n");
	Epimap epimap = parsy.get_epimap();
	DEBOUT("Map acquired.\n");
	m_min_score=epimap.get_min_score();
	m_max_time=epimap.get_max_time();
	m_name=epimap.get_name().c_str();
	m_author=epimap.get_author().c_str();
	m_size_x=epimap.get_size_x();
	m_size_y=epimap.get_size_y();
	DEBOUT("Getting Map... ");
	DEBOUT("\n\tMap Name: "<<m_name);
	DEBOUT("\n\tMap Author: "<<m_author);
	DEBOUT("\n\tMinimum score: "<<m_min_score);
	DEBOUT("\n\tMaximum time: "<<m_max_time);

	m_map=epimap.get_map();
	DEBOUT("\nGot.\n");
    m_version=epimap.get_map_version();


}


Uint32 Levelmap::get_min_score()
{
	return m_min_score;
}

Uint32 Levelmap::get_max_time()
{
	return m_max_time;
}

const char* Levelmap::get_name()
{
	return m_name;
}

const char* Levelmap::get_author()
{
	return m_author;
}

Uint32 Levelmap::get_size_x()
{
	return m_size_x;
}

Uint32 Levelmap::get_size_y()
{
	return m_size_y;
}


std::vector< std::vector<Entity_Type> >& Levelmap::get_map()
{
	return m_map;
}

Entity_Type Levelmap::get_map_element(Uint32 x, Uint32 y)
{
	if((x>m_size_x)||(y>m_size_y))
		DEBOUT("Alert: map element outside map size\n");
	
	return m_map[x][y];
}

