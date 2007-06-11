#include "entity_factory.h"
//#include "entity_blank.h"
#include "entity_all.h"

#include "level.h"

//FIXME: remove *any* reference to Level

Entity* Entity_Factory::create_entity(Entity_Type type, Level* level)
{
	//DEBOUT(type<<"\n");
	Entity* entity;
	
	Uint32 x=1;
	Uint32 y = 1;
	DEBOUT("Creating entity of type:"<<type<<"\n");
	switch(type)
	{
	case UNKNOWN:
		entity = new Entity_Unknown();
		break;
	case PLAYER:
		entity=new Entity_Player(level,x,y);
		//set_entity(m_player);
		DEBOUT("Setting player...\n");
		break;
	case GRASS:
		entity=new Entity_Grass(level,x,y);
		break;
	case STEEL:
		entity=new Entity_Steel(level,x,y);
		break;
	case EMERALD:
		entity=new Entity_Emerald(level,x,y);
		break;
	case BOULDER:
		entity=new Entity_Boulder(level,x,y);
		break;
	case SAPPHIRE:
		entity=new Entity_Sapphire(level,x,y);
		break;
	case EXIT:
		entity=new Entity_Exit(level,x,y,1);
		//set_entity(m_exit);
		DEBOUT("Setting Exit...\n");
		break;
	case DOOR_RED:
		entity=new Entity_Door(level,x,y,1);
		break;
	case DOOR_BLUE:
		entity=new Entity_Door(level,x,y,2);
		break;
	case DOOR_GREEN:
		entity=new Entity_Door(level,x,y,4);
		break;
	case DOOR_YELLOW:
		entity=new Entity_Door(level,x,y,8);
		break;
	case KEY_RED:
		entity=new Entity_Key(level,x,y,1);
		break;
	case KEY_BLUE:
		entity=new Entity_Key(level,x,y,2);
		break;
	case KEY_GREEN:
		entity=new Entity_Key(level,x,y,4);
		break;
	case KEY_YELLOW:
		entity=new Entity_Key(level,x,y,8);
		break;
	case FLINTSTONE:
		entity=new Entity_Flintstone(level,x,y);
		break;
	case PEPERON_UP:
		entity=new Entity_Peperon(level,x,y,UP);
		break;
	case PEPERON_RIGHT:
		entity=new Entity_Peperon(level,x,y,RIGHT);
		break;
	case PEPERON_DOWN:
		entity=new Entity_Peperon(level,x,y,DOWN);
		break;
	case PEPERON_LEFT:
		entity=new Entity_Peperon(level,x,y,LEFT);
		break;
	case BRICK:
		entity=new Entity_Brick(level,x,y);
		break;
	case WOOD:
		entity=new Entity_Wood(level,x,y);
		break;
	case TOMATO_UP:
		entity=new Entity_Tomato(level,x,y,UP);
		break;
	case TOMATO_RIGHT:
		entity=new Entity_Tomato(level,x,y,RIGHT);
		break;
	case TOMATO_DOWN:
		entity=new Entity_Tomato(level,x,y,DOWN);
		break;
	case TOMATO_LEFT:
		entity=new Entity_Tomato(level,x,y,LEFT);
		break;
	case EXPLOSION:
		entity = new Entity_Explosion(level,x,y);
	default:
		//do nothing
		break;
	}
	return entity;
}

Entity_Factory* Entity_Factory::_instance = 0;

Entity_Factory* Entity_Factory::instance()
{
	if(_instance==0)
	{
		_instance=new Entity_Factory();
	}
	return _instance;
}
