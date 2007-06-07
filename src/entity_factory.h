#ifndef ENTITY_FACTORY_H_
#define ENTITY_FACTORY_H_
#include "entity_type.h"
//#include "entity.h"
#include "spriteset.h"

class Entity;
class Level;

//typedef unsigned int Entity_Type;

class Entity_Factory
{
public:
/*	enum {		UNKNOWN=0,
			PLAYER=1,
			GRASS=2,
			STEEL=3,
			EMERALD=4,
			BOULDER=5,
			SAPPHIRE=6,
			EXIT=7,
			EXPLOSION=8,
			DOOR=9,
			DOOR_RED=9,
			DOOR_BLUE=10,
			DOOR_GREEN=11,
			DOOR_YELLOW=12,
			KEY=13,
			KEY_RED=13,
			KEY_BLUE=14,
			KEY_GREEN=15,
			KEY_YELLOW=16,
			FLINTSTONE=17,
			PEPERON=18,
			PEPERON_UP=PEPERON+UP,
			PEPERON_RIGHT=PEPERON+RIGHT,
			PEPERON_DOWN=PEPERON+DOWN,
			PEPERON_LEFT=PEPERON+LEFT,
			BRICK=19,
			WOOD=20,
			TOMATO=21,
			TOMATO_UP=TOMATO+UP,
			TOMATO_RIGHT=TOMATO+RIGHT,
			TOMATO_DOWN=TOMATO+DOWN,
			TOMATO_LEFT=TOMATO+LEFT
	};
*/
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
