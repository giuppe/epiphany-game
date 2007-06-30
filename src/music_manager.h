
#include "dephine.h"
#include <SDL/SDL_mixer.h>
#include <vector>


#ifndef MUSIC_MANAGER_H_
#define MUSIC_MANAGER_H_


enum Music_Type{
				MUS_MENU,
				MUS_CREDITS,
				MUS_GAME
};


class Music_Manager{
private:
	std::vector<Mix_Music*> m_musics;
	
	Mix_Music* get_music(Music_Type music);
	
	void load_musics();
	
public:
	
	void init();
	
	void deinit();
	
	void play(Music_Type type);
	
	Uint32 get_max_volume();
	
	Uint32 get_volume();
	
	void set_volume(Uint32 value);
	
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
