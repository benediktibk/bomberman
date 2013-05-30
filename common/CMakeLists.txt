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
	leveldefinition.cpp
	changeablestate.cpp
	destroyablestate.cpp
	powerupstate.cpp
	powerupmaxbombstate.cpp
	powerupbombpackstate.cpp
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
	leveldefinitiontest.cpp
	changeablestatetest.cpp
	destroyablestatetest.cpp
	destroyablestatemock.cpp
	powerupstatetest.cpp
	powerupmaxbombstatetest.cpp
	powerupbombpackstatetest.cpp
)

add_library(common ${COMMON_SRC})
add_library(commontest ${COMMON_TEST_SRC})
