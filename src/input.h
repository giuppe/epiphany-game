/***************************************************************************
                          input.h  -  description
                             -------------------
    begin                : Jun 13 2007
    copyright            : (C) 2007 by Giuseppe D'Aqui'
    email                : kumber@tiscalinet.it
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License, Version 2,      *
 *   as published by the Free Software Foundation.                         *
 *                                                                         *
 ***************************************************************************/

#ifndef INPUT_H_
#define INPUT_H_
#include <SDL2/SDL.h>
class Input
{
private:
// states
    bool m_left;
    bool m_right;
    bool m_up;
    bool m_down;
    bool m_alt;
    bool m_quit;
    bool m_die;
    bool m_fire;
    bool m_pause;
    bool m_enter;
    bool m_fullscreen;

    bool p_left;
    bool p_right;
    bool p_up;
    bool p_down;
    bool p_alt;
    bool p_quit;
    bool p_die;
    bool p_fire;
    bool p_pause;
    bool p_enter;
    bool p_fullscreen;

    bool r_left;
    bool r_right;
    bool r_up;
    bool r_down;
    bool r_alt;
    bool r_quit;
    bool r_die;
    bool r_fire;
    bool r_pause;
    bool r_enter;
    bool r_fullscreen;


public:

    int event_filter(const SDL_Event *event);
    bool get_left(){return m_left;}
    bool get_right(){return m_right;}
    bool get_up(){return m_up;}
    bool get_down(){return m_down;}
    bool get_quit(){return m_quit;}
    bool get_die(){return m_die;}
    bool get_fire(){return m_fire;}
    bool get_pause(){return m_pause;}
    bool get_enter(){return m_enter;}
    void update();
    void init();

    void reset_states();
            
// begin Singleton stuff

private:

	static Input* _instance;

protected:

	Input(){};

public:

	static Input* instance();

// end Singleton stuff

};
#endif /*INPUT_H_*/
