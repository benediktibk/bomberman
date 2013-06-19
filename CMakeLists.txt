cmake_minimum_required(VERSION 2.8)
project(game)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE debug)
endif()

set(BOX2D_BUILD_STATIC)

set(CMAKE_CXX_FLAGS_COMMON "-Wall -Wextra -Werror -ansi")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_COMMON} -O3 -DNDEBUG")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_COMMON} -g")
set(CMAKE_CXX_FLAGS_COVERAGE "${CMAKE_CXX_FLAGS_COMMON} -g -fprofile-arcs -ftest-coverage")

include_directories(
	.
)

add_subdirectory(common)
add_subdirectory(gameengine)
add_subdirectory(graphic)
add_subdirectory(main)
add_subdirectory(physic)
add_subdirectory(sound)
add_subdirectory(threading)

add_custom_target(
		checkIncludeGuards ALL
		COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/checkIncludeGuards.sh
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
	)

set(LEVELS
	defaultlevel.csv
	levellist.csv
)

set(TESTFILES
	testlevel.csv
	testlevelonerowtoshort.csv
	testlevelwrongtypeinfile.csv
	testlevellist.csv
)

set(GRAPHICS
	bomb_planted.svg
	player_standing.svg
	wall_loose.svg
	wall_solid.svg
	power_up.svg
	powerup_v1.svg
	powerup_v2.svg
	explosion_center.svg
	explosion_flame.svg
    powerup.svg
	bg_cell_pattern.svg
)

foreach(file ${LEVELS})
	file(	COPY
			${CMAKE_CURRENT_SOURCE_DIR}/resources/levels/${file}
			DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/main/bin/resources/levels/)
endforeach()

foreach(file ${TESTFILES})
	file(	COPY
			${CMAKE_CURRENT_SOURCE_DIR}/resources/testfiles/${file}
			DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/main/bin/resources/testfiles/)
endforeach()

foreach(file ${GRAPHICS})
	file(	COPY
			${CMAKE_CURRENT_SOURCE_DIR}/resources/graphics/${file}
			DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/main/bin/resources/graphics/)
endforeach()

add_custom_target(
	testcoverage
	${CMAKE_CURRENT_SOURCE_DIR}/testCoverage.sh ${CMAKE_CURRENT_SOURCE_DIR}
	DEPENDS testrunner
)

find_package(Doxygen)
if(DOXYGEN_FOUND)
execute_process(COMMAND hg identify -n
				OUTPUT_VARIABLE HG_CURRENT_REV)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)

add_custom_target(

	doc

	rm -f ${CMAKE_CURRENT_BINARY_DIR}/documentation/html/formula.repository && ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile 2>&1 | grep -v "stl_vector.h" | grep -v "parameter '__"

	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}

	COMMENT "Generating API documentation with Doxygen" VERBATIM

	DEPENDS ${COMMON_SRC} ${COMMON_TEST_SRC}

)
endif(DOXYGEN_FOUND)
