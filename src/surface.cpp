#include "dephine.h"
#include "surface.h"

void Surface::init(CL_Surface* surface)
{
	m_surface = surface;
}

void Surface::put_screen(Sint32 x, Sint32 y, Uint32 size_x, Uint32 size_y, int frame_no)
{
	m_surface->put_screen(x, y, (int)size_x, (int)size_y, frame_no);
}
