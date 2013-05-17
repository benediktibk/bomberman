set(MAIN_SRC
	src/gameloop.cpp
)

set(MAIN_TEST_SRC
	src/gamelooptest.cpp
)

include_directories(
	incl
	../common/incl
	../gameengine/incl
	../graphic/incl
	../physic/incl
	../sound/incl
	../threading/incl
)

set(LIBRARIES
	common
	gameengine
	graphic
	physic
	sound
	threading
)

set(LIBRARIES_TEST
	maintest
	commontest
	gameenginetest
	physictest
	threadingtest
)

find_library(CPPUNIT_LIBRARY cppunit)

add_library(main ${MAIN_SRC})
add_library(maintest ${MAIN_TEST_SRC})
add_executable(game src/main.cpp)
add_executable(testrunner src/testrunner.cpp)
target_link_libraries(game ${LIBRARIES})
target_link_libraries(testrunner ${LIBRARIES} ${LIBRARIES_TEST} ${CPPUNIT_LIBRARY})