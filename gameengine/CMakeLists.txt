set(GAMEENGINE_SRC
	gameengineimpl.cpp
)

set(GAMEENGINE_TEST_SRC
	gameengineimpltest.cpp
)

add_library(gameengine ${GAMEENGINE_SRC})
add_library(gameenginetest ${GAMEENGINE_TEST_SRC})