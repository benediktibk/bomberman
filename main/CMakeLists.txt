find_library(CPPUNIT_LIBRARY cppunit)
find_package(Qt4 REQUIRED)
set(QT_USE_QTOPENGL TRUE)
set(QT_USE_QTSVG TRUE)
include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})

set(MAIN_SRC
)

set(MAIN_TEST_SRC
	gamelooptest.cpp
)

set(MAIN_QT_SRC
	mainwindow.cpp
	mainwindowinputfetcher.cpp
	mainwindowinputtest.cpp
	mainwindowgraphictest.cpp
	gameloop.cpp
)

set(MAIN_FORMS
	gui/mainwindow.ui
	gui/mainwindowinputtest.ui
	gui/mainwindowgraphictest.ui
)

set(MAIN_QT_INCL
	mainwindow.h
	mainwindowinputfetcher.h
	mainwindowinputtest.h
	mainwindowgraphictest.h
	gameloop.h
)

include_directories(
	${CMAKE_CURRENT_BINARY_DIR}
)

set(LIBRARIES
	gameengine
	graphic
	physic
	sound
	threading
	common
	Box2D
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

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

#add_library(main ${MAIN_SRC})
add_library(maintest ${MAIN_TEST_SRC})
add_executable(game main.cpp ${MAIN_QT_SRC} ${MAIN_QT_INCL_MOC} ${MAIN_FORMS_MOC})
add_executable(inputtest maininputtest.cpp ${MAIN_QT_SRC} ${MAIN_QT_INCL_MOC} ${MAIN_FORMS_MOC})
add_executable(graphictest maingraphictest.cpp ${MAIN_QT_SRC} ${MAIN_QT_INCL_MOC} ${MAIN_FORMS_MOC})
add_executable(testrunner testrunner.cpp testregistration.cpp)
target_link_libraries(game ${LIBRARIES} ${QT_LIBRARIES} boost_thread-mt)
target_link_libraries(inputtest ${LIBRARIES} ${QT_LIBRARIES} boost_thread-mt)
target_link_libraries(graphictest ${LIBRARIES} ${QT_LIBRARIES} boost_thread-mt)
target_link_libraries(testrunner ${LIBRARIES_TEST} ${LIBRARIES} ${CPPUNIT_LIBRARY} boost_thread-mt)
