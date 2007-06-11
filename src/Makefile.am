#SUBDIRS = entities
LDADD = -lclanSound -lclanDisplay -lclanApp -lclanCore

bin_PROGRAMS = epiphany

epiphany_SOURCES = sfx.cpp main.cpp level.cpp sample.cpp entity.cpp \
	levelmap.cpp epiconfig.cpp entity_factory.cpp entity_manager.cpp \
	spriteset.cpp game_timer.cpp myparser.cpp epimap.cpp emdlparser.cpp \
	entities/entity_gem.cpp entities/entity_door.cpp  entities/entity_wood.cpp 			\
         entities/entity_brick.cpp  entities/entity_player.cpp  entities/entity_falling.cpp 		\
	 entities/entity_emerald.cpp  entities/entity_peperon.cpp  entities/entity_sapphire.cpp 	\
	 entities/entity_flintstone.cpp  entities/entity_explosion.cpp  entities/entity_monster.cpp 	\
	 entities/entity_boulder.cpp  entities/entity_tomato.cpp				\
         entities/entity_steel.cpp  entities/entity_grass.cpp  entities/entity_exit.cpp  entities/entity_key.cpp \
	screen.cpp sprite.cpp menu.cpp game.cpp surface_manager.cpp input.cpp fonts/font.cpp \
	fonts/font_factory.cpp fonts/font_manager.cpp surface.cpp surface_factory.cpp

EXTRA_DISTS = entities/Makefile.am