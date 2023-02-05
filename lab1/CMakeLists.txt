cmake_minimum_required(VERSION 3.11)

set(CMAKE_CXX_FLAGS "-std=c++11 -g")

project(lab1)
add_executable(task1 ${CMAKE_SOURCE_DIR}/task1.cpp)
add_executable(task2 ${CMAKE_SOURCE_DIR}/task2.cpp)

# gmsh
add_library(gmsh SHARED IMPORTED)
set_target_properties(gmsh PROPERTIES
    IMPORTED_LOCATION "/media/daniil/Kingston/gmsh-sdk/lib/libgmsh.so"
    INTERFACE_INCLUDE_DIRECTORIES "/media/daniil/Kingston/gmsh-sdk/include"
)
set(GMSH_LIBRARY gmsh)

# Укажем библиотеки для линковки
target_link_libraries(task1 ${GMSH_LIBRARY})
target_link_libraries(task2 ${GMSH_LIBRARY})
