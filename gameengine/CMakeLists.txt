set(GAMEENGINE_SRC
	gameengineimpl.cpp
	grid.cpp
	computerenemyinputfetcher.cpp
	gridobserver.cpp
	routergrid.cpp
	routergridfield.cpp
	notdangerousandfreedecider.cpp
	coveredbyplayerdecider.cpp
	coveredbyloosewalldecider.cpp
	freedecider.cpp
	route.cpp
	router.cpp
)

set(GAMEENGINE_TEST_SRC
	gameengineimpltest.cpp
	gridtest.cpp
	gridobservermock.cpp
	gridobserverstub.cpp
	gridobservertest.cpp
	routergridtest.cpp
	routergridfieldtest.cpp
	notdangerousandfreedecidertest.cpp
	coveredbyplayerdecidertest.cpp
	coveredbyloosewalldecidertest.cpp
	freedecidertest.cpp
	routetest.cpp
)

add_library(gameengine ${GAMEENGINE_SRC})
add_library(gameenginetest ${GAMEENGINE_TEST_SRC})
