#include "menu_options_state.h"

#include "menu_list_options.h"
#include "screen.h"
#include "input.h"


Menu_Options_State::Menu_Options_State()
{
    
}

Menu_Options_State::~Menu_Options_State()
{

}


void Menu_Options_State::create()
{
    Menu_Base_State::create();
    m_menu_list = new Menu_List_Options(this);
    Input::instance()->reset_states();
}

void Menu_Options_State::update(double elapsed)
{
    Menu_Base_State::update(elapsed);

	//DEBOUT("Menu selected: "<<m_menu_list->get_selected()<<"\n");
}

void Menu_Options_State::deinit()
{
    Input::instance()->reset_states();
    Menu_Base_State::deinit();
	delete m_menu_list;
}

void Menu_Options_State::draw()
{
    Menu_Base_State::draw();
	Epiconfig* config = Epiconfig::instance();

	//this->print_menu_background();
	this->render_menu_list(m_menu_list, config->get_base_screen_size_y()/2, config->get_base_screen_size_x()/3, config->get_base_screen_size_y()/9);

}