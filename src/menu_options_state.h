#include "dephine.h"

#include "menu_base_state.h"

#ifndef MENU_OPTIONS_STATE_H
#define MENU_OPTIONS_STATE_H

class Menu_List;

class Menu_Options_State : public Menu_Base_State
{
   

    public:

        Menu_Options_State();

        ~Menu_Options_State();

        void create();

        void update(double elapsed);

        void deinit();

        void draw();
};

#endif //MENU_OPTIONS_STATE_H