cmake_minimum_required(VERSION 2.8)
project(openprison)

add_subdirectory(extlibs/libSDL2pp)
include_directories(SYSTEM ${SDL2PP_INCLUDE_DIRS})

set(SOURCE_FILES
	./src/main.cpp)

add_executable(openprison ${SOURCE_FILES})
target_link_libraries(openprison ${SDL2PP_LIBRARIES})
