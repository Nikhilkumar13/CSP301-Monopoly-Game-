#Specify the version being used aswell as the language
#cmake_minimum_required(VERSION 2.6)
#Name your project here
project(Game)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

#set(CMAKE_BUILD_TYPE Debug)

#This tells CMake to fib.c and name it fibonacci
add_executable(Game Chance.cpp)
add_executable(Game Chest.cpp)
add_executable(Game main.cpp)
add_executable(Game Player.cpp)
add_executable(Game Properties.cpp)
add_executable(Game botPlayer.cpp)
#add_executable(Game pointer.cpp)
#add_executable(Game dice.cpp)

include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

target_link_libraries(Game ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
