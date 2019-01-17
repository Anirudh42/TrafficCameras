cmake_minimum_required(VERSION 2.8)
project(prj-ece650)

if (EXISTS "${CMAKE_SOURCE_DIR}/minisat")
  add_subdirectory(minisat)
else()
  message (FATAL_ERROR "MiniSat not found. Use `git clone https://github.com/agurfinkel/minisat` to check it out.")
endif()


## ECE650 Specific configuration start here
## Project specific configurations go here

# enable c++11 support
set (CMAKE_CXX_FLAGS "-std=c++11 -Wall ${CMAKE_CXX_FLAGS}")

# expose minisat header files
include_directories(${CMAKE_SOURCE_DIR}/minisat)

 set(SourceFiles
      ${CMAKE_CURRENT_LIST_DIR}/src/Adjacency.cpp
      ${CMAKE_CURRENT_LIST_DIR}/src/AllEdges.cpp
      ${CMAKE_CURRENT_LIST_DIR}/src/ApproxVC1.cpp
      ${CMAKE_CURRENT_LIST_DIR}/src/ApproxVC2.cpp
      ${CMAKE_CURRENT_LIST_DIR}/src/FindVertexCover.cpp
      ${CMAKE_CURRENT_LIST_DIR}/src/InputOutput.cpp
      ${CMAKE_CURRENT_LIST_DIR}/src/prj-ece650.cpp
      ${CMAKE_CURRENT_LIST_DIR}/src/Vertex.cpp
    )




# create the main executable
## add additional .cpp files if needed
add_executable(prj-ece650 ${SourceFiles})
# link MiniSAT libraries
target_link_libraries(prj-ece650  minisat-lib-static)
# link pthread
target_link_libraries(prj-ece650 pthread)
