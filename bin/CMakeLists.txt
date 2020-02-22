# create binary
aux_source_directory(. DIR_BIN)
add_executable(parse-xml-configuration ${DIR_BIN})

# link
target_link_libraries(parse-xml-configuration parser)
