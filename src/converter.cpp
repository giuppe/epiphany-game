/***************************************************************************
                          converter.cpp  -  description
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
#include "entity_type.h"
#include <fstream>

int main(int argc, char* argv[])
{
	if(argc>=2)
	{
		ifstream oldmap(argv[1]);
		ofstream newmap;
		if(argc==3)
		{
			newmap.open(argv[2]);
		}
		else
		{
			newmap.open("./convert.map");
		}
		
		newmap<<"EPIMAP";
		newmap.put(1);
		newmap.put(32);//size_x
		newmap.put(32);//size_y
		newmap.put(0);//name
		newmap.put(0);//author
		newmap.put(0);//min_score
		newmap.put(0);//time
		unsigned char cell;



	for(int i=0; i<32; i++)
		for(int j=0; j<32; j++)
		{
			oldmap.get(cell);

			if(cell==0x0a)
			{
				oldmap.get(cell);
			}
			
			switch(cell)
			{
			case 'a':
				newmap.put((unsigned char)KEY);
				break;
			case 'b':
				newmap.put((unsigned char)FLINTSTONE);
				break;
			case 'c':
			//	newmap.put(cell-87+6);
				newmap.put((unsigned char)PEPERON);
				break;
			case 'd':
				newmap.put((unsigned char)BRICK);
				break;
			case 'e':
				newmap.put((unsigned char)WOOD);
				break;
			default:
				newmap.put(cell-48);
				break;
			}
		}
	}
}

