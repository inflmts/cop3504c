# I don't know if this works or not...
set(SFML_DIR "/path/to/sfml")
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
add_library(memer memer.cpp)
target_link_libraries(memer sfml-graphics sfml-window sfml-system)
add_executable(memeify memeify.cpp)
target_link_libraries(memeify memer sfml-graphics sfml-window sfml-system)
