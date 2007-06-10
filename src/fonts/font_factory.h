#ifndef FONT_FACTORY_H_
#define FONT_FACTORY_H_

#include "resource_manager.h"

class Font;



class Font_Factory
{
private:

	Resource_Manager* m_res_manager;
	
public:

	enum Font_Type
	{
		MENU_FONT,
		GAME_FONT,
		CREDITS_FONT,
		TIME_FONT
	};


	Font* create_font(Font_Type type);

	void set_resource_manager(Resource_Manager* res_manager){m_res_manager=res_manager;};

// begin Singleton stuff

private:

	static Font_Factory* _instance;

protected:

	Font_Factory(){};

public:

	static Font_Factory* instance();

// end Singleton stuff

};

#endif /*FONT_FACTORY_H_*/
