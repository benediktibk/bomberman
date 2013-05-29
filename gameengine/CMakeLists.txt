set(GAMEENGINE_SRC
	gameengineimpl.cpp
    grid.cpp
)

set(GAMEENGINE_TEST_SRC
	gameengineimpltest.cpp
    gridtest.cpp
)

add_library(gameengine ${GAMEENGINE_SRC})
add_library(gameenginetest ${GAMEENGINE_TEST_SRC})
