# I don't know if this works or not...
# Anyways, I have no idea where you put your SFML, so good luck
cmake_minimum_required(VERSION 3.28)
project(lab10 LANGUAGES CXX)

set(SFML_DIR "/path/to/sfml") # <-- YOUR PATH HERE
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
add_library(memer memer.cpp)
target_link_libraries(memer sfml-graphics sfml-audio)
add_executable(memeify memeify.cpp)
target_link_libraries(memeify memer sfml-graphics sfml-audio)
