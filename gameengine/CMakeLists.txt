set(GAMEENGINE_SRC
	src/gameengineimpl.cpp
)

set(GAMEENGINE_TEST_SRC
	src/gameengineimpltest.cpp
)

include_directories(
	incl
	../common
	../physic/incl
)

add_library(gameengine ${GAMEENGINE_SRC})
add_library(gameenginetest ${GAMEENGINE_TEST_SRC})