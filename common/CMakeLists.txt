set(COMMON_SRC
	src/gamestate.cpp
	src/inputstate.cpp
	src/stopwatch.cpp
	src/playerstate.cpp
)

set(COMMON_TEST_SRC
	src/gamestatetest.cpp
	src/inputstatetest.cpp
	src/stopwatchtest.cpp
)

include_directories(
	incl
)

add_library(common ${COMMON_SRC})
add_library(commontest ${COMMON_TEST_SRC})