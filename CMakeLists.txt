project(XMLPARSER)

#set minimum version
cmake_minimum_required(VERSION 3.7)

include_directories(.)

#set variable
set(CMAKE_ROOT .)
set(CMAKE_PARSER ./parser)
set(CMAKE_BIN ./bin)

# compile sub-directory
add_subdirectory(parser)
add_subdirectory(bin)
