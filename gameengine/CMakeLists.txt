set(GAMEENGINE_SRC
	gameengineimpl.cpp
	grid.cpp
	computerenemyinputfetcher.cpp
	gridobserver.cpp
)

set(GAMEENGINE_TEST_SRC
	gameengineimpltest.cpp
	gridtest.cpp
	gridobservermock.cpp
	gridobserverstub.cpp
	gridobservertest.cpp
)

add_library(gameengine ${GAMEENGINE_SRC})
add_library(gameenginetest ${GAMEENGINE_TEST_SRC})
