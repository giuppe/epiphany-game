#include "dephine.h"

#include <SDL/SDL.h>
#include "input.h"



int Input::event_filter(const SDL_Event *event)
{

	switch( event->type )
    {
	case SDL_KEYDOWN:
        std::cout<<"Keydown event\n";
        return 1;
        break;
  
	case SDL_KEYUP:
        std::cout<<"Keyup event\n";
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

int sdl_event_filter(const SDL_Event *event)
{
    return Input::instance()->event_filter(event);
}


void Input::reset_states()
{
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
    SDL_PollEvent(&event);
	switch( event.type )
    {
	case SDL_KEYDOWN:
		if (event.key.keysym.sym==SDLK_LEFT) m_left=true;
		if (event.key.keysym.sym==SDLK_RIGHT) m_right=true;
		if (event.key.keysym.sym==SDLK_UP) m_up=true;
		if (event.key.keysym.sym==SDLK_DOWN) m_down=true;
		if (event.key.keysym.sym==SDLK_RCTRL) m_fire=true;
		if (event.key.keysym.sym==SDLK_LCTRL) m_fire=true;
		if (event.key.keysym.sym==SDLK_SPACE) m_fire=true;
		if (event.key.keysym.sym==SDLK_ESCAPE) m_die=true;
		if (event.key.keysym.sym==SDLK_LALT) m_alt=true;
		if (event.key.keysym.sym==SDLK_RALT) m_alt=true;
        if (event.key.keysym.sym==SDLK_RETURN) {m_enter=true;}
		if (event.key.keysym.sym==SDLK_p) m_pause!=m_pause;
		if (event.key.keysym.sym==SDLK_x && m_alt) m_quit=true;
		if (((event.key.keysym.sym==SDLK_q) && m_alt)||
			(event.key.keysym.sym==SDLK_ESCAPE)) m_quit=true;
		if ((event.key.keysym.sym==SDLK_F4) && m_alt) m_quit=true;
        if ((event.key.keysym.sym==SDLK_RETURN) && m_alt) m_fullscreen!=m_fullscreen;        
		break;

	case SDL_KEYUP:
		if (event.key.keysym.sym==SDLK_LEFT) m_left=false;
		if (event.key.keysym.sym==SDLK_RIGHT) m_right=false;
		if (event.key.keysym.sym==SDLK_UP) m_up=false;
		if (event.key.keysym.sym==SDLK_DOWN) m_down=false;
		if (event.key.keysym.sym==SDLK_RCTRL) m_fire=false;
		if (event.key.keysym.sym==SDLK_LCTRL) m_fire=false;
		if (event.key.keysym.sym==SDLK_SPACE) m_fire=false;
		if (event.key.keysym.sym==SDLK_RETURN) m_enter=false;
		if (event.key.keysym.sym==SDLK_ESCAPE) m_die=false;
		if (event.key.keysym.sym==SDLK_LALT) m_alt=false;
		if (event.key.keysym.sym==SDLK_RALT) m_alt=false;
		break;


	case SDL_QUIT:
		m_quit=true;

	}

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
