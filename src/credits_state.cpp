
#include "credits_state.h"
#include "input.h"
#include <vector>
#include "fonts/font_factory.h"
#include "screen.h"
#include "music_manager.h"
#include "game_manager.h"


void CreditsState::create()
{
    

	credits.push_back("Epiphany");
	credits.push_back(" ");
	credits.push_back("Giuseppe D'Aqui':");
	credits.push_back("    Coding, Level Design, Graphics, Music");
	credits.push_back(" ");
	credits.push_back("Giuseppe Martino:");
	credits.push_back("    Coding, Level Design");
	credits.push_back(" ");
	credits.push_back("Antonio Malara: Graphics");
	credits.push_back(" ");
	credits.push_back("Thanks to:");
	credits.push_back("  Joerg Jaspert & Ricardo Mones, for Debian Packages");
	credits.push_back("  Eric Mangold, for the Level Editor");
	credits.push_back("  Stefan for gameplay related patches");
	credits.push_back(" ");
	credits.push_back("Released under General Public License v2");
	credits.push_back("See COPYING for details.");

	//standard method: text scrolling
	
	
	
	Input* input =Input::instance();
	input->reset_states();
	
	Screen* screen = Screen::instance();
	
	screen->resize_world_screen(0,0);
	
	
	
	Music_Manager::instance()->play(MUS_CREDITS);
}

void CreditsState::update(double elapsed)
{
    
    Input* input =Input::instance();

    if((input->get_quit()||input->get_enter()||input->get_fire()))
	{
        Game_Manager::instance()->return_to_system();
        return;
    }

    

    input->update();
	
}

void CreditsState::draw()
{
    Font* credits_font = Font_Manager::instance()->get_font(Font_Factory::CREDITS_FONT);

    Uint32 i;

    for(i = 0; i < credits.size(); i++)
    {
        credits_font->write(32, 10+20*i,credits[i].c_str());
    }
}