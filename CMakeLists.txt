cmake_minimum_required(VERSION 2.8)
project(openprison)

set(SDL2PP_WITH_IMAGE ON)
set(SDL2PP_WITH_MIXER ON)
set(SDL2PP_WITH_TTF ON)
add_subdirectory(extlibs/libSDL2pp)
include_directories(SYSTEM ${SDL2PP_INCLUDE_DIRS} ./src)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
	./src/App.cpp
	./src/Commuter.cpp
	./src/WorldView.cpp
	./src/micropather.cpp
	./src/Worker.cpp
	./src/World.cpp
	./src/WorkerTaskQueue.cpp
	./src/Box.cpp
	./src/DeliveryQueue.cpp
	./src/Delivery.cpp
	./src/AreaSelection.cpp
	./src/choreograph/Timeline.cpp
	./src/choreograph/TimelineItem.cpp
	./src/choreograph/Cue.cpp
	./src/main.cpp)

add_executable(openprison ${SOURCE_FILES})
target_link_libraries(openprison ${SDL2PP_LIBRARIES})
