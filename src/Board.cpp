#include "../inc/Board.h"

namespace Chess{
    std::map<int, char> Board::colMap1 = {{1, 'a'},{2, 'b'},{3, 'c'},{4, 'd'},{5, 'e'},{6, 'f'},{7, 'g'},{8, 'h'}, {-1, 'x'}};
    std::map<char, int> Board::colMap2 = {{'a', 1},{'b', 2},{'c', 3},{'d', 4},{'e', 5},{'f', 6},{'g', 7},{'h', 8}, {'x', -1}};
    std::map<std::string, std::string> Board::prefixMap = {{"Pawn", "P"}, {"King",  "K"}, {"Queen",  "Q"}, {"Bishop",  "B"}, {"Knight", "N"}, {"Rook",  "R"}, {"NoPiece",  "X"}};
    void Board::addToBoard(std::string pos, BasePiece* piece) { board.emplace(pos, piece); };
} // namespace Chess