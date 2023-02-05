cmake_minimum_required(VERSION 3.11)

project(lab_1)
add_executable(exercise_0.1 exercise_0.1.cpp)
add_executable(exercise_0.2 exercise_0.2.cpp)
add_executable(exercise_0.3 exercise_0.3.cpp)
add_executable(exercise_1 exercise_1.cpp)
add_executable(exercise_2 exercise_2.cpp)

add_library(gmsh SHARED IMPORTED)
set_target_properties(gmsh PROPERTIES
    IMPORTED_LOCATION "/usr/local/lib/libgmsh.so"
    INTERFACE_INCLUDE_DIRECTORIES "/usr/local/include"
)

set(GMSH_LIBRARY gmsh)

target_link_libraries(exercise_0.1 ${GMSH_LIBRARY})
target_link_libraries(exercise_0.2 ${GMSH_LIBRARY})
target_link_libraries(exercise_0.3 ${GMSH_LIBRARY})
target_link_libraries(exercise_1 ${GMSH_LIBRARY})
target_link_libraries(exercise_2 ${GMSH_LIBRARY})
