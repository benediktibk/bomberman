set(COMMON_SRC
	gamestate.cpp
	inputstate.cpp
	stopwatch.cpp
	playerstate.cpp
	point.cpp
	enemystate.cpp
	bombstate.cpp
	wallstate.cpp
	uniqueidcreator.cpp
)

set(COMMON_TEST_SRC
	gamestatetest.cpp
	inputstatetest.cpp
	stopwatchtest.cpp
	pointtest.cpp
	enemystatetest.cpp
	bombstatetest.cpp
	wallstatetest.cpp
	uniqueidcreatortest.cpp
)

add_library(common ${COMMON_SRC})
add_library(commontest ${COMMON_TEST_SRC})
