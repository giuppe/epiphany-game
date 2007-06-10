#include "font.h"
#include "epiconfig.h"

void Font::write(Sint32 x, Sint32 y, const char* text)
{
	m_font->print_left((int)x, (int)y, text);
}

void Font::write_center(Sint32 y, const char* text)
{
	m_font->print_center(Epiconfig::instance()->get_game_size_x()/2, (int)y, text);
}
