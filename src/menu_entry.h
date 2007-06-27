#ifndef MENU_ENTRY_H_
#define MENU_ENTRY_H_

#include "dephine.h"

class Menu_Entry
{
protected:
	
//	std::string m_string;

public:

	Menu_Entry(){};
	
	virtual const char* get_string() = 0;
	
//	virtual void set_string(const char* string) = 0;
	
	virtual void action_left() = 0;
	
	virtual void action_right() = 0;
	
	virtual void action_up() = 0;
	
	virtual void action_down() = 0;
	
	virtual void action_press() = 0;
	
	virtual Uint32 get_value() = 0;
	
	virtual ~Menu_Entry(){};		
	
};

#endif /*MENU_ENTRY_H_*/
