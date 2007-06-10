#include "dephine.h"
#include <ClanLib/display.h>
#include "input.h"


/*
int Input::event_filter(const SDL_Event *event)
{

	switch( event->type )
    {
	case SDL_KEYDOWN:
        cout<<"Keydown event\n";
        return 1;
        break;
  
	case SDL_KEYUP:
        cout<<"Keyup event\n";
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
*/

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
  
}

void Input::update()
{
 		reset_states();
  		CL_System::keep_alive();
		if (CL_Keyboard::get_keycode(CL_KEY_LEFT)) m_left=true;
		if (CL_Keyboard::get_keycode(CL_KEY_RIGHT)) m_right=true;
		if (CL_Keyboard::get_keycode(CL_KEY_UP)) m_up=true;
		if (CL_Keyboard::get_keycode(CL_KEY_DOWN)) m_down=true;
		if (CL_Keyboard::get_keycode(CL_KEY_SPACE)) m_fire=true;
		if (CL_Keyboard::get_keycode(CL_KEY_ESCAPE)) m_die=true;
		if (CL_Keyboard::get_keycode(CL_KEY_PAUSE)||CL_Keyboard::get_keycode(CL_KEY_P))
		{
			 m_pause = true;
		}
		if (CL_Keyboard::get_keycode(CL_KEY_ENTER)) m_enter = true;
		if (CL_Keyboard::get_keycode(CL_KEY_ESCAPE)) m_quit=true;
	
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
