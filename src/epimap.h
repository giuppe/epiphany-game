// -*-C++-*-
/***************************************************************************
                    epimap.h  -  Definition of epimap class
                             -------------------
    begin                : Sat Aug 3 2002
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

#include "entity_type.h"
#include <vector>
#include <string>

#ifndef EPIMAP_H
#define EPIMAP_H

typedef std::vector< std::vector<Entity_Type> > entity_matrix;

class Epimap
{
private:
	unsigned int m_version;
	unsigned int m_size_x;
	unsigned int m_size_y;

	std::string m_name;
	std::string m_author;

	unsigned int m_min_score;
	unsigned int m_max_time;

	entity_matrix m_map;



	void make_borders();

	bool m_player_on_map();


	bool m_exit_on_map();

public:

	Epimap();
//	Epimap(const Epimap&);
	~Epimap();

	void set_map_version(unsigned int);
	unsigned int get_map_version();

	unsigned int count_total_score();
	unsigned int get_min_score();
	unsigned int get_max_time();
    
	void set_min_score(unsigned int);
	void set_max_time(unsigned int);
    
	std::string get_name();
	std::string get_author();
    
	void set_name(const std::string&);
	void set_author(const std::string&);
    
	unsigned int get_size_x();
	unsigned int get_size_y();
    
	void set_map_size_xy(unsigned int, unsigned int);
       
	entity_matrix& get_map();

	void put_entity(Entity_Type, unsigned int, unsigned int);

	Entity_Type get_entity(unsigned int, unsigned int);

	void put_line(Entity_Type, unsigned int, unsigned int, unsigned int, unsigned int);

	void put_rectangle(Entity_Type, unsigned int, unsigned int, unsigned int, unsigned int);

};
 /*
class Epimap_excep
{// temporany exception class
public:
    Epimap_excep(const std::string& msg): m_msg(msg)
	{};
    inline std::string get_msg(){ return m_msg;};

private:
    std::string m_msg;
};
*/
#endif //EPIMAP_H
