#ifndef FONT_H_
#define FONT_H_

#include "dephine.h"
#include "resource.h"
#include "SFont.h"

class Font : public Resource
{
private:
	SFont_Font* m_font;
	bool m_initialized;
public:
	Font(): m_initialized(false){};
	~Font(){deinit();};
	void init(SFont_Font* font);
    void deinit(){if(m_initialized==true) SFont_FreeFont(m_font);};
    void write(Sint32 x, Sint32 y, const char* text);
    void write_center(Sint32 y, const char* text);
};
#endif /*FONT_H_*/
