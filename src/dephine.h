/***********************************************
** ------------------------------------------ **
** ------ Standard Definitions Header ------- **
** ------------------------------------------ **
** ------------- Version 1.1 ---------------- **
** ------------------------------------------ **
***********************************************/

#ifndef DEPHINE_H
#define DEPHINE_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#ifdef DEBUG_MODE

//Standard includes needed by DebugMode
#include <iostream>
#include <fstream>

#define DEBUG(x) {x;}
#define DEBOUT(x) {cout<<x;}
#else
#define DEBUG(x)
#define DEBOUT(x)

#endif  // DEBUG_MODE

//Insert standard includes here (used by all files)
#include <ClanLib/core.h>
#include <ClanLib/application.h>
#include <ClanLib/display.h>
#include <ClanLib/sound.h>
#include "except.h"
#include "epiconfig.h"



/**************************************************/
/*                  Game Constants                */
/**************************************************/
//const unsigned int k_max_num_of_levels=13;
 /*
//size in pixels
//const unsigned int k_game_size_x=640;
//const unsigned int k_game_size_y=480;
//const unsigned int k_score_size_y=32;

//size in cells
const static int k_level_size_x=32;
const static int k_level_size_y=32;

const unsigned int k_max_anim_drawn=8;
*/
const unsigned int k_max_anim=8;
const int k_sprite_size=32;
/*
const unsigned int k_moving_step=k_sprite_size/k_max_anim_drawn;

//const unsigned int k_msec_per_frame=176/k_max_anim_drawn;
//const unsigned int k_msec_per_frame=150/k_max_anim_drawn;
*/ 

#endif  // DEPHINE_H

