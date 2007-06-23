#ifndef MENU_ENTRY_RANGED_H_
#define MENU_ENTRY_RANGED_H_

#include "menu_entry.h"

class Menu_Entry_Ranged : public Menu_Entry
{

	protected:
	
		Uint32 m_range_begin;
	
		Uint32 m_range_end;
		
		Uint32 m_current_value;
		
		std::string m_string;
	
	public:

		Menu_Entry_Ranged(Uint32 range_begin, Uint32 range_end):
																m_range_begin(range_begin), 
																m_range_end(range_end), 
																m_current_value(range_begin)
																{};
																
		Menu_Entry_Ranged(Uint32 range_begin, Uint32 range_end, const char* string):
																m_range_begin(range_begin), 
																m_range_end(range_end), 
																m_current_value(range_begin),
																m_string(string)
																{};
	
		void set_current_value(Uint32 current_value);
	
		const char* get_string();
	
		void set_string(const char* string);
	
		void action_left();
	
		void action_right();
	
		void action_up(){};
	
		void action_down(){};
	
		void action_press(){};
	
		~Menu_Entry_Ranged(){};		
	
};

#endif /*MENU_ENTRY_RANGED_H_*/
