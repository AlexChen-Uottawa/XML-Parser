#find boost package
find_package(Boost REQUIRED)
if(NOT Boost_FOUND)
  message("Not Found Boost")
endif()

message("Boost_INCLUDE_DIRS = ${Boost_INCLUDE_DIRS}")
include_directories(${Boost_INCLUDE_DIRS})

# build library
aux_source_directory(. DIR_PARSER)
add_library(parser SHARED ${DIR_PARSER})
