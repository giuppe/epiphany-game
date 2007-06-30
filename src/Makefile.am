#SUBDIRS = entities

bin_PROGRAMS = epiphany

epiphany_SOURCES = sfx.cpp main.cpp level.cpp sample.cpp entity.cpp \
	levelmap.cpp epiconfig.cpp entity_factory.cpp entity_manager.cpp \
	game_timer.cpp myparser.cpp epimap.cpp emdlparser.cpp cmdline.cpp \
	entities/entity_gem.cpp entities/entity_door.cpp  entities/entity_wood.cpp 			\
         entities/entity_brick.cpp entities/entity_player.cpp  entities/entity_falling.cpp 		\
	 entities/entity_emerald.cpp  entities/entity_peperon.cpp  entities/entity_sapphire.cpp 	\
	 entities/entity_flintstone.cpp  entities/entity_explosion.cpp  entities/entity_monster.cpp 	\
	 entities/entity_boulder.cpp  entities/entity_tomato.cpp	fonts/SFont.c			\
         entities/entity_steel.cpp  entities/entity_grass.cpp  entities/entity_exit.cpp  entities/entity_key.cpp \
	screen.cpp sprite.cpp menu.cpp game.cpp surface_manager.cpp input.cpp fonts/font.cpp \
	fonts/font_factory.cpp fonts/font_manager.cpp surface.cpp resource_factory.cpp \
	menu_entry_ranged.cpp menu_list_epiphany.cpp menu_list_options.cpp \
	tinyxml/tinystr.cpp tinyxml/tinyxmlerror.cpp tinyxml/tinyxmlparser.cpp \
	tinyxml/tinyxml.cpp menu_entry_bool.cpp music_manager.cpp

epiphany_LDADD = -lSDL -lSDL_mixer


noinst_HEADERS = entity_type.h emdlparser.h levelmap.h \
	game.h screen.h menu.h sfx.h except.h level.h entity_factory.h \
	fonts/font_manager.h fonts/font_factory.h fonts/font.h fonts/SFont.h \
	input.h sample.h myparser.h epiconfig.h entity_all.h resource.h \
	game_timer.h map_editor.h entity_manager.h direction.h \
	surface_manager.h surface.h dephine.h entities/entity_explosion.h \
	entities/entity_boulder.h entities/entity_wood.h entities/entity_exit.h \
	entities/entity_steel.h entities/entity_key.h entities/entity_sapphire.h \
	entities/entity_unknown.h entities/entity_flintstone.h entities/entity_falling.h \
	entities/entity_grass.h entities/entity_monster.h entities/entity_peperon.h \
	entities/entity_player.h entities/entity_brick.h entities/entity_door.h \
	entities/entity_gem.h entities/entity_emerald.h entities/entity_tomato.h \
	resource_factory.h sprite.h epimap.h entity.h cmdline.h \
	menu_entry.h menu_entry_simple.h menu_entry_ranged.h menu_list.h \
	menu_list_epiphany.h menu_list_options.h tinyxml/tinystr.h \
	tinyxml/tinyxml.h menu_entry_bool.h music_manager.h