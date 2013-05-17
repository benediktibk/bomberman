set(GAMEENGINE_SRC
	src/gameengine.cpp
)

set(GAMEENGINE_TEST_SRC
	src/gameenginetest.cpp
)

include_directories(
	incl
	../common/incl
)

add_library(gameengine ${GAMEENGINE_SRC})
add_library(gameenginetest ${GAMEENGINE_TEST_SRC})