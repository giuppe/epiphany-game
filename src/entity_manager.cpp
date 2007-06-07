#include <cassert>
#include "entity_manager.h"
#include "entity.h"


void Entity_Manager::init()
{
	//FIXME: it should create an empty entity 
    Entity* e;
    m_entities.push_back(e);
}

Entity_Handle Entity_Manager::add_entity(Entity* entity)
{
    Entity_Handle e_h = m_entities.size();
    m_entities.push_back(entity);
    return e_h;
}

Entity* Entity_Manager::get_entity(Entity_Handle entity_handle)
{
	assert(entity_handle<m_entities.size());
	
        return m_entities[entity_handle];
}

Entity_Manager* Entity_Manager::_instance = 0;

Entity_Manager* Entity_Manager::instance()
{
	if(_instance==0)
	{
		_instance=new Entity_Manager();
		_instance->init();
	}
	return _instance;
}
