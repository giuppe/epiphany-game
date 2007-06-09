// -*- C++ -*-
/***************************************************************************
                  emdlparser.cpp  - definition of emdlparser
                             -------------------
    begin                : Mar Jan 14 2003
    copyright            : (C) 2003 by Giuseppe "denever" Martino
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


#ifndef EMDLPARSER_H
#define EMDLPARSER_H

#include "dephine.h"
#include <string>
#include <fstream>
#include "entity_type.h"

class EMDLParser
{
private:
	Uint32 m_x0;
	Uint32 m_y0;
	Uint32 m_x1;
	Uint32 m_y1;
	Uint32 m_value;

	std::string m_command;
	std::string m_object;
	std::string m_string_value;

public:
	EMDLParser();


	virtual ~EMDLParser()
	{
	clear();
	}

	void clear();
        void read(char);
	void operator<<(std::ifstream&);

	virtual void handle_command_put(Entity_Type, int x, int y)=0;
	virtual void handle_command_set_str(std::string, std::string)=0;
	virtual void handle_command_set_int(std::string, Uint32)=0;
	virtual void handle_command_line(Entity_Type, Uint32, Uint32, Uint32, Uint32)=0;
	virtual void handle_command_rect(Entity_Type, Uint32, Uint32, Uint32, Uint32)=0;

	virtual void handle_command_view()=0;
	virtual void handle_command_write()=0;
    
	virtual void handle_sintaxerror_comma()=0;
	virtual void handle_sintaxerror_par()=0;

};

#endif //EMDLPARSER_H
