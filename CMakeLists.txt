cmake_minimum_required(VERSION 3.27)
project(mongodb_getting_started)

find_package(mongocxx REQUIRED)
find_package(bsoncxx REQUIRED)

set(CMAKE_CXX_STANDARD 17)

add_executable(mongodb_getting_started main.cpp)

target_link_libraries(mongodb_getting_started PRIVATE mongo::mongocxx_shared)
target_link_libraries(mongodb_getting_started PRIVATE mongo::bsoncxx_shared)