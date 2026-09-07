#include "dephine.h"

#include "menu_base_state.h"

#ifndef MENU_STATE_INGAME_OPTIONS_H
#define MENU_STATE_INGAME_OPTIONS_H

class Menu_List;

class Menu_State_Ingame_Options : public Menu_Base_State
{
    protected:
        void print_menu_background();

    public:

        Menu_State_Ingame_Options();

        ~Menu_State_Ingame_Options();

        void create();

        void update(double elapsed);

        void deinit();

        void draw();
};

#endif //MENU_STATE_INGAME_OPTIONS_H