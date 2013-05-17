set(GRAPHIC_SRC
	src/graphicdrawerqt.cpp
)

include_directories(
	incl
	../common/incl
)

find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})

add_library(graphic ${GRAPHIC_SRC})