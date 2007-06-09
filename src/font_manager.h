#ifndef FONT_MANAGER_H_
#define FONT_MANAGER_H_
#include "dephine.h"
#include "surface_manager.h"
#include <string>

class Font_Manager
{
private:
    SFont_Font* m_font;
public:
    void init(string font_surface_path);
    void deinit();
    void write(Uint32 x, Uint32 y, const char* text);
    void write_center(Uint32 y, const char* text);

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
