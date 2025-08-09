#include <string>
#include <list>
#include <map>
#include <vector>
#include <typeinfo>
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <iostream>

namespace Chess{

    class BasePiece;

    class Board
    {   
        public:
            static std::map<int, std::string> colMap1;
            static std::map<char, int> colMap2;
            static std::map<std::string, std::string> prefixMap;


            // getters
            BasePiece* getSquare(std::string pos) { return board[pos]; };
            std::map<std::string, BasePiece*> getboard() { return board; };

            // setters
            void setBoard(std::map<std::string, BasePiece*> newBoard) { board = newBoard; }
            void addToBoard(std::string* pos, BasePiece* piece);
            void removeFromBoard(std::string* pos) { board.erase(*pos); };
            void setSquare(std::string pos, BasePiece* piece);

        private:
            std::map<std::string, BasePiece*> board;
    };
}