#include "../inc/BasePiece.h"
#include <string>

namespace Chess{
    std::map<int, std::string> Board::colMap1 = {{1, "a"},{2, "b"},{3, "c"},{4, "d"},{5, "e"},{6, "f"},{7, "g"},{8, "h"}, {-1, "x"}};
    std::map<char, int> Board::colMap2 = {{'a', 1},{'b', 2},{'c', 3},{'d', 4},{'e', 5},{'f', 6},{'g', 7},{'h', 8}, {'x', -1}};
    std::map<std::string, std::string> Board::prefixMap = {{"class Chess::Pawn", "P"}, 
                                                    {"class Chess::King",  "K"}, 
                                                    {"class Chess::Queen",  "Q"}, 
                                                    {"class Chess::Bishop",  "B"}, 
                                                    {"class Chess::Knight", "N"}, 
                                                    {"class Chess::Rook",  "R"}, 
                                                    {"class Chess::NoPiece",  " "}};
    
    
    void Board::addToBoard(std::string* pos, BasePiece* piece) { board.insert({*pos, piece}); }
    void Board::setSquare(std::string pos, BasePiece* piece) { board[pos] = piece; }
} // namespace Chess