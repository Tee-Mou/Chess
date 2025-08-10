#include "Pieces.h"

namespace Chess{

    class Game
    {
        public:
            Game();
            void startGame();
            void gameOver();
            int turn();
            void printBoard(std::map<std::string, BasePiece*> boardToPrint);

            template <class T>
            void addPiece(std::string* pos, bool colour);
            void addNullPiece(std::string pos);
            BasePiece* checkSquare(std::tuple<std::string, std::string, std::string, bool> moveTuple);
            std::tuple<std::string, std::string, std::string, bool> ParseMove(std::string move);
            int validateMove(std::tuple<std::string, std::string> moveTuple, BasePiece* piece);
            bool doMove(std::tuple<std::string, std::string> moveTuple, BasePiece* piece);
            bool checkCheckmate();

            bool getTurn();

            //setters
            std::tuple<int, int> setOccupiedSquares(int old_x, int old_y, int new_x, int new_y);
            void nextTurn() { currentTurn = !currentTurn; };

        private:
            std::vector<BasePiece*> remainingPieces = {};
            Board* gameBoard;
            std::vector<std::map<std::string, BasePiece*>> boardHistory;
            bool currentTurn = 1;
            bool mCheckingCheckmate = false;
    };
} // namespace Chess