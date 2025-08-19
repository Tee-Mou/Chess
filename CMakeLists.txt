cmake_minimum_required(VERSION 3.10.0)
project(chessAPI VERSION 0.1.0 LANGUAGES C CXX)

set(SOURCE_FILES_EXE
    main.cpp
    src/Board.cpp
    src/Game.cpp
    src/Pieces.cpp
    src/BasePiece.cpp
    )
add_executable(myChess ${SOURCE_FILES_EXE})

add_subdirectory(pybind11)

set(SOURCE_FILES_MODULE
    module.cpp
    src/Board.cpp
    src/Game.cpp
    src/Pieces.cpp
    src/BasePiece.cpp
    )

pybind11_add_module(chessAPI ${SOURCE_FILES_MODULE})

