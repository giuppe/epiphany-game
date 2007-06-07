#ifndef ENTITY_MANAGER_H_
#define ENTITY_MANAGER_H_

#include <vector>
#include <string>

class Entity;

typedef unsigned int Entity_Handle;

class Entity_Manager
{
private:
	std::vector<Entity*> m_entities;
	void init();

	
public:
	
	Entity* get_entity(Entity_Handle handle);
	
	Entity_Handle add_entity(Entity* entity);
	
	int size(){return m_entities.size();}
	
	void reset();
	
	    // begin Singleton stuff

private:

    static Entity_Manager* _instance;

protected:

    Entity_Manager(){};

public:

    static Entity_Manager* instance();

// end Singleton stuff
	
};
	

#endif /*ENTITY_MANAGER_H_*/
