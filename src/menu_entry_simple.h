#ifndef MENU_ENTRY_SIMPLE_H_
#define MENU_ENTRY_SIMPLE_H_

#include "menu_entry.h"

class Menu_Entry_Simple : public Menu_Entry
{
	protected:
		std::string m_string;
		
	public:
		Menu_Entry_Simple(){};
	
		Menu_Entry_Simple(const char* string):m_string(string){};
	
		const char* get_string(){return m_string.c_str();};
	
		void set_string(const char* string){m_string = string;};
		
		Uint32 get_value(){ return 0;}
	
		void action_left(){};
	
		void action_right(){};
	
		void action_up(){};
	
		void action_down(){};
	
		void action_press(){};
	
		~Menu_Entry_Simple(){};		
	
};

#endif /*MENU_ENTRY_SIMPLE_H_*/
