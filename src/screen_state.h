/***************************************************************************
    screen_state.h  -  basic game state screen (e.g. menu, credits, etc.)
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

#include "dephine.h"

#ifndef SCREENSTATE_H
#define SCREENSTATE_H

class ScreenState
{
    private:
        bool m_persistent_update = false;
        bool m_persistent_draw = false;
        
        bool m_kill_substate_next = false;
        ScreenState* m_substate_to_launch = NULL;
        void real_kill_substate_();
        void real_launch_substate_();

    protected:
        ScreenState* m_parent = NULL;
        ScreenState* m_substate = NULL;
        

        void set_parent(ScreenState* parent);

    public:
        virtual ~ScreenState();

        virtual void create() = 0;

        virtual void update(double elapsed) = 0;

        virtual void deinit() = 0;

        virtual void draw() = 0;

        virtual void update_fixed(Uint64 elapsed){};

        void update_all(double elapsed);

        void update_fixed_all(Uint64 elapsed);

        void draw_all();

        void kill_substate();

        void close();

        void launch_substate(ScreenState* substate);

        void set_persistent_update(bool persistent_update){m_persistent_update = persistent_update;}

        void set_persistent_draw(bool persistent_draw){m_persistent_draw = persistent_draw;}
};

#endif //SCREENSTATE_H