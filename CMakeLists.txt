cmake_minimum_required(VERSION 3.7)
project(btree)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Btree.hpp BtreeNode.hpp BtreeVisualize.hpp)
#target_link_libraries(/usr/local/include/graphviz)
#find_package(/usr/local/include/graphviz)
#file(GLOB graph "/usr/local/include/graphviz/*.h")

#aux_source_directory(/usr/local/include/graphviz/ graph)
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
#find_package(Boost  COMPONENTS *boost libraries here*)
find_package(Boost 1.62.0 COMPONENTS filesystem regex graph)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    add_executable(btree ${SOURCE_FILES})
#    add_executable(progname file1.cxx file2.cxx)
    target_link_libraries(btree ${Boost_LIBRARIES})
endif()

#target_link_libraries(btree graph_lib)
