#include "font_manager.h"
#include <cassert>

Font_Handle Font_Manager::add_font(Font* font)
{
	Font_Handle f_handle = m_fonts.size();
	m_fonts.push_back(font);
	return f_handle;
}

Font* Font_Manager::get_font(Font_Handle handle)
{
	assert((m_fonts.size()>handle) && "Error: Accessing non-existent font.");
	return m_fonts[handle];
}

// begin Singleton stuff

Font_Manager* Font_Manager::_instance = 0;

Font_Manager* Font_Manager::instance()
{
	if (_instance == 0)
	{
		_instance = new Font_Manager();
	}
	return _instance;
}

//end Singleton stuff
