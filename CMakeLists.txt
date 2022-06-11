cmake_minimum_required(VERSION 3.10)
project(main)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_BUILD_TYPE Debug)

include_directories(/usr/local/Cellar/open-scene-graph/3.6.5_1/include)

find_package(OpenSceneGraph REQUIRED COMPONENTS osgDB osgGA osgUtil osgViewer)

add_executable(main main.cpp)

target_link_libraries(${PROJECT_NAME} ${OPENSCENEGRAPH_LIBRARIES})
