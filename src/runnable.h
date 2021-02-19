/***************************************************************************
                          resource.h  -  description
                             -------------------
    begin                : Feb 18 2020
    copyright            : (C) 2007 by Giuseppe D'Aqui'
    email                : kumber@tiscalinet.it
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License, Version 2,      *
 *   as published by the Free Software Foundation.                         *
 *                                                                         *
 ***************************************************************************/

#ifndef RUNNABLE_H
#define RUNNABLE_H

class Runnable{
    virtual void setup() = 0;
    virtual void update(double elapsed) = 0;
    virtual void destroy() = 0;
};

#endif //RUNNABLE_H
