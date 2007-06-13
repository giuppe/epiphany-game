#include "font_manager.h"
#include "font_factory.h"
#include <cassert>


void Font_Manager::init()
{
	add_font(Font_Factory::instance()->create_font(Font_Factory::MENU_FONT));
	add_font(Font_Factory::instance()->create_font(Font_Factory::GAME_FONT));
	add_font(Font_Factory::instance()->create_font(Font_Factory::CREDITS_FONT));
	add_font(Font_Factory::instance()->create_font(Font_Factory::TIME_FONT));
}

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

void Font_Manager::deinit()
{
	if(m_fonts.size()>1)
	{
		// start from the beginning of the array
  		std::vector<Font*>::iterator itPos = m_fonts.begin();
  
  		// clear all elements from the array
  		for(; itPos < m_fonts.end(); itPos++)
    		delete *itPos;    // free the element from memory
   
   		// finally, clear all elements from the array
  		m_fonts.clear();
	}
}

// begin Singleton stuff

Font_Manager* Font_Manager::_instance = 0;

Font_Manager* Font_Manager::instance()
{
	if (_instance == 0)
	{
		_instance = new Font_Manager();
		_instance->init();
	}
	return _instance;
}

//end Singleton stuff
