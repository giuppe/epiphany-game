/***************************************************************************
                          screen.cpp  -  description
                             -------------------
    begin                : Mon Oct 22 2001
    copyright            : (C) 2001 by Giuseppe D'Aquì
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
#include "screen.h"
#include "sprite.h"
#include "entity.h"



unsigned int Screen::get_screen_size_x()
{
	return m_screen_size_x;
	
}

unsigned int Screen::get_screen_size_y()
{

	return m_screen_size_y;
	
}

void Screen::init(unsigned int resolution_x, unsigned int resolution_y, unsigned int level_size_x, unsigned int level_size_y, unsigned int cell_size)
{
	m_win_pos_x=0;
	m_win_pos_y=0;
	m_win_size_x=resolution_x;
	m_win_size_y=resolution_y-Epiconfig::instance()->get_score_size_y();
	m_cell_size=cell_size;
	
	m_screen_size_x=level_size_x*m_cell_size;
	m_screen_size_y=level_size_y*m_cell_size;
	
	try
	{
	CL_Display::set_videomode ((int)resolution_x, (int)resolution_y,16, false);
	}
	catch(CL_Error ex)
	{
		std::cout<<"Error initializing video mode\n";
	}
}


void Screen::put(Sprite& sprite)
{
	int curr_pos_x=sprite.get_pos_x();
	int curr_pos_y=sprite.get_pos_y();
	if(	((curr_pos_x+48>m_win_pos_x)&&
			(curr_pos_x<(m_win_pos_x+m_win_size_x)))&&
			((curr_pos_y+48>m_win_pos_y)&&
			(curr_pos_y<(m_win_pos_y+m_win_size_y))))
	{
//	DEBOUT("drawing sprite at: "<<curr_pos_x<<", "<<curr_pos_y<<"\n");
	//int frame=sprite.get_frame_number();
	//sprite.put_screen((int)(curr_pos_x-m_win_pos_x), (int)(curr_pos_y-m_win_pos_y), (int)m_cell_size, (int)m_cell_size, frame);
	sprite.put_screen((int)(curr_pos_x-m_win_pos_x), (int)(curr_pos_y-m_win_pos_y), (int)m_cell_size, (int)m_cell_size);
	}
	
}

void Screen::set_cell_size(unsigned int cell_size)
{
	
	m_cell_size=cell_size;
	
}

void Screen::set_window_center(int x, int y)
{

	if(x>(m_win_size_x/2))
	{
		if((x+(m_win_size_x/2))<m_screen_size_x)
		{
			m_win_pos_x=(x-(m_win_size_x/2));
		}	
		else
		{
			m_win_pos_x=(m_screen_size_x-(m_win_size_x));
		}
	}
	else
	{
		m_win_pos_x=0;
	}
		
	if(y>(m_win_size_y/2))
	{
		if((y+(m_win_size_y/2))<m_screen_size_y)
		{
			m_win_pos_y=(y-(m_win_size_y/2));
		}	
		else
		{
			m_win_pos_y=(m_screen_size_y-(m_win_size_y));
		}
	}
	else
	{
		m_win_pos_y=0;
	}

//	if((x>(m_win_size_x/2))&&((x+(m_win_size_x/2))<m_screen_size_x))
//		m_win_pos_x=(x-(m_win_size_x/2));
		
//	if((y>(m_win_size_y/2))&&((y+(m_win_size_y/2))<m_screen_size_y))
//		m_win_pos_y=(y-(m_win_size_y/2));
}

void Screen::clear()
{
	CL_Display::clear_display(0.0, 0.0, 0.0, 1.0);
}	

void Screen::flip_display()
{
	CL_Display::flip_display(false);
}

void Screen::fill_rect(int x, int y, unsigned int size_x, unsigned int size_y, float r, float g, float b, float alpha)
{
	CL_Display::fill_rect(x, y, (int)size_x, (int)size_y, r, g, b, alpha);
}

void Screen::draw_rect(int x, int y, unsigned int size_x, unsigned int size_y, float r, float g, float b, float alpha)
{
	CL_Display::draw_rect(x, y, (int)size_x, (int)size_y, r, g, b, alpha);
}

// begin Singleton stuff

Screen* Screen::_instance = 0;

Screen* Screen::instance()
{
	if (_instance == 0)
	{
		_instance = new Screen();
		
	}
	return _instance;
}

//end Singleton stuff
