#include <cassert>
#include "entity_manager.h"
#include "entity.h"
#include "entities/entity_unknown.h"


void Entity_Manager::init()
{
	//FIXME: it should create an empty entity 
    Entity* e = new Entity_Unknown();
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

void Entity_Manager::reset()
{
	if(m_entities.size()>1)
	{
	// start from the beginning of the array
  vector<Entity*>::iterator itPos = m_entities.begin();
  // clear all elements from the array
  for(; itPos < m_entities.end(); itPos++)
    delete *itPos;    // free the element from memory
   // finally, clear all elements from the array
  m_entities.clear();
  
  init();
	}
	/*
	for(int i=0; i<m_entities.size(); i++)
	{
		delete m_entities[i];
	}
	m_entities.clear();
	*/
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
