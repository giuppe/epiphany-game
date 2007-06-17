/***************************************************************************
                          except.h  -  Exception Classes
                             -------------------
    begin                : Thu Jan 17 2002
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

#ifndef EXCEPT_H
#define EXCEPT_H

class Common_Ex
{
private:
	const char* message;

public:
	Common_Ex(const char* msg):message(msg) {}
	const char* get_message()
	{
		return message;
	}

	static void throw_common(const char* msg)
	{
		Common_Ex ex(msg);
		throw ex;
	}
		
};



#endif //EXCEPT_H


