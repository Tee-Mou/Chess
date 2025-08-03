#include "../inc/Pieces.h"

namespace Chess{

    Pawn::Pawn(bool colour, char prefix, std::string pos, Board board) : BasePiece(colour, prefix, pos) { gameBoard = board; };
    King::King(bool colour, char prefix, std::string pos, Board board) : BasePiece(colour, prefix, pos) { gameBoard = board; };
    Queen::Queen(bool colour, char prefix, std::string pos, Board board) : BasePiece(colour, prefix, pos) { gameBoard = board; };
    Bishop::Bishop(bool colour, char prefix, std::string pos, Board board) : BasePiece(colour, prefix, pos) { gameBoard = board; };
    Knight::Knight(bool colour, char prefix, std::string pos, Board board) : BasePiece(colour, prefix, pos) { gameBoard = board; };
    Rook::Rook(bool colour, char prefix, std::string pos, Board board) : BasePiece(colour, prefix, pos) { gameBoard = board; };

    bool Pawn::canSeeSquare(std::string pos, bool isCapture) {
        std::string piecePos = this->getPos();
        int x = Board::colMap2[piecePos[0]];
        int y = piecePos[1];
        bool canMoveToSquare = false;
        bool uClear = true;
        int d = 1;
        std::string checkPos;
        BasePiece* pieceInSquare;
        checkPos = piecePos;
        char rank = (int)checkPos[1] + d;
        checkPos[1] = rank;
        if (!isCapture){
            if (gameBoard.getSquare(checkPos)->getPrefix() == 'X'){
                if (checkPos == pos) { canMoveToSquare = true; }
                else {
                    rank = (int)checkPos[1] + d;
                    checkPos[1] = rank;
                    if (gameBoard.getSquare(checkPos)->getPrefix() == 'X' && checkPos == pos) { canMoveToSquare = true; }
                }
            }
        }
        else{
            checkPos[0] = checkPos[0]--;
            if (checkPos == pos && gameBoard.getSquare(checkPos)->getPrefix() != 'X') { canMoveToSquare = true; };
            checkPos[0] = checkPos[0]++;
            if (checkPos == pos && gameBoard.getSquare(checkPos)->getPrefix() != 'X') { canMoveToSquare = true; };
        }
        return canMoveToSquare;
    };
    

    bool King::canSeeSquare(std::string pos, bool isCapture) { return true; }; 
    bool Queen::canSeeSquare(std::string pos, bool isCapture) { return true; }; 
    bool Bishop::canSeeSquare(std::string pos, bool isCapture) { return true; }; 
    bool Knight::canSeeSquare(std::string pos, bool isCapture) { return true; }; 
    bool Rook::canSeeSquare(std::string pos, bool isCapture) { return true; }; 
} // namespace Chess