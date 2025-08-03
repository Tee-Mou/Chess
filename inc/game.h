#include "Pieces.h"

namespace Chess{

    class Game
    {
        public:
            Game();
            void startGame();
            std::tuple<char, std::string, std::string> ParseMove(std::string move);

            template <class T>
            void addPiece(std::string pos, bool colour);
            template <class T>
            bool checkSquare(std::tuple<char, std::string, std::string> moveTuple);

            bool getTurn();

            //setters
            void removePiece(std::string pos);
            std::tuple<int, int> setOccupiedSquares(int old_x, int old_y, int new_x, int new_y);

        private:
            std::vector<BasePiece*> remainingPieces = {};
            Board gameBoard;
            bool currentTurn = 0;
    };
} // namespace Chess