#include "dephine.h"
#include "menu_entry_ranged.h"


void Menu_Entry_Ranged::set_current_value(Uint32 current_value)
{
	if((current_value>=m_range_begin)&&(current_value<=m_range_end))
	{
		m_current_value = current_value;
	}
	
}


	
const char* Menu_Entry_Ranged::get_string()
{
	std::string result(m_string);
	char value_string[255];
	sprintf(value_string, "%d", m_current_value);
	result+= value_string;
	return result.c_str();
}



	
void Menu_Entry_Ranged::set_string(const char* string)
{
	m_string = string;
}



	
void Menu_Entry_Ranged::action_left()
{
	if(m_current_value>m_range_begin) 
		m_current_value--;
}




void Menu_Entry_Ranged::action_right()
{
	if(m_current_value<m_range_end)
		 m_current_value++;
}
