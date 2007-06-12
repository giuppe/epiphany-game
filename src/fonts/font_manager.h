#ifndef FONT_MANAGER_H_
#define FONT_MANAGER_H_
#include "dephine.h"
#include "surface_manager.h"
#include "font.h"
#include <vector>

typedef Uint32 Font_Handle;

class Font_Manager
{
private:

    std::vector<Font*> m_fonts;

public:
 
	Font_Handle add_font(Font* font);

	Font* get_font(Font_Handle);
	
	void deinit();

// begin Singleton stuff

private:

    static Font_Manager* _instance;

protected:

    Font_Manager(){};

public:

    static Font_Manager* instance();

// end Singleton stuff

};


#endif /*FONT_MANAGER_H_*/
