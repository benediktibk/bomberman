set(PHYSIC_SRC
	physicsimulator.cpp
	dynamicobject.cpp
	staticobject.cpp
	player.cpp
)

set(PHYSIC_TEST_SRC
	physicsimulatortest.cpp
	dynamicobjecttest.cpp
	staticobjecttest.cpp
	playertest.cpp
)

include_directories(
	.
)

add_library(physic ${PHYSIC_SRC})
add_library(physictest ${PHYSIC_TEST_SRC})
add_subdirectory(Box2D)
