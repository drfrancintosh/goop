cmake_minimum_required(VERSION 3.12)
set(LIB goop)
add_library(${LIB} INTERFACE)
print_variables("./lib/${LIB}/")

target_sources(${LIB} INTERFACE
${CMAKE_CURRENT_SOURCE_DIR}/src/GList.c
${CMAKE_CURRENT_SOURCE_DIR}/src/GMap.c
${CMAKE_CURRENT_SOURCE_DIR}/src/GNode.c
${CMAKE_CURRENT_SOURCE_DIR}/src/GObj.c
${CMAKE_CURRENT_SOURCE_DIR}/src/Goop.c
${CMAKE_CURRENT_SOURCE_DIR}/src/GQueue.c
${CMAKE_CURRENT_SOURCE_DIR}/src/GString.c
${CMAKE_CURRENT_SOURCE_DIR}/src/GTree.c
)

target_include_directories(${LIB} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/includes)

target_link_libraries(${LIB} INTERFACE
)