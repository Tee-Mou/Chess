#include "../inc/Pieces.h"

namespace Chess{

    Pawn::Pawn(bool colour, char prefix, std::string pos, Board board) : BasePiece(colour, prefix, pos) { gameBoard = board; };
    King::King(bool colour, char prefix, std::string pos, Board board) : BasePiece(colour, prefix, pos) { gameBoard = board; };
    Queen::Queen(bool colour, char prefix, std::string pos, Board board) : BasePiece(colour, prefix, pos) { gameBoard = board; };
    Bishop::Bishop(bool colour, char prefix, std::string pos, Board board) : BasePiece(colour, prefix, pos) { gameBoard = board; };
    Knight::Knight(bool colour, char prefix, std::string pos, Board board) : BasePiece(colour, prefix, pos) { gameBoard = board; };
    Rook::Rook(bool colour, char prefix, std::string pos, Board board) : BasePiece(colour, prefix, pos) { gameBoard = board; };

    bool Pawn::canSeeSquare(std::string pos) {
        std::string piecePos = this->getPos();
        int x = Board::colMap2[piecePos[0]];
        int y = piecePos[1];
        bool canMoveToSquare = false;
        bool uClear = true;
        bool foundSquare = false;
        int d = 1;
        std::string checkPos;
        BasePiece* pieceInSquare;
        if (this->getColour() == 0) { d = -1; };
        for (int checkX = x - 1; checkX <= x + 1; checkX++){
            char checkY = y + d;
            char charCheckX = Board::colMap1[checkX];  
            checkPos = charCheckX + checkY;
            pieceInSquare = gameBoard.getSquare(checkPos);
            char piecePrefix = pieceInSquare->getPrefix();
            if (piecePrefix != 'X' && checkX == x) { uClear = false; }
            if (checkPos == pos) { 
                foundSquare = true; 
                if (checkX == x && piecePrefix == 'X') { canMoveToSquare = true; break; }
                else if (checkX != x && piecePrefix != 'X') { canMoveToSquare = true; break; }
            };
        };
        if (this->getHasMoved() == false && foundSquare == false && uClear == true) {
            checkPos = piecePos;
            char rank = (int)checkPos[1] + 2 * d;
            checkPos[1] = rank;
            if (checkPos == pos) { 
                foundSquare = true; 
                if (gameBoard.getSquare(checkPos)->getPrefix() == 'X') { canMoveToSquare = true; }; 
            };
        };
        return canMoveToSquare;
    };
    bool King::canSeeSquare(std::string pos) { return true; }; 
    bool Queen::canSeeSquare(std::string pos) { return true; }; 
    bool Bishop::canSeeSquare(std::string pos) { return true; }; 
    bool Knight::canSeeSquare(std::string pos) { return true; }; 
    bool Rook::canSeeSquare(std::string pos) { return true; }; 
} // namespace Chess