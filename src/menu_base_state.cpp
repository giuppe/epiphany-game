#include "menu_base_state.h"

#include "screen.h"
#include "menu_list.h"
#include "surface_manager.h"
#include "input.h"
#include "epiconfig.h"
#include "fonts/font.h"
#include "fonts/font_manager.h"
#include "fonts/font_factory.h"

Menu_Base_State::Menu_Base_State()
{
    m_menu_font=Font_Factory::MENU_FONT;

	Surface_Manager* surf_man= Surface_Manager::instance();

	m_selector.init(surf_man->get_surface(Surface_Manager::SRF_MENU_SELECTOR));
	
	m_background = surf_man->get_surface(Surface_Manager::SRF_MENU_BACKGROUND);

	m_menu_list = NULL;
}



void Menu_Base_State::create()
{
    m_selector.start_animation();
    Input::instance()->reset_states();

	Screen::instance()->resize_world_screen(0, 0);
}

void Menu_Base_State::update(double elapsed)
{
    manage_input();
}

void Menu_Base_State::draw()
{
    
}

void Menu_Base_State::deinit()
{

}




void Menu_Base_State::print_menu_background()
{
	
	Epiconfig* config=Epiconfig::instance();
	
	ScreenCoord scr_coord;
	for(Uint32 i=0; i< config->get_base_screen_size_x(); i+=96)
	for(Uint32 j=0; j< config->get_base_screen_size_y(); j+=96)
	{
		
		scr_coord.x = i;
		scr_coord.y = j;
		Surface_Manager::instance()->get_surface(Surface_Manager::SRF_MENU_BACK_TILE)->put_screen(scr_coord);
	}
	
	scr_coord.x = config->get_base_screen_size_x()/2-148;
	scr_coord.y = 32;
	Surface_Manager::instance()->get_surface(Surface_Manager::SRF_MENU_TITLE)->put_screen(scr_coord);
	//m_background->put_screen(0,0, config->get_screen_size_x(), config->get_screen_size_y());
	
}


void Menu_Base_State::manage_input()
{
	Input* input = Input::instance();
	input->update();
    //DEBOUT("Managing input\n");
    if(m_menu_list != NULL)
    {
        //DEBOUT("m_menu_list is not null\n");
	    if(input->up().get_just_pressed())
		{

			m_menu_list->action_up();

		}
		
		if(input->down().get_just_pressed())
		{

			m_menu_list->action_down();

		}
		
		if((input->left().get_just_pressed()))
		{

			m_menu_list->action_left();

		}
		
		if((input->right().get_just_pressed()))
		{

			m_menu_list->action_right();

		}
		
		if(input->get_enter()||input->get_fire())
		{
			m_menu_list->action_press();
		}

		if(input->get_quit())
		{
			m_menu_list->action_quit();
		}
    }
}



void Menu_Base_State::render_menu_list(Menu_List* menu_list, Sint32 menu_top_point, Sint32 menu_left_point, Sint32 menu_vertical_distance)
{
	

	Screen* screen = Screen::instance();

	Font* menu_font = Font_Manager::instance()->get_font(m_menu_font); 

	Uint64 current_time=SDL_GetTicks64();

	Uint32 menu_offset_x = 10;
	
	//printing menu
	
			
	for(Uint32 i=0; i<menu_list->get_list_size(); i++)
	{
		menu_font->write(menu_left_point-50+menu_offset_x*i, menu_top_point+menu_vertical_distance*i, menu_list->get_menu_entry_string(i).c_str());
	}	
	
	
	//m_selector.update_frame();
	static Sint32 selector_y_current = 4+menu_top_point;
	static Sint32 selector_y_target = 4+menu_top_point;

	float phase = static_cast<float>(current_time) * 0.006f; // frequency
	int x_offset = static_cast<int>(4.0f * sin(phase)); // max pixels of offset

	m_selector.set_offset_x(x_offset);
	
	ScreenCoord scr_coord;
	
	scr_coord.x = menu_left_point-90 + menu_list->get_selected()*menu_offset_x;
	
	selector_y_target = 4+menu_top_point+menu_list->get_selected()*menu_vertical_distance;
	
	if(abs(selector_y_current - selector_y_target) > 4 )
	{
		selector_y_current += (selector_y_target-selector_y_current)/3; 
	}
	else
	{
		selector_y_current = selector_y_target;
	}
	scr_coord.y = selector_y_current;
	
	m_selector.set_position_on_screen(scr_coord);
	
	m_selector.draw();
	
//	m_selector.put_screen(scr_coord);


	
}