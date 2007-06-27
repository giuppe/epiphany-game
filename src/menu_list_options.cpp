#include "dephine.h"
#include "menu_list_options.h"
#include "menu_entry.h"
#include "menu_entry_simple.h"
#include "menu_entry_ranged.h"
#include "sfx.h"
#include <vector>
#include <cassert>




Menu_List_Options::Menu_List_Options()
{
	m_return_action = Menu_List_Options::MENU_NONE;
	
	m_selected = 0;
	
	m_entries_list.push_back(new Menu_Entry_Ranged(0, 128, "Sound Volume: ", Sample_Manager::instance()->get_volume()));
	
	//TODO insert music volume control
	m_entries_list.push_back(new Menu_Entry_Ranged(0, 128, "Music Volume: ", 0));
	
	m_entries_list.push_back(new Menu_Entry_Simple("Back"));
	
}




Menu_List_Options::~Menu_List_Options()
{
	for(Uint32 i=0; i<m_entries_list.size(); i++)
	{
		delete m_entries_list[i];
	}
}




void Menu_List_Options::action_press()
{
	m_entries_list[m_selected]->action_press();
	
	switch(m_selected)
	{
		case 2:
			m_return_action = MENU_OK;
			Sample_Manager::instance()->set_volume(m_entries_list[0]->get_value());
			break;
		default:
			m_return_action = MENU_NONE;
	}
	
}




void Menu_List_Options::action_down()
{
	
	if(m_selected<m_entries_list.size()-1)
	{

		m_selected++;

	}

}




void Menu_List_Options::action_up()
{
	
	if(m_selected>0)
	{

		m_selected--;

	}

}




void Menu_List_Options::action_right()
{
	m_entries_list[m_selected]->action_right();
}




void Menu_List_Options::action_left()
{
	m_entries_list[m_selected]->action_left();
}




const char* Menu_List_Options::get_menu_entry_string(Uint32 entry)
{
	assert(entry<m_entries_list.size() && "Fatal: Accessing menu_entry outside limits");

	return m_entries_list[entry]->get_string();
}




Uint32 Menu_List_Options::get_list_size()
{
	return m_entries_list.size();
		
}




Uint32 Menu_List_Options::get_return_action()
{
	return m_return_action;
}


