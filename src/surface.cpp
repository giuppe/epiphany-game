#include "dephine.h"
#include "SDL/SDL.h"
#include "screen.h"
#include "surface.h"

void Surface::init(SDL_Surface* surface, Uint32 frame_size_x=32, Uint32 frame_size_y=32)
{
	m_surface = surface;
	m_frame_size_x=frame_size_x;
	m_frame_size_y=frame_size_y;
}

void Surface::put_screen(Sint32 x, Sint32 y, Uint32 size_x, Uint32 size_y, int frame_no)
{
	
	SDL_Rect src;
	SDL_Rect dest;
	SDL_Surface* screen = Screen::instance()->get_screen();
	if(frame_no == -1)
	{
	
	dest.x = x;
	dest.y = y;

	dest.w = size_x;
	dest.h = size_y;
		SDL_BlitSurface(m_surface, NULL,  screen, &dest);
	}
	else
	{
	src.x = (frame_no%k_max_anim)*m_frame_size_x;
	src.y = (frame_no/k_max_anim)*m_frame_size_y;
	
	src.w = m_frame_size_x;
	src.h = m_frame_size_y;
	
	dest.x = x;
	dest.y = y;

	dest.w = m_frame_size_x;
	dest.h = m_frame_size_y;
	SDL_BlitSurface(m_surface, &src,  screen, &dest);
	}
	
	
	
	
}

Surface::~Surface()
{
	SDL_FreeSurface(m_surface);
}
