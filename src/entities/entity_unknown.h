
#include "entity.h"

#ifndef ENTITY_UNKNOWN_H_
#define ENTITY_UNKNOWN_H_


class Entity_Unknown:public Entity
{
public:	

	Entity_Unknown(){};

	
	//it does nothing: its check_and_do is empty.
	void check_and_do(){}	

	bool hit_from_up(Entity_Handle){return false;};
	
	bool explode(){return false;};
	
	bool roll_on_me(){return false;};
	
};
#endif /*ENTITY_UNKNOWN_H_*/
