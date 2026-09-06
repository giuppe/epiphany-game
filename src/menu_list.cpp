#include "menu_list.h"

#include "menu_entry.h"

void Menu_List::action_press()
{
	
	m_entries_list[m_selected]->action_press();

}

void Menu_List::action_down()
{
	
	if(m_selected<m_entries_list.size()-1)
	{

		m_selected++;

	}

}




void Menu_List::action_up()
{
	
	if(m_selected>0)
	{

		m_selected--;

	}

}


void Menu_List::action_right()
{
	m_entries_list[m_selected]->action_right();
}




void Menu_List::action_left()
{
	m_entries_list[m_selected]->action_left();
}

