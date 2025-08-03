#include "BasePiece.h"

namespace Chess{
    class Board
    {   
        public:
            static std::map<int, char> colMap1;
            static std::map<char, int> colMap2;
            static std::map<std::string, std::string> prefixMap;

            // getters
            BasePiece* getSquare(std::string pos) { return board[pos]; };
            std::map<std::string, BasePiece*> getboard() { return board; };

            // setters
            void addToBoard(std::string pos, BasePiece* piece);

        private:
            std::map<std::string, BasePiece*> board = {};
    };
}