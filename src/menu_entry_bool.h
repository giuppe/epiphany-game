#ifndef MENU_ENTRY_BOOL_H_
#define MENU_ENTRY_BOOL_H_

#include "menu_entry.h"
#include <string>

class Menu_Entry_Bool : public Menu_Entry
{

	protected:
	
		std::string m_string;
	
		Uint32 m_current_value;
		
	
	public:

		Menu_Entry_Bool(const char* string):
						m_string(string),
						m_current_value(0)
						{};
																
		Menu_Entry_Bool(const char* string, Uint32 current_value):
																m_string(string),
																m_current_value(current_value)
																{};
	
		void set_current_value(Uint32 current_value);
		
		Uint32 get_value(){return m_current_value;}
	
		const char* get_string();
	
		void set_string(const char* string){m_string = string;}
	
		void action_left(){};
	
		void action_right(){};
	
		void action_up(){};
	
		void action_down(){};
	
		void action_press();
	
		~Menu_Entry_Bool(){};		
	
};

#endif /*MENU_ENTRY_BOOL_H_*/
