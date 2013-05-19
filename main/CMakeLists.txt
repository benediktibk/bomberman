find_library(CPPUNIT_LIBRARY cppunit)
find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})

set(MAIN_SRC
	src/gameloop.cpp
)

set(MAIN_TEST_SRC
	src/gamelooptest.cpp
)

set(MAIN_QT_SRC
	src/mainwindow.cpp
)

set(MAIN_FORMS
	gui/mainwindow.ui
)

set(MAIN_QT_INCL
	incl/mainwindow.h
)

include_directories(
	incl
	../common/incl
	../gameengine/incl
	../graphic/incl
	../physic/incl
	../sound/incl
	../threading/incl
	${CMAKE_CURRENT_BINARY_DIR}
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

qt4_wrap_ui(MAIN_FORMS_MOC ${MAIN_FORMS})
qt4_wrap_cpp(MAIN_QT_INCL_MOC ${MAIN_QT_INCL})

add_library(main ${MAIN_SRC})
add_library(maintest ${MAIN_TEST_SRC})
add_executable(game src/main.cpp ${MAIN_QT_SRC} ${MAIN_QT_INCL_MOC} ${MAIN_FORMS_MOC})
add_executable(testrunner src/testrunner.cpp src/testregistration.cpp)
target_link_libraries(game ${LIBRARIES} ${QT_LIBRARIES} boost_thread-mt)
target_link_libraries(testrunner ${LIBRARIES_TEST} ${LIBRARIES} ${CPPUNIT_LIBRARY} boost_thread-mt)