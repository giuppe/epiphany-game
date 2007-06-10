#ifndef ENTITY_FACTORY_H_
#define ENTITY_FACTORY_H_
#include "entity_type.h"
//#include "entity.h"
#include "spriteset.h"

class Entity;
class Level;


class Entity_Factory
{
private:

	Spriteset m_spriteset;

public:

	Entity* create_entity(Entity_Type type, Level* level);

	void set_spriteset(Spriteset& spriteset){m_spriteset = spriteset;}

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
