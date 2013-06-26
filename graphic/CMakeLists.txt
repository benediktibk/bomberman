set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5OpenGL REQUIRED)
find_package(Qt5Svg REQUIRED)

set(GRAPHIC_SRC
	graphicdrawerqt.cpp
	player.cpp
	bomb.cpp
	wall.cpp
	point.cpp
	powerup.cpp
	cellbackground.cpp
	explodedbomb.cpp
	svgrenderer.cpp
)

add_library(graphic ${GRAPHIC_SRC})
qt5_use_modules(graphic Widgets Gui Svg OpenGL Core)
