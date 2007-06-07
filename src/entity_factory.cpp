#include "entity_factory.h"
//#include "entity_blank.h"
#include "entity_all.h"

#include "level.h"

//FIXME: remove *any* reference to Level

Entity* Entity_Factory::create_entity(Entity_Type type, Level* level)
{
	//DEBOUT(type<<"\n");
	Entity* entity;
	
	unsigned int x=1;
	unsigned int y = 1;
	DEBOUT("Creating entity of type:"<<type<<"\n");
	switch(type)
	{
	case UNKNOWN:
		entity = new Entity_Unknown();
		break;
	case PLAYER:
		entity=new Entity_Player(level,x,y,m_spriteset.get_sprite(PLAYER));
		//set_entity(m_player);
		DEBOUT("Setting player...\n");
		break;
	case GRASS:
		entity=new Entity_Grass(level,x,y,m_spriteset.get_sprite(GRASS));
		break;
	case STEEL:
		entity=new Entity_Steel(level,x,y,m_spriteset.get_sprite(STEEL));
		break;
	case EMERALD:
		entity=new Entity_Emerald(level,x,y,m_spriteset.get_sprite(EMERALD));
		break;
	case BOULDER:
		entity=new Entity_Boulder(level,x,y,m_spriteset.get_sprite(BOULDER));
		break;
	case SAPPHIRE:
		entity=new Entity_Sapphire(level,x,y,m_spriteset.get_sprite(SAPPHIRE));
		break;
	case EXIT:
		entity=new Entity_Exit(level,x,y,m_spriteset.get_sprite(EXIT),1);
		//set_entity(m_exit);
		DEBOUT("Setting Exit...\n");
		break;
	case DOOR_RED:
		entity=new Entity_Door(level,x,y,m_spriteset.get_sprite(DOOR),1);
		break;
	case DOOR_BLUE:
		entity=new Entity_Door(level,x,y,m_spriteset.get_sprite(DOOR),2);
		break;
	case DOOR_GREEN:
		entity=new Entity_Door(level,x,y,m_spriteset.get_sprite(DOOR),4);
		break;
	case DOOR_YELLOW:
		entity=new Entity_Door(level,x,y,m_spriteset.get_sprite(DOOR),8);
		break;
	case KEY_RED:
		entity=new Entity_Key(level,x,y,m_spriteset.get_sprite(KEY),1);
		break;
	case KEY_BLUE:
		entity=new Entity_Key(level,x,y,m_spriteset.get_sprite(KEY),2);
		break;
	case KEY_GREEN:
		entity=new Entity_Key(level,x,y,m_spriteset.get_sprite(KEY),4);
		break;
	case KEY_YELLOW:
		entity=new Entity_Key(level,x,y,m_spriteset.get_sprite(KEY),8);
		break;
	case FLINTSTONE:
		entity=new Entity_Flintstone(level,x,y,m_spriteset.get_sprite(FLINTSTONE));
		break;
	case PEPERON_UP:
		entity=new Entity_Peperon(level,x,y,m_spriteset.get_sprite(PEPERON),UP);
		break;
	case PEPERON_RIGHT:
		entity=new Entity_Peperon(level,x,y,m_spriteset.get_sprite(PEPERON),RIGHT);
		break;
	case PEPERON_DOWN:
		entity=new Entity_Peperon(level,x,y,m_spriteset.get_sprite(PEPERON),DOWN);
		break;
	case PEPERON_LEFT:
		entity=new Entity_Peperon(level,x,y,m_spriteset.get_sprite(PEPERON),LEFT);
		break;
	case BRICK:
		entity=new Entity_Brick(level,x,y,m_spriteset.get_sprite(BRICK));
		break;
	case WOOD:
		entity=new Entity_Wood(level,x,y,m_spriteset.get_sprite(WOOD));
		break;
	case TOMATO_UP:
		entity=new Entity_Tomato(level,x,y,m_spriteset.get_sprite(TOMATO),UP);
		break;
	case TOMATO_RIGHT:
		entity=new Entity_Tomato(level,x,y,m_spriteset.get_sprite(TOMATO),RIGHT);
		break;
	case TOMATO_DOWN:
		entity=new Entity_Tomato(level,x,y,m_spriteset.get_sprite(TOMATO),DOWN);
		break;
	case TOMATO_LEFT:
		entity=new Entity_Tomato(level,x,y,m_spriteset.get_sprite(TOMATO),LEFT);
		break;
	case EXPLOSION:
		//FIXME add explosion
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
