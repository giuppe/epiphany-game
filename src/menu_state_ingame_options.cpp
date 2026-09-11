#include "menu_state_ingame_options.h"

#include "menu_list_ingame_options.h"
#include "screen.h"
#include "input.h"
#include "surface_manager.h"
#include "fonts/font_factory.h"


Menu_State_Ingame_Options::Menu_State_Ingame_Options()
{
    
}

Menu_State_Ingame_Options::~Menu_State_Ingame_Options()
{

}


void Menu_State_Ingame_Options::create()
{
    Menu_Base_State::create();
    m_menu_font = Font_Factory::MENU_FONT;
    Input::instance()->reset_states();
    m_menu_list = new Menu_List_Ingame_Options(this);
    
    Font* menu_font = Font_Manager::instance()->get_font(m_menu_font); 

    Uint32 menu_height = menu_font->get_text_height() * (6+1);
    m_background = new Sprite_Nine_Slice();
    m_background->init(
        Surface_Manager::instance()->get_surface(Surface_Manager::SRF_DIALOG_BACKGROUND), 
        400+50+20, 
        menu_height
    );
}

void Menu_State_Ingame_Options::update(double elapsed)
{
    Menu_Base_State::update(elapsed);

	//DEBOUT("Menu selected: "<<m_menu_list->get_selected()<<"\n");
}

void Menu_State_Ingame_Options::deinit()
{
    Menu_Base_State::deinit();
	delete m_menu_list;
    delete m_background;
}

void Menu_State_Ingame_Options::draw()
{
    Menu_Base_State::draw();
	Epiconfig* config = Epiconfig::instance();
    Screen* screen = Screen::instance();

	this->print_menu_background();
	this->render_menu_list(m_menu_list, config->get_base_screen_size_y()/4, config->get_base_screen_size_x()/3, config->get_base_screen_size_y()/9);

}

void Menu_State_Ingame_Options::print_menu_background()
{
    Epiconfig* config = Epiconfig::instance();
    ScreenCoord coord;
    coord.x = config->get_base_screen_size_x()/3 - 60 -50-10;
    coord.y = config->get_base_screen_size_y()/4 - 30+5;
    m_background->set_position_on_screen(coord);
    m_background->draw();
}