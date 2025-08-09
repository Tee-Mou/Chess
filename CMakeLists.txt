cmake_minimum_required(VERSION 3.10.0)
project(myChess VERSION 0.1.0 LANGUAGES C CXX)

set(SOURCE_FILES
    main.cpp
    src/Board.cpp
    src/Game.cpp
    src/Pieces.cpp
    src/BasePiece.cpp
    )

add_executable(myChess ${SOURCE_FILES})

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
