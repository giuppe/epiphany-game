/***************************************************************************
                          myparser..h  -  description
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
#include "emdlparser.h"
#include "epimap.h"
#include <iostream>



#ifndef MYPARSER_H
#define MYPARSER_H


class myparser: public EMDLParser
{
private:
    Epimap m_map;

public:
	myparser();
	Epimap& get_epimap();
	void handle_command_put(Entity_Type e, int x, int y);

	void handle_command_set_str(std::string o, std::string v);

	void handle_command_set_int(std::string o, unsigned int v);

	void handle_command_line(Entity_Type e, unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1);

	void handle_command_rect(Entity_Type e, unsigned int x0, unsigned int y0, unsigned int w, unsigned int h);

	void handle_command_view();

	void handle_command_write();

	void handle_sintaxerror_comma();

	void handle_sintaxerror_par();


};

#endif //MYPARSER_H
