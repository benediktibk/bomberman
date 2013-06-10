set(GRAPHIC_SRC
	graphicdrawerqt.cpp
	player.cpp
	bomb.cpp
	wall.cpp
	point.cpp
	powerup.cpp
)

find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})

add_library(graphic ${GRAPHIC_SRC})
