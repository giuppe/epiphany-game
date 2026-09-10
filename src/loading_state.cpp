
#include "loading_state.h"
#include "input.h"
#include <vector>
#include <string>
#include "fonts/font_factory.h"
#include "screen.h"
#include "music_manager.h"
#include "game_manager.h"


void Loading_State::create()
{
    Screen* screen = Screen::instance();
	
	screen->reset_virtual_screen_size();
	
	
	

	
	Music_Manager::instance()->play(MUS_READY);
	
	

}

void Loading_State::update(double elapsed)
{
	m_timeout -= (Uint32) (elapsed * 1000.0);
	if(m_timeout <= 0)
	{
		Uint32 current_level = Epiconfig::instance()->get_current_level();
		Game_Manager::instance()->change_state(new Game(current_level));
	}
}

void Loading_State::draw()
{
    Font* ready_font = Font_Manager::instance()->get_font(Font_Factory::MENU_FONT);
	Uint32 current_level = Epiconfig::instance()->get_current_level();
	char* text_level = new char[255];
	sprintf(text_level, "Level %d", current_level);
	ready_font->write_center(100, text_level);
	ready_font->write_center(200, "Ready!");
}