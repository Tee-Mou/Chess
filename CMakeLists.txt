cmake_minimum_required(VERSION 3.10.0)
project(myChess VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

set(headerdir ${PROJECT_SOURCE_DIR}/inc)
include_directories(myChess PRIVATE headerdir)

set

add_executable(myChess main.cpp)
