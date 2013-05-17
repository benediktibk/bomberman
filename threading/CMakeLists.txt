set(THREADING_SRC
	src/thread.cpp
)

set(THREADING_TEST_SRC
	src/threadtest.cpp
)

include_directories(
	incl
)

add_library(threading ${THREADING_SRC})
add_library(threadingtest ${THREADING_TEST_SRC})