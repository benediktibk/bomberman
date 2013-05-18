set(THREADING_SRC
	src/thread.cpp
	src/mutex.cpp
)

set(THREADING_TEST_SRC
	src/threadtest.cpp
	src/mutextest.cpp
)

include_directories(
	incl
)

add_library(threading ${THREADING_SRC})
add_library(threadingtest ${THREADING_TEST_SRC})