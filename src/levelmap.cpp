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
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
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

Levelmap::Levelmap(CL_String map_path)
{

	load_map(map_path);
}

void Levelmap::load_map(CL_String map_path)
{
	ifstream scriptfile(map_path);

	myparser parsy;
	parsy<<scriptfile;
	DEBOUT("Map parsed.\n");
	Epimap epimap = parsy.get_epimap();
	DEBOUT("Map acquired.\n");
	m_min_score=epimap.get_min_score();
	m_max_time=epimap.get_max_time();
	m_name=epimap.get_name();
	m_author=epimap.get_author();
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

/*
	ifstream map(map_path);
	
	if(!map)
	{

		Common_Ex::throw_common(CL_String("Error loading map in ")+map_path+CL_String("\n"));
	}
	
	DEBOUT("Loading map in "<<map_path<<" ...\n");
		
	char cell;
	
	//getting header

	//getting init_string
	unsigned int i;
	CL_String init_string="";
	for(i=0;i<6;i++)
	{
		map.get(cell);
		init_string=init_string+std::string(1,(char)cell);
	}
	//DEBOUT(init_string<<"\n");
	if(init_string!="EPIMAP")
	{
		throw Common_Ex("Bad map header\n");
	}

// getting version
	map.get(cell);
	m_version=(unsigned int)cell;
	if (m_version>1)
	{
		throw Common_Ex("Sorry, I can't handle maps with version greather than 1.\nMaybe you can check if a new version of Epiphany has been released.\n");

	}

	//getting map size
	map.get(cell);
	m_size_x=(unsigned int)cell;
	map.get(cell);
	m_size_y=(unsigned int)cell;

// getting map name
	map.get(cell);
	while(cell!=0)
	{
		m_name=m_name+std::string(1,(char)cell);
		map.get(cell);
	}
	DEBOUT("Map name: "<<m_name<<"\n");
	
// getting author name
	map.get(cell);
	while(cell!=0)
	{
		m_author=m_author+std::string(1,(char)cell);
		map.get(cell);
	}
	DEBOUT("Map author: "<<m_author<<"\n");
//getting minimum score needed
	map.get(cell);
	m_min_score=(unsigned int)((unsigned char)cell);

//getting maximum time
	map.get(cell);
	m_max_time=(unsigned int)((unsigned char)(cell*5));
//end header

//getting real map
//	resizing
	m_map.resize(m_size_x);
	for(i=0;i<m_size_x;i++)
		m_map[i].resize(m_size_y);
//	getting
	unsigned int j;
	for(j=0; j<m_size_y; j++)
	{
		for(i=0; i<m_size_x;i++)
		{
			map.get(cell);
			m_map[i][j]=(Entity_Type)((unsigned char)(cell));
		}
	}*/

}


unsigned int Levelmap::get_min_score()
{
	return m_min_score;
}

unsigned int Levelmap::get_max_time()
{
	return m_max_time;
}

CL_String Levelmap::get_name()
{
	return m_name;
}

CL_String Levelmap::get_author()
{
	return m_author;
}

unsigned int Levelmap::get_size_x()
{
	return m_size_x;
}

unsigned int Levelmap::get_size_y()
{
	return m_size_y;
}
/*
bool Levelmap::error()
{
	return m_error;
}
*/
std::vector< std::vector<Entity_Type> >& Levelmap::get_map()
{
	return m_map;
}

Entity_Type Levelmap::get_map_element(unsigned int x, unsigned int y)
{
	if((x>m_size_x)||(y>m_size_y))
		DEBOUT("Alert: map element outside map size\n");
	
	return m_map[x][y];
}

