find_package(Qt5Multimedia REQUIRED)

set(SOUND_SRC
	soundplayer.cpp
)

add_library(sound ${SOUND_SRC})
qt5_use_modules(sound Multimedia)
