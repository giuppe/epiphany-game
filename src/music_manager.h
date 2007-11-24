/***************************************************************************
                          music_manager.h  -  description
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
#include <SDL/SDL_mixer.h>
#include <vector>


#ifndef MUSIC_MANAGER_H_
#define MUSIC_MANAGER_H_


enum Music_Type{
				MUS_MENU,
				MUS_CREDITS,
				MUS_GAME,
				MUS_READY
};


class Music_Manager{
private:
	std::vector<Mix_Music*> m_musics;
	
	Mix_Music* get_music(Music_Type music);
	
	void load_musics();
	
	bool m_disabled;
	
	bool music_enabled;
	
public:
	
	void init();
	
	void deinit();
	
	void play(Music_Type type);
	
	Uint32 get_max_volume();
	
	Uint32 get_volume();
	
	void set_volume(Uint32 value);
	
	void disable_music();
	
	void enable_music();
	
	// begin Singleton stuff

private:

    static Music_Manager* _instance;

protected:

	Music_Manager(){};

public:

    static Music_Manager* instance();

// end Singleton stuff

};
#endif /*MUSIC_MANAGER_H_*/
