#include "Pieces.h"

namespace Chess{

    class Game
    {
        public:
            Game();
            void startGame();
            void gameOver();
            std::string receiveMove();
            int turn(std::string args);
            void printBoard(std::map<std::string, BasePiece*> boardToPrint);

            template <class T>
            void addPiece(std::string* pos, bool colour);
            void addNullPiece(std::string pos);
            BasePiece* findPiece(std::tuple<std::string, std::string, std::string, bool> moveTuple);
            std::tuple<std::string, std::string, std::string, bool> parseMove(std::string move);
            int validateMove(std::tuple<std::string, std::string> moveTuple, BasePiece* piece);
            bool doMove(std::tuple<std::string, std::string> moveTuple, BasePiece* piece);
            bool checkCheckmate();
            int validateCastle(bool longCastle);
            int validateChecks();

            //getters
            bool getTurn();
            Board* getGameBoard() { return gameBoard; };
            std::vector<std::string> getMoveList() { return moveList; };

            //setters
            std::tuple<int, int> setOccupiedSquares(int old_x, int old_y, int new_x, int new_y);
            void nextTurn() { currentTurn = !currentTurn; };
            void addToMoveList(std::string move) { moveList.push_back(move); }

        private:
            std::vector<BasePiece*> remainingPieces = {};
            Board* gameBoard;
            std::vector<std::map<std::string, BasePiece*>> boardHistory;
            std::vector<std::string> moveList;
            bool currentTurn = 1;
            bool mCheckingCheckmate = false;
    };
} // namespace Chess