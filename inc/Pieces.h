#include "Board.h"

namespace Chess {
    class Pawn : public BasePiece{ public: Pawn(bool colour, char prefix, std::string pos, Board board); bool canSeeSquare(std::string pos, bool isCapture); private: Board gameBoard; };
    class King : public BasePiece{ 
        public: 
            King(bool colour, char prefix, std::string pos, Board board);
            bool canSeeSquare(std::string pos, bool isCapture); 
            bool moveIsCheck(std::string pos);

            //getters
            bool getCheck() { return inCheck; };
            //setters
            void setCheck(bool isCheck) { inCheck = isCheck; };

        private:
            bool inCheck;
            Board gameBoard; };
    class Queen : public BasePiece{ public: Queen(bool colour, char prefix, std::string pos, Board board); bool canSeeSquare(std::string pos, bool isCapture); private: Board gameBoard; };
    class Bishop : public BasePiece{ public: Bishop(bool colour, char prefix, std::string pos, Board board); bool canSeeSquare(std::string pos, bool isCapture); private: Board gameBoard; };
    class Knight : public BasePiece{ public: Knight(bool colour, char prefix, std::string pos, Board board); bool canSeeSquare(std::string pos, bool isCapture); private: Board gameBoard; };
    class Rook : public BasePiece{ public: Rook(bool colour, char prefix, std::string pos, Board board); bool canSeeSquare(std::string pos, bool isCapture); private: Board gameBoard; };
    class NoPiece : public BasePiece{ public: NoPiece(bool colour, char prefix, std::string pos, Board board); bool canSeeSquare(std::string pos, bool isCapture); private: Board gameBoard; };
}