#include "menu_entry_bool.h"

void Menu_Entry_Bool::action_press()
{
	if(m_current_value == 0)
		m_current_value = 1;
	else
		m_current_value = 0;
		
}

const char* Menu_Entry_Bool::get_string()
{
	if(m_current_value == 0)
	{
		return (m_string+std::string(" Off")).c_str();
	}
	
	return (m_string+std::string(" On")).c_str();
}
