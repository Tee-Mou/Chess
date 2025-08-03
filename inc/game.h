#include "Pieces.h"
#include <list>
#include <string>
#include <map>

class Game
{
    public:
        Game();
        void generateBoard();
        std::tuple<char, std::string, std::string> ParseMove(std::string move);

        template <class T>
        BasePiece* addPiece(std::string pos, bool colour);
        template <class T>
        bool checkSquare(std::string pos, std::string lookingForPiece);

        //getters
        BasePiece* getSquare(std::string pos) { return board[pos]; };
        std::map<std::string, BasePiece*> getboard() { return board; };

        //setters
        void removePiece(std::string pos);
        std::tuple<int, int> setOccupiedSquares(int old_x, int old_y, int new_x, int new_y);

        std::map<int, std::string> colMap1 = {{1, "a"},{2, "b"},{3, "c"},{4, "d"},{5, "e"},{6, "f"},{7, "g"},{8, "h"}};
        std::map<std::string, int> colMap2 = {{"a", 1},{"b", 2},{"c", 3},{"d", 4},{"e", 5},{"f", 6},{"g", 7},{"h", 8}};

    private:
        std::map<std::string, BasePiece*> board = {};
        bool currentTurn = 0;
};