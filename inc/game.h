#include "Pieces.h"

namespace Chess{

    class Game
    {
        public:
            Game();
            void startGame();
            void turn();
            std::tuple<std::string, std::string, std::string, bool> ParseMove(std::string move);
            void printBoard();

            template <class T>
            void addPiece(std::string* pos, bool colour);
            void addNullPiece(std::string pos);
            BasePiece* checkSquare(std::tuple<std::string, std::string, std::string, bool> moveTuple);
            bool movePiece(std::tuple<std::string, std::string> moveTuple, BasePiece* piece);

            bool getTurn();

            //setters
            std::tuple<int, int> setOccupiedSquares(int old_x, int old_y, int new_x, int new_y);

        private:
            std::vector<BasePiece*> remainingPieces = {};
            Board* gameBoard;
            std::vector<std::map<std::string, BasePiece*>> boardHistory;
            bool currentTurn = 1;
    };
} // namespace Chess