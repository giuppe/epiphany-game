#include "surface_manager.h"
#include "game.h"
#include <cassert>

Surface_Handle Surface_Manager::load_surface(string path)
{
    Surface_Handle s_h = m_surfaces.size();
    
    CL_ResourceManager* res_manag=Game::instance()->get_resource_manager();

    CL_Surface* temp = new CL_Surface(path, res_manag);
                     
    m_surfaces.push_back(temp);
    return s_h;
}

void Surface_Manager::add_surface(Surface_Handle handle, Surface* surface)
{
    //Surface_Handle s_h = m_surfaces.size();
                        
    m_surfaces[handle]=surface;

}

Surface* Surface_Manager::get_surface(Surface_Handle surface_handle)
{
    if(surface_handle<m_surfaces.size())
    {
        return m_surfaces[surface_handle];
    }
    assert(!"Error: Trying to access a non-initialized surface");
}

void Surface_Manager::deinit()
{
    DEBOUT("\n\tFlushing all surfaces... ");
    for(unsigned int i=0; i < m_surfaces.size(); i++)
    {
        delete m_surfaces[i];
    }

    DEBOUT("done.\n");
}

// begin Singleton stuff

Surface_Manager* Surface_Manager::_instance = 0;

Surface_Manager* Surface_Manager::instance()
{
	if (_instance == 0)
	{
		_instance = new Surface_Manager();
		//FIXME: this is for enabling random adding of surfaces
		_instance->m_surfaces.resize(40);
	}
	return _instance;
}

//end Singleton stuff
