set(PHYSIC_SRC
	physicsimulator.cpp
	dynamicobject.cpp
)

set(PHYSIC_TEST_SRC
	physicsimulatortest.cpp
)

include_directories(
	../common
	.
)

add_library(physic ${PHYSIC_SRC})
add_library(physictest ${PHYSIC_TEST_SRC})
add_subdirectory(Box2D)