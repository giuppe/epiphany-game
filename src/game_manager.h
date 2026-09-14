
/***************************************************************************
                        game_manager.h  -  
                             -------------------
    begin                : Sep 02 2026
    copyright            : (C) 2026 by Giuseppe D'Aqui'
    email                : kumber@tiscalinet.it
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License, Version 2,      *
 *   as published by the Free Software Foundation.                         *
 *                                                                         *
 ***************************************************************************/

#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "dephine.h"
#include "game.h"
#include "epiconfig.h"
#include "screen_state.h"

class Game_Manager 
{
    private:

        Epiconfig* m_config;
        
        char m_ini_path[255];

        ScreenState* m_current_state = NULL;

        ScreenState* m_incoming_state = NULL;

        bool m_current_state_just_created = false;

        ScreenState* m_state_to_delete_next = NULL;

        Uint32 m_fps_last_second = 0;
        Uint32 m_fps_fixed_last_second = 0;

    public:

        Uint32 find_levels_in_dir();

        void init();

        void go();

        void change_state(ScreenState* new_state);

        void return_to_system();

        void kill_game();
        
        void save_config();

        Uint32 get_fps_last_second(){return m_fps_last_second;}

        Uint32 get_fps_fixed_last_second(){return m_fps_fixed_last_second;}


    // singleton stuff
    private:

	    static Game_Manager* _instance;

    protected:

        Game_Manager(){};

    public:

        static Game_Manager* instance();
};

#endif //GAME_MANAGER_H