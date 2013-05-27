set(SOUND_SRC
	soundplayer.cpp
)

include_directories(
	../common
)

add_library(sound ${SOUND_SRC})