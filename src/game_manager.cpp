
#include "game_manager.h"
#include "sfx.h"
#include "music_manager.h"
#include "surface_manager.h"
#include "screen.h"
#include "resource_factory.h"
#include <cassert>

void GameManager::init()
{

	DEBOUT("Entering Game::init()...\n");

	m_game = new Game();
	//m_game->init();

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
	
	
	DEBOUT("Loading fonts...\n");
	m_game->load_fonts();
	

	
}


Uint32 GameManager::find_levels_in_dir()
{
	Uint32 result = 0;
	char base_path[255];
	char level_path[255];
	
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

void GameManager::save_config()
{
	Epiconfig::instance()->save_values_to_file(m_ini_path);
}

void GameManager::change_state(ScreenState* new_state)
{
	m_current_state = new_state;
}

void GameManager::return_to_system()
{
	m_current_state = NULL;
}

void GameManager::go()
{
	m_game->go();

	if(m_current_state != NULL)
	{
		m_current_state->create();
	}

	Screen* screen = Screen::instance();

	while(m_current_state != NULL)
	{
		Sint32 current_frame_time=0;
		current_frame_time=SDL_GetTicks();

		ScreenState* temp_state = m_current_state;
		
		temp_state->update(0);

		temp_state->draw();

		while(SDL_GetTicks()-current_frame_time<20)
		{
			if(SDL_GetTicks()-current_frame_time<15)
			{
				SDL_Delay(5);
			}
		}
		screen->flip_display();
		screen->clear();
	}
	

}

void GameManager::play_level(const char* level)
{
	m_game->play_level(level);
}




// singleton stuff

GameManager* GameManager::_instance = 0;

GameManager* GameManager::instance()
{
	if(_instance==0)
	{
		_instance=new GameManager();
		_instance->init();

	}
	return _instance;
}