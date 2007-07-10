/***************************************************************************
                    emdlparser.cpp  - implements emdlparser
                             -------------------
    begin                : Mar Jan 14 2003
    copyright            : (C) 2003 by Giuseppe "denever" Martino
    email                : rdmartin@infinito.it
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License, Version 2,      *
 *   as published by the Free Software Foundation.                         *
 *                                                                         *
 ***************************************************************************/

#include "emdlparser.h"

Entity_Type map_entity(const std::string& str)
{
	if(str == "grass")
		return	GRASS;
	if(str == "player")
		return	PLAYER;
	if(str == "steel")
		return STEEL;
	if(str == "emerald")
		return EMERALD;
	if(str == "boulder")
		return BOULDER;
	if(str == "sapphire")
		return SAPPHIRE;
	if(str == "exit")
		return EXIT;
	if(str == "explosion")
		return EXPLOSION;
	if(str == "door")
		return DOOR;
	if(str == "red_door")
		return DOOR_RED;
	if(str == "blue_door")
		return DOOR_BLUE;
	if(str == "green_door")
		return DOOR_GREEN;
	if(str == "yellow_door")
		return DOOR_YELLOW;
	if(str == "key")
		return KEY;
	if(str == "red_key")
		return KEY_RED;
	if(str == "blue_key")
		return KEY_BLUE;
	if(str == "green_key")
		return KEY_GREEN;
	if(str == "yellow_key")
		return KEY_YELLOW;
	if(str == "flintstone")
		return FLINTSTONE;
	if(str == "peperon")
		return PEPERON;
	if(str == "peperon_up")
		return PEPERON_UP;
	if(str == "peperon_right")
		return PEPERON_RIGHT;
	if(str == "peperon_down")
		return PEPERON_DOWN;
	if(str == "peperon_left")
		return PEPERON_LEFT;
	if(str == "brick")
		return BRICK;
	if(str == "wood")
		return  WOOD;
	if(str == "tomato")
		return TOMATO;
	if(str == "tomato_up")
		return TOMATO_UP;
	if(str == "tomato_right")
		return TOMATO_RIGHT;
	if(str == "tomato_down")
		return TOMATO_DOWN;
	if(str == "tomato_left")
		return TOMATO_LEFT;
	return UNKNOWN;
}

EMDLParser::EMDLParser()
{
	clear();
}

void EMDLParser::clear()
{
	//m_command.clear();
	m_command = "";

	//m_object.clear();
	m_object = "";

	//m_string_value.clear();
	m_string_value = "";
	
	m_x0 = 0;
	m_x1 = 0;
	
	m_y0 = 0;
	m_y1 = 0;
	
	m_value = 0;
}

void EMDLParser::operator<<(std::ifstream& stream)
{
	char ch;
	std::string alfa;

//    alfa.clear(); //ONLY ON GCC 3.x
	alfa = "";

	bool comment = false;
	bool string_value = false;
	bool first_coord = true;
	bool command = true;

	while(stream.get(ch))
		switch(ch)
		{
		case '(':
			if(!comment)
			{
				if(first_coord)
					stream>>m_x0;
				else
					stream>>m_x1;
		
				stream.get(ch);

				if(ch != ',')
				{
					handle_sintaxerror_comma();
					break;
				}
	
				if(first_coord)
					stream>>m_y0;
				else
					stream>>m_y1;
		
				stream.get(ch);
				if(ch != ')')
				{
					handle_sintaxerror_par();
					break;
				}

				if(first_coord)
					first_coord = false;
				break;
			}

		case '#':
			comment = true;
			break;

		case '"':
			if(!comment)
				if(!string_value)
					string_value = true;
				else
					if(!alfa.empty())
					{
						string_value = false;
						m_string_value = alfa;

						//alfa.clear(); //ONLY ON GCC 3.x
						alfa = "";
					}
			break;

		case '\n':
			comment = false;
			first_coord = true;
			command = true;
			break;	

		case ';':
		{
			if(command)
			m_command = alfa;
	    
			// alfa.clear(); //ONLY ON GCC 3.x
			alfa = "";
   
			if(!comment && !m_command.empty())
			    read(m_command[0]);
			
			break;
		}
		case ' ':
			if(!comment && !string_value && !alfa.empty())
			{
				if(command)
				{
					m_command = alfa;
		    
					//alfa.clear(); //ONLY GCC 3.x
					alfa = "";
		    
					command = false;
					break;
				}
				else
				{
					m_object = alfa;
		    
					//alfa.clear(); //ONLY ON GCC 3.x
					alfa = "";
				}
			}
	    
		default:
			if(!comment)
				if(!isdigit(ch))
					alfa += ch;
				else
				{
					stream.putback(ch);
					stream >> m_value;
				}
		}
}


void EMDLParser::read(char ch)
{
    switch(ch)
    {
    case 's':
	if(!m_string_value.empty())
	    handle_command_set_str(m_object, m_string_value);
	else
	    handle_command_set_int(m_object, m_value);
	break;
    case 'p':
    {
	Entity_Type e = map_entity(m_object);
	handle_command_put(e,m_x0,m_y0);
	break;
    }
    case 'l':
    {
	Entity_Type e = map_entity(m_object);
	handle_command_line(e, m_x0, m_y0, m_x1, m_y1);
	break;
    }
    case 'r':
    {
	Entity_Type e = map_entity(m_object);
	handle_command_rect(e, m_x0, m_y0, m_x1, m_y1);
	break;
    }
    case 'v':
    {
	handle_command_view();
	break;
    }
    case 'w':
    {
	handle_command_write();
	break;
    }
    default:
	break;
    };
    
    clear();
}
