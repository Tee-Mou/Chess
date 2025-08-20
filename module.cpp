#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "inc/Game.h"

namespace py = pybind11;
using namespace Chess;

PYBIND11_MODULE(chessAPI, handle) {
    handle.doc() = "API to simulate chess. For use training a machine learning chess engine.";

    py::class_<Game>(handle, "Game")
        .def(py::init())
        .def("start_game", &Game::startGame, py::return_value_policy::reference)
        .def("turn", &Game::turn, py::return_value_policy::reference)
        .def("next_turn", &Game::nextTurn, py::return_value_policy::reference)
        .def("get_gameboard", &Game::getGameBoard, py::return_value_policy::reference)
        .def("print_board", &Game::printBoard, py::return_value_policy::reference)
        .def("game_over", &Game::gameOver, py::return_value_policy::reference)
        .def("parse_move", &Game::parseMove, py::return_value_policy::reference)
        .def("get_move_list", &Game::getMoveList,py::return_value_policy::reference);

    py::class_<Board>(handle, "Board")
        .def(py::init())
        .def("get_board", &Board::getboard, py::return_value_policy::reference);

    py::class_<BasePiece>(handle, "Base_Piece")
        .def(py::init<bool, std::string, std::string, Board*>());
    
    py::class_<Pawn, BasePiece>(handle, "Pawn")
        .def(py::init<bool, std::string, std::string, Board*>());

    py::class_<King, BasePiece>(handle, "King")
        .def(py::init<bool, std::string, std::string, Board*>());

    py::class_<Queen, BasePiece>(handle, "Queen")
        .def(py::init<bool, std::string, std::string, Board*>());

    py::class_<Bishop, BasePiece>(handle, "Bishop")
        .def(py::init<bool, std::string, std::string, Board*>());

    py::class_<Knight, BasePiece>(handle, "Knight")
        .def(py::init<bool, std::string, std::string, Board*>());

    py::class_<Rook, BasePiece>(handle, "Rook")
        .def(py::init<bool, std::string, std::string, Board*>());
}