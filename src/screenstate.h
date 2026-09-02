/***************************************************************************
    screenstate.h  -  basic game state screen (e.g. menu, credits, etc.)
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


#ifndef SCREENSTATE_H
#define SCREENSTATE_H

class ScreenState
{

    virtual void create() = 0;

    virtual void update(double elapsed) = 0;

    virtual void deinit() = 0;
};

#endif //SCREENSTATE_H