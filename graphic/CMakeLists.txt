set(GRAPHIC_SRC
	src/graphicdrawerqt.cpp
)

include_directories(
	incl
	../common/incl
)

add_library(graphic ${GRAPHIC_SRC})