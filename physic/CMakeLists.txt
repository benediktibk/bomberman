set(PHYSIC_SRC
	src/physicsimulator.cpp
	src/dynamicobject.cpp
)

set(PHYSIC_TEST_SRC
	src/physicsimulatortest.cpp
)

include_directories(
	incl
	../common
	.
)

add_library(physic ${PHYSIC_SRC})
add_library(physictest ${PHYSIC_TEST_SRC})
add_subdirectory(Box2D)