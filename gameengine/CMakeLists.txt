set(GAMEENGINE_SRC
	allplayerinputfetcher.cpp
	gameengineimpl.cpp
	computerenemyinputfetcher.cpp
	computerenemyinputfetchereasy.cpp
	computerenemyinputfetchermedium.cpp
	computerenemyinputfetcherhard.cpp
	routergrid.cpp
	routergridfield.cpp
	notdangerousandfreedecider.cpp
	coveredbyplayerdecider.cpp
	coveredbyloosewalldecider.cpp
	freedecider.cpp
	route.cpp
	router.cpp
	coveredbypowerupdecider.cpp
	certainfieldandnotdangerousdecider.cpp
)

set(GAMEENGINE_TEST_SRC
	gameengineimpltest.cpp
	routergridtest.cpp
	routergridfieldtest.cpp
	notdangerousandfreedecidertest.cpp
	coveredbyplayerdecidertest.cpp
	coveredbyloosewalldecidertest.cpp
	freedecidertest.cpp
	routetest.cpp
	routertest.cpp
	computerenemyinputfetcherhardtest.cpp
	coveredbypowerupdecidertest.cpp
	certainfieldandnotdangerousdecidertest.cpp
)

add_library(gameengine ${GAMEENGINE_SRC})
add_library(gameenginetest ${GAMEENGINE_TEST_SRC})
