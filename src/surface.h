#ifndef SURFACE_H_
#define SURFACE_H_
#include "dephine.h"
#include <SDL/SDL.h>

//typedef CL_Surface Surface;




class Surface
{
private:
	SDL_Surface* m_surface;
	
	Uint32 m_frame_size_x;
	
	Uint32 m_frame_size_y;
	
public:

	Surface():m_surface(0), m_frame_size_x(0), m_frame_size_y(0){};
	
	Surface(SDL_Surface* surface):m_surface(surface), m_frame_size_x(32), m_frame_size_y(32){};

	void put_screen(Sint32 x, Sint32 y, Uint32 size_x, Uint32 size_y, int frame_no=-1);
	
	void init(SDL_Surface* surface);
	
	~Surface();
	
};



#endif /*SURFACE_H_*/
