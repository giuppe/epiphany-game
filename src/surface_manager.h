#ifndef SURFACE_MANAGER_H_
#define SURFACE_MANAGER_H_

#include "dephine.h"

typedef CL_Surface Surface;

#include <vector>

typedef unsigned int Surface_Handle;

class Surface_Manager
{
private:
    std::vector <Surface*> m_surfaces;
public:

    Surface* get_surface(Surface_Handle handle);

    // Since all surfaces in game should be inited and flushed by Surface_Manager
    // We do not support loading images by others
	void add_surface(Surface_Handle handle, Surface* surface);

    Surface_Handle load_surface(string path);

    // this should free all surfaces
    void deinit();


    // begin Singleton stuff

private:

    static Surface_Manager* _instance;

protected:

    Surface_Manager(){};

public:

    static Surface_Manager* instance();

// end Singleton stuff

};

#endif /*SURFACE_MANAGER_H_*/
