/***************************************************************************
                   epimap.cpp  -  implementation of epimap class
                             -------------------
    begin                : Thu Aug 8 2002
    copyright            : (C) 2002 by Giuseppe Martino aka denever
    email                : rdmartin@infinito.it
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "epimap.h"
#include "except.h"

using namespace std;

typedef std::string::const_iterator cit;
typedef std::string::iterator it;

Epimap::Epimap(): m_version(1), m_min_score(0), m_max_time(20)
{
	set_map_size_xy(32,32);
	make_borders();
}

entity_matrix& Epimap::get_map()
{
	if(!m_player_on_map())
    	Common_Ex::throw_common("Player is not on map.\n");
	if(!m_exit_on_map())
    	Common_Ex::throw_common("Exit is not on map.\n");

	return m_map;
}

/*
Epimap::Epimap(const Epimap& cpy)
{
    m_map = cpy.m_map;
    
    m_name = cpy.m_name;
    m_author = cpy.m_author;
    
    m_version = cpy.m_version;
    
    m_size_x = cpy.m_size_x;
    m_size_y = cpy.m_size_y;

    m_min_score = cpy.m_min_score;
    m_max_time = cpy.m_max_time;
}
*/
Epimap::~Epimap()
{}

bool Epimap::m_exit_on_map()
{
	for(unsigned int y=0; y<m_size_y; y++)
		for(unsigned int x=0; x<m_size_x; x++)
			if(m_map[x][y] == EXIT)
				return true;
    return false;
}

bool Epimap::m_player_on_map()
{
	for(unsigned int y=0; y<m_size_y; y++)
		for(unsigned int x=0; x<m_size_x; x++)
			if(m_map[x][y] == PLAYER)
				return true;
	return false;
}

void Epimap::set_map_version(unsigned int v)
{
	m_version = v;
}

unsigned int Epimap::get_map_version()
{
	return m_version;
}

unsigned int Epimap::get_min_score()
{
	return m_min_score;
}

unsigned int Epimap::get_max_time()
{
	return m_max_time;
}

string Epimap::get_name()
{
	return m_name;
}

string Epimap::get_author()
{
	return m_author;
}

unsigned int Epimap::get_size_x()
{
	return m_size_x;
}

unsigned int Epimap::get_size_y()
{
	return m_size_y;
}

Entity_Type Epimap::get_entity(unsigned int x, unsigned int y)
{
	if((x>m_size_x)||(y>m_size_y))
		Common_Ex::throw_common("Alert: map element outside map size\n");
	
	return m_map[x][y];
}

void Epimap::set_map_size_xy(unsigned int x, unsigned int y)
{
	if( x < 1 || y < 1)
		Common_Ex::throw_common("Can't set size less than 1");

	m_size_x = x;
	m_size_y = y;

	m_map.resize(m_size_x);

	for(unsigned int i=0; i<m_size_x; i++)
		m_map[i].resize(m_size_y);

	for(unsigned int i=0; i<m_size_x; i++)
		for(unsigned int j=0; j<m_size_y; j++)
			m_map[i][j] = GRASS;
}

/*void Epimap::set_version(unsigned int v)
{}*/

void Epimap::set_min_score(unsigned int s)
{  /*
	if(s<0)
		Common_Ex::throw_common("Can't set minimum score less than 0");
  */
	m_min_score = s;
}

void Epimap::set_max_time(unsigned int t)
{
	if(t<1)
		Common_Ex::throw_common("Can't set max time less than 1");

	m_max_time = t;
}

void Epimap::set_name(const string& name)
{
	if(name.empty())
		Common_Ex::throw_common("Can't set a map name to null");

	m_name = name;
}

void Epimap::set_author(const string& author)
{
	if(author.empty())
		Common_Ex::throw_common("Can't set a map author to null");
	m_author = author;
}

void Epimap::put_entity(Entity_Type e, unsigned int x, unsigned int y)
{
	if(x>m_size_x || y>m_size_y)
		Common_Ex::throw_common("Setting an entity out of map");

	m_map[y][x] = e;
}
/*
void put_player(unsigned int x, unsigned int y)
{
    if(x>m_size_x || y>m_size_y)
        		Common_Ex::throw_common("Putting player out of map");

    m_map[y][x] = PLAYER;
}

void Epimap::put_exit(unsigned int x, unsigned int y)
{
    if(x>m_size_x || y>m_size_y)
		Common_Ex::throw_common("Putting exit out of map");

    m_map[y][x] = EXIT;
}
*/

void Epimap::make_borders()
{
	for(unsigned int i=0; i<m_size_y; i++)
	{
		m_map[0][i] =  STEEL;
		m_map[m_size_x - 1][i] = STEEL;
	}
	
	for(unsigned int i=0; i<m_size_y; i++)
	{
		m_map[i][0] = STEEL;
		m_map[i][m_size_y-1] = STEEL;
	}
}

void Epimap::put_line(Entity_Type t, unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2)
{
	if( (x1 <= 0) || (x2 <= 0) || (y1 <= 0) || (y2 <= 0) )
		Common_Ex::throw_common("Can't write on borders or out of map!");

	if( (x1>32) || (x2>32) || (y1 > 32) || (y2 > 32) )
		Common_Ex::throw_common("Can't write on borders or out of map!");


	int deltax = x2 - x1;
	int deltay = y2 - y1;
	int d = 2*deltay - deltax;
    
	if(deltax>1)
	{
		unsigned int y = y1;

		for(unsigned int x=x1; x<=x2; x++)
		{
			m_map[y][x] = t;

			if(d<0)
				d+=(2*deltay);
			else
			{
				d+=2*(deltay-deltax);
				y++;
			}
		}
	}
	else
		if(deltay>1)
			for(unsigned int y=y1; y<=y2; y++)
				m_map[y][x1] = t;
}

void Epimap::put_rectangle(Entity_Type t, unsigned int x1, unsigned int y1, unsigned int height, unsigned int width)
{
	for(unsigned int x=x1; x<x1+height; x++)
		for(unsigned int y=y1; y<y1+width; y++)
			m_map[y][x] = t;
}

unsigned int Epimap::count_total_score()
{
	unsigned int score = 0;
  unsigned int x,y;
	for(x = 0; x<m_size_x; x++)
	{
		for(y = 0; y<m_size_y; y++)
		{
			if(m_map[x][y] == EMERALD)
			{
				score += 1;
				
			}
			else
			if(m_map[x][y] == SAPPHIRE)
			{
				score += 3;
			}
		}
	}

	return score;
}
