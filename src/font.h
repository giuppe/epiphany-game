#ifndef FONT_H_
#define FONT_H_

#include "dephine.h"
#include <ClanLib/display.h>

class Font
{
private:
	CL_Font* m_font;
	bool m_initialized;
public:
	Font(): m_initialized(false){};
	~Font(){deinit();};
	void init(CL_Font* font){m_font = font;};
    void deinit(){if(m_initialized==true) delete m_font;};
    void write(Sint32 x, Sint32 y, const char* text);
    void write_center(Sint32 y, const char* text);
};
#endif /*FONT_H_*/
