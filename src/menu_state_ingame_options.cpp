#include "menu_state_ingame_options.h"

#include "menu_list_ingame_options.h"
#include "screen.h"
#include "input.h"


Menu_State_Ingame_Options::Menu_State_Ingame_Options()
{
    
}

Menu_State_Ingame_Options::~Menu_State_Ingame_Options()
{

}


void Menu_State_Ingame_Options::create()
{
    Menu_Base_State::create();
    Input::instance()->reset_states();
    m_menu_list = new Menu_List_Ingame_Options(this);
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
    //TODO: draw a semi-transparent background
}