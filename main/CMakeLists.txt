set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_library(CPPUNIT_LIBRARY cppunit)
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5OpenGL REQUIRED)
find_package(Qt5Svg REQUIRED)
find_package(Qt5Multimedia REQUIRED)


set(MAIN_SRC
	gameloop.cpp
	mainwindow.cpp
	mainwindowinputfetcher.cpp
	mainwindowinputtest.cpp
	mainwindowgraphictest.cpp
	mainwindowsoundtest.cpp
	startwindow.cpp
)

set(MAIN_TEST_SRC
	gamelooptest.cpp
)

set(REGRESSION_SRC
	userinputsimulator.cpp
)

set(MAIN_FORMS
	gui/mainwindow.ui
	gui/mainwindowinputtest.ui
	gui/mainwindowgraphictest.ui
	gui/startwindow.ui
	gui/mainwindowsoundtest.ui
)

set(LIBRARIES
	main
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
	gameenginetest
	physictest
	threadingtest
	commontest
)

set(QTLIBRARIES
	${Qt5Widgets_LIBRARIES}
	${Qt5Gui_LIBRARIES}
	${Qt5Core_LIBRARIES}
	${Qt5OpenGL_LIBRARIES}
	${Qt5Svg_LIBRARIES}
)

qt5_wrap_ui(MAIN_FORMS_MOC ${MAIN_FORMS})

add_library(main ${MAIN_SRC} ${MAIN_FORMS_MOC})
add_library(maintest ${MAIN_TEST_SRC})
add_executable(game main.cpp ${MAIN_QT_SRC} ${MAIN_FORMS_MOC})
add_executable(inputtest maininputtest.cpp ${MAIN_QT_SRC} ${MAIN_FORMS_MOC})
add_executable(graphictest maingraphictest.cpp ${MAIN_QT_SRC} ${MAIN_FORMS_MOC})
add_executable(startwindowtest startwindowtest.cpp ${MAIN_QT_SRC} ${MAIN_FORMS_MOC})
add_executable(regressiontest mainregressiontest.cpp ${REGRESSION_SRC} ${MAIN_FORMS_MOC})
add_executable(testrunner testrunner.cpp testregistration.cpp)
add_executable(soundtest mainsoundtest.cpp ${MAIN_QT_SRC} ${MAIN_FORMS_MOC})
qt5_use_modules(main Widgets Gui Svg OpenGL Core Multimedia)
qt5_use_modules(game Widgets Gui Svg OpenGL Core Multimedia)
qt5_use_modules(maintest Core)
target_link_libraries(game ${LIBRARIES} boost_thread-mt)
qt5_use_modules(inputtest Widgets Gui Svg OpenGL Core)
target_link_libraries(inputtest ${LIBRARIES} boost_thread-mt)
qt5_use_modules(graphictest Widgets Gui Svg OpenGL Core Multimedia)
qt5_use_modules(graphictest Widgets Gui Svg OpenGL Core Multimedia)
target_link_libraries(graphictest ${LIBRARIES} boost_thread-mt)
qt5_use_modules(startwindowtest Widgets Gui Svg OpenGL Core Multimedia)
target_link_libraries(startwindowtest ${LIBRARIES} boost_thread-mt)
target_link_libraries(regressiontest ${LIBRARIES} boost_thread-mt commontest)
qt5_use_modules(regressiontest Widgets Gui Svg OpenGL Core Multimedia)
target_link_libraries(testrunner ${LIBRARIES_TEST} ${LIBRARIES} ${CPPUNIT_LIBRARY} boost_thread-mt)
qt5_use_modules(soundtest Widgets Gui Core Multimedia)
target_link_libraries(soundtest ${LIBRARIES} boost_thread-mt)
