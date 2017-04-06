cmake_minimum_required(VERSION 3.6)
project(Rpn)

set(CMAKE_CXX_STANDARD 11)

###############################Allegro 5 Stuff################################

INCLUDE_DIRECTORIES(C:/allegro/include)
LINK_DIRECTORIES(C:/allegro/lib)

#########From above###############
set(SOURCE_FILES main.cpp Stack.cpp Stack.h Button.cpp Button.h Numpad.cpp Numpad.h)
add_executable(Rpn ${SOURCE_FILES})
#################################

file(GLOB LIBRARIES "C:/allegro/lib/liballegro_main-debug.dll.a" "C:/allegro/lib/liballegro_monolith-debug.dll.a" "C:/allegro/lib/liballegro.dll.a")
message("LIBRARIES = ${LIBRARIES}")

TARGET_LINK_LIBRARIES(Rpn ${LIBRARIES})