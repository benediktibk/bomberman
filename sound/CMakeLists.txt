set(SOUND_SRC
	src/soundplayer.cpp
)

include_directories(
	incl
	../common
)

add_library(sound ${SOUND_SRC})