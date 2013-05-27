set(GRAPHIC_SRC
	src/graphicdrawerqt.cpp
	src/player.cpp
	src/bomb.cpp
	src/wall.cpp
	src/pointgraphic.cpp
)

include_directories(
	incl
	../common
	../resources/objects
)

find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})

add_library(graphic ${GRAPHIC_SRC})
