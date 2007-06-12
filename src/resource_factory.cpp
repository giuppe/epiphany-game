#include "resource_factory.h"
#include "dephine.h"



void Resource_Factory::init()
{
	//portability "quick hack" :)
	#ifdef _WIN32
	m_resource_path=".";
	#else
	m_resource_path= RESOURCE_PATH;
	#endif
	DEBOUT("Resource_path: "<<m_resource_path<<"\n");

	try
	{
		m_res_manager=new CL_ResourceManager(CL_String(m_resource_path)+"/sprites.scr", false);
	}
	catch(CL_Error ex)
	{
		std::cout<<ex.message<<"\n";
		m_resource_path="./data";

		try
		{
			m_res_manager=new CL_ResourceManager(CL_String(m_resource_path)+"/sprites.scr", false);
		}
		catch(CL_Error ex)
		{
			throw Common_Ex(ex.message.c_str() );
			m_resource_path="../data";

			try
			{
				m_res_manager=new CL_ResourceManager(CL_String(m_resource_path)+"/sprites.scr", false);
			}
			catch(CL_Error ex)
			{
				throw Common_Ex(ex.message.c_str());
				exit(1);
			}
		}
	}
	DEBOUT("Using "<<m_resource_path<<"/sprites.scr"<<" as resource script.\n");
}

void Resource_Factory::deinit()
{
	delete m_res_manager;
}

// begin Singleton stuff

Resource_Factory* Resource_Factory::_instance = 0;

Resource_Factory* Resource_Factory::instance()
{
	if (_instance == 0)
	{
		_instance = new Resource_Factory();
		_instance->init();
	}
	return _instance;
}

//end Singleton stuff