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

#include "dephine.h"
#include "entity_type.h"
#include <vector>
#include <string>

#ifndef EPIMAP_H
#define EPIMAP_H

typedef std::vector< std::vector<Entity_Type> > entity_matrix;

class Epimap
{
private:
	Uint32 m_version;
	Uint32 m_size_x;
	Uint32 m_size_y;

	std::string m_name;
	std::string m_author;

	Uint32 m_min_score;
	Uint32 m_max_time;

	entity_matrix m_map;



	void make_borders();

	bool m_player_on_map();


	bool m_exit_on_map();

public:

	Epimap();
//	Epimap(const Epimap&);
	~Epimap();

	void set_map_version(Uint32);
	Uint32 get_map_version();

	Uint32 count_total_score();
	Uint32 get_min_score();
	Uint32 get_max_time();
    
	void set_min_score(Uint32);
	void set_max_time(Uint32);
    
	std::string get_name();
	std::string get_author();
    
	void set_name(const std::string&);
	void set_author(const std::string&);
    
	Uint32 get_size_x();
	Uint32 get_size_y();
    
	void set_map_size_xy(Uint32, Uint32);
       
	entity_matrix& get_map();

	void put_entity(Entity_Type, Uint32, Uint32);

	Entity_Type get_entity(Uint32, Uint32);

	void put_line(Entity_Type, Uint32, Uint32, Uint32, Uint32);

	void put_rectangle(Entity_Type, Uint32, Uint32, Uint32, Uint32);

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
