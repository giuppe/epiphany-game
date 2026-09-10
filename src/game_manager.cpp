
#include "game_manager.h"
#include "sfx.h"
#include "music_manager.h"
#include "surface_manager.h"
#include "screen.h"
#include "resource_factory.h"
#include "menu_state.h"
#include <cassert>

void Game_Manager::init()
{

	DEBOUT("Entering Game::init()...\n");

	
	DEBOUT("Loading default configuration values...\n");
	
	m_config = Epiconfig::instance();
	
	m_config->set_frame_limiter_enabled(true);
	
	m_config->set_frame_skip(0);
	
	#ifdef _WIN32
	sprintf(m_ini_path, "%s", "./epiphany.ini");
	#else
	std::string user_home(getenv("HOME"));
	if(user_home=="")
	{
		assert(!"Unable to find HOME environment variable");
	}
	else
	{
		user_home+="/.epiphany";
		sprintf(m_ini_path, "%s", user_home.c_str());
	}
	#endif


	m_config->read_values_from_file(m_ini_path);

	Sample_Manager::instance()->set_volume(m_config->get_volume_sound());
	
	Music_Manager::instance()->set_volume(m_config->get_volume_music());
	
	
	
	DEBOUT("Initing Screen...\n");
	Screen::instance()->init(m_config->get_screen_size_x(),m_config->get_screen_size_y(),m_config->get_map_size_x()*k_sprite_size, m_config->get_map_size_y()*k_sprite_size);
	
	Screen::instance()->set_fullscreen(m_config->get_fullscreen());
	
	DEBOUT("Initing Surface Manager...\n");
	Surface_Manager::instance();
	
	
	

	
}


Uint32 Game_Manager::find_levels_in_dir()
{
	Uint32 result = 0;
	char base_path[255];
	char level_path[300];
	
	sprintf(base_path, "%s%s", Resource_Factory::instance()->get_resource_path().c_str(), "/maps/level");
	
	sprintf(level_path, "%s%d%s", base_path, result, ".map");
	FILE* pFile = fopen (level_path,"r");
	while(pFile != NULL)
	{
		DEBOUT("Found "<<level_path<<".\n");
		fclose(pFile);
		result++;
		sprintf(level_path, "%s%d%s", base_path, result, ".map");
		pFile = fopen (level_path,"r");
	}
	return result;
}

void Game_Manager::save_config()
{
	Epiconfig::instance()->save_values_to_file(m_ini_path);
}

void Game_Manager::change_state(ScreenState* new_state)
{
	m_current_state = new_state;
	m_current_state_just_created = true;
}

void Game_Manager::return_to_system()
{
	m_current_state = NULL;
}

void Game_Manager::kill_game()
{
	if(m_current_state != NULL)
	{
		m_current_state->deinit();
		m_state_to_delete_next = m_current_state;
		m_current_state = NULL;
	}
	this->change_state(new Menu_State());
}

void Game_Manager::go()
{
	Screen* screen = Screen::instance();
	Uint64 current_frame_time=SDL_GetTicks64();
	Uint64 accumulator = 0;
	const Uint32 dt = 1000.0 / 6.0;

	while(m_current_state != NULL)
	{

		if(m_current_state_just_created)
		{
			m_current_state->create();
			m_current_state_just_created = false;
		}

		ScreenState* temp_state = m_current_state;

		Uint64 new_time = SDL_GetTicks64();
		Uint64 frame_time = new_time - current_frame_time;
		current_frame_time = new_time;

		accumulator += frame_time;

		//DEBWARN("accumulator "<<accumulator<<"\n");

		while (accumulator >= dt) {
			temp_state->update_fixed_all(dt);
			accumulator -= dt;
		}


		temp_state->update_all((double)(frame_time/1000.0));

		temp_state->draw_all();

		while(SDL_GetTicks64()-current_frame_time<20)
		{
			if(SDL_GetTicks64()-current_frame_time<15)
			{
				SDL_Delay(5);
			}
		}
		screen->flip_display();
		screen->clear();

		if(m_state_to_delete_next != NULL)
		{
			delete m_state_to_delete_next;
			m_state_to_delete_next = NULL;
		}
	}
	

}






// singleton stuff

Game_Manager* Game_Manager::_instance = 0;

Game_Manager* Game_Manager::instance()
{
	if(_instance==0)
	{
		_instance=new Game_Manager();
		_instance->init();

	}
	return _instance;
}