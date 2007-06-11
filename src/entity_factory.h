#ifndef ENTITY_FACTORY_H_
#define ENTITY_FACTORY_H_
#include "entity_type.h"


class Entity;
class Level;


class Entity_Factory
{
private:

public:

	Entity* create_entity(Entity_Type type, Level* level);


// begin Singleton stuff

private:

	static Entity_Factory* _instance;

protected:

	Entity_Factory(){};

public:

	static Entity_Factory* instance();

// end Singleton stuff

};

#endif /*ENTITY_FACTORY_H_*/
