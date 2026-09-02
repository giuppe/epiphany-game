/***************************************************************************
                          inputbase.h  -  basic input event
                             -------------------
    begin                : Sep 01 2026
    copyright            : (C) 2026 by Giuseppe D'Aqui'
    email                : kumber@tiscalinet.it
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License, Version 2,      *
 *   as published by the Free Software Foundation.                         *
 *                                                                         *
 ***************************************************************************/

 /** Inspired by Flixel input management: 
 License: [https://github.com/HaxeFlixel/flixel/blob/5e147e81bb59a441f4afed72ab9a8299d8211216/LICENSE.md] 
 */

#ifndef INPUT_BASE_H_
#define INPUT_BASE_H_

enum InputState
{
	JUST_RELEASED,
	RELEASED,
	PRESSED,
	JUST_PRESSED
};


class InputBase
{
private:
	int ID;


	InputState current = RELEASED;
	InputState last = RELEASED;

public:
    InputBase()
	{
		this->ID = 0;
	}

	InputBase(int ID)
	{
		this->ID = ID;

	}

	void press()
	{
		bool pressed = last == PRESSED || last == JUST_PRESSED;
		last = current;
		current = pressed ? PRESSED : JUST_PRESSED;
	}

	void release()
	{
		bool pressed = last == PRESSED || last == JUST_PRESSED;
		last = current;
		current = pressed ? JUST_RELEASED : RELEASED;
	}

	void update()
	{
		if (last == JUST_RELEASED && current == JUST_RELEASED)
		{
			current = RELEASED;
		}
		else if (last == JUST_PRESSED && current == JUST_PRESSED)
		{
			current = PRESSED;
		}

		last = current;
	}

	void reset()
	{
		current = RELEASED;
		last = RELEASED;
	}


	inline bool get_just_released()
	{
		return current == JUST_RELEASED;
	}

	inline bool get_released()
	{
		return current == RELEASED || current == JUST_RELEASED;
	}

	inline bool get_pressed()
	{
		return current == PRESSED || current == JUST_PRESSED;
	}

	inline bool get_just_pressed()
	{
		return current == JUST_PRESSED;
	}
};



#endif //INPUT_BASE_H