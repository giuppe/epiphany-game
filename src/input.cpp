/***************************************************************************
                          input.cpp  -  description
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


#include "dephine.h"
#include <SDL/SDL.h>
#include "input.h"



Sint32 Input::event_filter(const SDL_Event *event)
{

	switch( event->type )
	{
	case SDL_KEYDOWN:
		//std::cout<<"Keydown event\n";
		return 1;
		break;

	case SDL_KEYUP:
		//std::cout<<"Keyup event\n";
		return 1;
		break;


	case SDL_QUIT:
		m_quit=true;
		return 0;

	default:
		return 0;
	}
	return 1;
}

Sint32 sdl_event_filter(const SDL_Event *event)
{
	return Input::instance()->event_filter(event);
}


void Input::reset_states()
{
	SDL_Event dummy_event;
	//clear all key events
	while(SDL_PollEvent(&dummy_event));
	m_quit= false;
	m_die = false;
	m_left = false;
	m_right = false;
	m_up = false;
	m_down = false;
	m_alt = false;
	m_pause = false;
	m_fire = false;
	m_enter = false;

	p_quit= false;
	p_die = false;
	p_left = false;
	p_right = false;
	p_up = false;
	p_down = false;
	p_alt = false;
	p_pause = false;
	p_fire = false;
	p_enter = false;

	r_quit= false;
	r_die = false;
	r_left = false;
	r_right = false;
	r_up = false;
	r_down = false;
	r_alt = false;
	r_pause = false;
	r_fire = false;
	r_enter = false;
	r_fullscreen = false;
}

void Input::init()
{
	m_fullscreen = false;
	m_pause = false;
	reset_states();
	SDL_SetEventFilter(sdl_event_filter);
	SDL_EnableKeyRepeat(0,0);
}


void Input::update()
{
	SDL_Event event;

	// If key was released last turn: be sure release that key
	m_left&=!r_left;
	m_right&=!r_right;
	m_up&=!r_up;
	m_down&=!r_down;
	m_fire&=!r_fire;
	m_enter&=!r_enter;
	m_die&=!r_die;
	m_quit&=!r_quit;
	m_alt&=!r_alt;

	// Forget the saved release states
	r_quit= false;
	r_die = false;
	r_left = false;
	r_right = false;
	r_up = false;
	r_down = false;
	r_alt = false;
	r_pause = false;
	r_fire = false;
	r_enter = false;

	while(SDL_PollEvent(&event))
	{
		switch( event.type )
		{
		case SDL_KEYDOWN:
			// Just keep in mind, if a key was pressed this turn
			// But in this case: Forget a key release in this turn
			if (event.key.keysym.sym==SDLK_LEFT) { p_left=true; r_left=false; }
			if (event.key.keysym.sym==SDLK_RIGHT) { p_right=true; r_right=false; }
			if (event.key.keysym.sym==SDLK_UP) { p_up=true; r_up=false; }
			if (event.key.keysym.sym==SDLK_DOWN) { p_down=true; r_down=false; }
			if (event.key.keysym.sym==SDLK_RCTRL) { p_fire=true; r_fire=false; }
			if (event.key.keysym.sym==SDLK_LCTRL) { p_fire=true; r_fire=false; }
			if (event.key.keysym.sym==SDLK_SPACE) { p_fire=true; r_fire=false; }
			if (event.key.keysym.sym==SDLK_ESCAPE) { p_die=true; r_die=false; }
			if (event.key.keysym.sym==SDLK_LALT) { p_alt=true; r_alt=false; }
			if (event.key.keysym.sym==SDLK_RALT) { p_alt=true; r_alt=false; }
			if (event.key.keysym.sym==SDLK_RETURN) { p_enter=true; r_enter=false; }
			if (event.key.keysym.sym==SDLK_p) m_pause=!m_pause;
			if (event.key.keysym.sym==SDLK_x && m_alt) m_quit=true;
			if ((event.key.keysym.sym==SDLK_q) && m_alt) m_quit=true;
			if (event.key.keysym.sym==SDLK_ESCAPE) m_quit=true;
			if ((event.key.keysym.sym==SDLK_F4) && m_alt) m_quit=true;
			if ((event.key.keysym.sym==SDLK_RETURN) && m_alt) m_fullscreen=!m_fullscreen;        
			break;

		case SDL_KEYUP:
			// Just keep in mind, if a key was released this turn
			if (event.key.keysym.sym==SDLK_LEFT) r_left=true;
			if (event.key.keysym.sym==SDLK_RIGHT) r_right=true;
			if (event.key.keysym.sym==SDLK_UP) r_up=true;
			if (event.key.keysym.sym==SDLK_DOWN) r_down=true;
			if (event.key.keysym.sym==SDLK_RCTRL) r_fire=true;
			if (event.key.keysym.sym==SDLK_LCTRL) r_fire=true;
			if (event.key.keysym.sym==SDLK_SPACE) r_fire=true;
			if (event.key.keysym.sym==SDLK_RETURN) r_enter=true;
			if (event.key.keysym.sym==SDLK_ESCAPE) r_die=true;
			if (event.key.keysym.sym==SDLK_ESCAPE) r_quit=true;
			if (event.key.keysym.sym==SDLK_LALT) r_alt=true;
			if (event.key.keysym.sym==SDLK_RALT) r_alt=true;
			break;


		case SDL_QUIT:
			m_quit=true;

		}
	}

	// If key was released this turn, unset key state
	m_left&=!r_left;
	m_right&=!r_right;
	m_up&=!r_up;
	m_down&=!r_down;
	m_fire&=!r_fire;
	m_enter&=!r_enter;
	m_die&=!r_die;
	m_quit&=!r_quit;
	m_alt&=!r_alt;

	// If key was pressed, set state apropriately.
	// left, right, up, down: the winner is the last key pressed
	// I don't expect anyone to press more than one key per turn ;)
	if (p_left)
	{
		m_left=true;
		m_right=false;
		m_up=false;
		m_down=false;
	}
	if (p_right)
	{
		m_left=false;
		m_right=true;
		m_up=false;
		m_down=false;
	}
	if (p_up)
	{
		m_left=false;
		m_right=false;
		m_up=true;
		m_down=false;
	}
	if (p_down)
	{
		m_left=false;
		m_right=false;
		m_up=false;
		m_down=true;
	}
	m_fire|=p_fire;
	m_enter|=p_enter;
	m_die|=p_die;
	m_quit|=p_quit;
	m_alt|=p_alt;

	// Forget all key press events
	p_quit= false;
	p_die = false;
	p_left = false;
	p_right = false;
	p_up = false;
	p_down = false;
	p_alt = false;
	p_pause = false;
	p_fire = false;
	p_enter = false;
}


// begin Singleton stuff

Input* Input::_instance = 0;

Input* Input::instance()
{
	if (_instance == 0)
	{
		_instance = new Input;
	}
	return _instance;
}

//end Singleton stuff
