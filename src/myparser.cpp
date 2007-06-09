/***************************************************************************
                          myparser.cpp  -  description
                             -------------------
    begin                : Fri Jan 17 2003
    copyright            : (C) 2003 by Giuseppe D'Aqui'
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
#include "emdlparser.h"
#include "epimap.h"
#include "myparser.h"
#include <iostream>

using namespace std;

myparser::myparser()
{}

Epimap& myparser::get_epimap()
{
	return m_map;
}

void myparser::handle_command_put(Entity_Type e, int x, int y)
{
	m_map.put_entity(e,x,y);
}

void myparser::handle_command_set_str(std::string o, std::string v)
{
	DEBOUT("parsing: set "<<o<<" "<<v<<"\n");
	if(o == "name")
		m_map.set_name(v);

	if(o == "author")
		m_map.set_author(v);

	if(o == "minscore")
		m_map.set_min_score(m_map.count_total_score());
}

void myparser::handle_command_set_int(std::string o, Uint32 v)
{
	DEBOUT("parsing: set "<<o<<" "<<v<<"\n");
	if(o == "minscore")
		m_map.set_min_score(v);

	if(o == "maxtime")
		m_map.set_max_time(v);
}

void myparser::handle_command_line(Entity_Type e, Uint32 x0, Uint32 y0, Uint32 x1, Uint32 y1)
{
	    m_map.put_line(e,x0,y0,x1,y1);
}

void myparser::handle_command_rect(Entity_Type e, Uint32 x0, Uint32 y0, Uint32 w, Uint32 h)
{
	m_map.put_rectangle(e,x0,y0,w,h);
}

void myparser::handle_command_view()
{
/*
	cout<<"View of "<<m_map.get_name()<<endl;
	cout<<"Author "<<m_map.get_author()<<endl;
	cout<<"Minimum score "<<m_map.get_min_score()<<endl;
	cout<<"Maximum time "<<m_map.get_max_time()<<endl;
	
	const char* wrap_map = " P:#EOS]*DDDD++++*@@@@=o";
	
	cout<<"   01234567890123456789012345678901"<<endl;
	for(Uint32 i = 0; i< 32; i++)
	{
		cout<<i<<" ";
		if(i<10)
		    cout<<" ";

		for(Uint32 y = 0; y<32; y++)
			cout<<wrap_map[int(m_map.get_map_element(y,i))];
		cout<<endl;
	}
*/
}

void myparser::handle_command_write()
{
//	m_map.save_map_as(compiled_file_name);
}

void myparser::handle_sintaxerror_comma()
{
	cout<<"err"<<endl;
}

void myparser::handle_sintaxerror_par()
{
	cout<<"Par"<<endl;
}



