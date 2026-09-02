
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
#include "screenstate.h"

class GameManager 
{
    private:

        Epiconfig* m_config;
        
        char m_ini_path[255];

        Game* m_game;

        ScreenState* m_current_state;

    public:

        Uint32 find_levels_in_dir();

        void init();

        void go();

        void change_state(ScreenState* new_state);

        void play_level(const char *);

        
        void save_config();


    // singleton stuff
    private:

	    static GameManager* _instance;

    protected:

        GameManager(){};

    public:

        static GameManager* instance();
};

#endif //GAME_MANAGER_H