#include "dephine.h"
#include "menu_list.h"
#include "menu_entry.h"
#include <vector>

#ifndef MENU_LIST_EPIPHANY_H_
#define MENU_LIST_EPIPHANY_H_

class Menu_List_Epiphany : public Menu_List
{
private:

	std::vector<Menu_Entry*> m_entries_list;
	
	Uint32 m_return_action;
	
public:
	enum{
		MENU_NONE,
		MENU_START,
		MENU_OPTIONS,
		MENU_QUIT
	};
	
	Menu_List_Epiphany(Uint32 unsolved_level);
	
	~Menu_List_Epiphany();
	
	Uint32 get_selected_level();
	
	Uint32 get_return_action();
	
	void action_left();
	
	void action_right();
	
	void action_up();
	
	void action_down();
	
	void action_press();
	
	Uint32 get_list_size();
	
	const char* get_menu_entry_string(Uint32 entry);
	
};

#endif /*MENU_LIST_EPIPHANY_H_*/
