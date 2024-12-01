# I don't know if this works or not...
# Anyways, I have no idea where you put your SFML, so good luck
cmake_minimum_required(VERSION 3.28)
project(project4 LANGUAGES CXX)

set(SFML_DIR "/path/to/sfml") # <-- YOUR PATH HERE
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
add_executable(msw msw.cpp)
target_link_libraries(msw sfml-graphics sfml-audio)
