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
            if (checkPos == pos 
                && gameBoard.getSquare(checkPos)->getPrefix() != 'X' 
                && gameBoard.getSquare(checkPos)->getColour() == !this->getColour()) { canMoveToSquare = true; };
            checkPos[0] = checkPos[0]++;
            if (checkPos == pos 
                && gameBoard.getSquare(checkPos)->getPrefix() != 'X' 
                && gameBoard.getSquare(checkPos)->getColour() == !this->getColour()) { canMoveToSquare = true; };
        }
        return canMoveToSquare;
    };
    
    bool King::canSeeSquare(std::string pos, bool isCapture) { 
        std::string piecePos = this->getPos();
        int x = Board::colMap2[piecePos[0]];
        int y = piecePos[1];
        std::string checkPos;
        for(int i = x-1; i <= x+1; i++ ){
            for(int j = y-1; i <= x+1; j++ ){
                checkPos = Board::colMap1[i] + (char)j;
                if (checkPos == piecePos) { continue; };
                if (checkPos == pos 
                    && gameBoard.getSquare(checkPos)->getPrefix() != 'X' 
                    && isCapture
                    && !this->moveIsCheck(pos) 
                    && gameBoard.getSquare(checkPos)->getColour() == !this->getColour()) { return true; }
                else if (checkPos == pos 
                    && gameBoard.getSquare(checkPos)->getPrefix() == 'X' 
                    && !isCapture 
                    && !this->moveIsCheck(pos)) { return true; }
                else if (checkPos == pos) { return false; }
            }
        }
        return false;
    }; 

    bool Queen::canSeeSquare(std::string pos, bool isCapture) { 
        std::string piecePos = this->getPos();
        int x = Board::colMap2[piecePos[0]];
        int y = piecePos[1];
        bool uClear = true;
        bool rClear = true;
        bool dClear = true;
        bool lClear = true;
        bool urClear = true;
        bool drClear = true;
        bool dlClear = true;
        bool ulClear = true;
        std::string checkPos = piecePos;
        for (int i = 1; i <= 7; i++ ){
            if (uClear) {
                checkPos = (char)(piecePos[0] + i) + (char)(piecePos[0]);
                char prefix = gameBoard.getSquare(checkPos)->getPrefix();
                if (prefix != 'X') { uClear = false; }
                if (checkPos == pos 
                && prefix != 'X' 
                && isCapture
                && gameBoard.getSquare(checkPos)->getColour() == !this->getColour()) { return true; }
                else if (checkPos == pos 
                && prefix == 'X' 
                && !isCapture) { return true; }
            }
            if (dClear) {
                checkPos = (char)(piecePos[0] - i) + (char)(piecePos[0]);
                char prefix = gameBoard.getSquare(checkPos)->getPrefix();
                if (prefix != 'X') { dClear = false; }
                if (checkPos == pos 
                && prefix != 'X' 
                && isCapture
                && gameBoard.getSquare(checkPos)->getColour() == !this->getColour()) { return true; }
                else if (checkPos == pos 
                && prefix == 'X' 
                && !isCapture) { return true; }
            }
            if (rClear) {
                checkPos = (char)(piecePos[0]) + (char)(piecePos[0] + i);
                char prefix = gameBoard.getSquare(checkPos)->getPrefix();
                if (prefix != 'X') { rClear = false; }
                if (checkPos == pos 
                && prefix != 'X' 
                && isCapture
                && gameBoard.getSquare(checkPos)->getColour() == !this->getColour()) { return true; }
                else if (checkPos == pos 
                && prefix == 'X' 
                && !isCapture) { return true; }
            }
            if (lClear) {
                checkPos = (char)(piecePos[0]) + (char)(piecePos[0] - i);
                char prefix = gameBoard.getSquare(checkPos)->getPrefix();
                if (prefix != 'X') { lClear = false; }
                if (checkPos == pos 
                && prefix != 'X' 
                && isCapture
                && gameBoard.getSquare(checkPos)->getColour() == !this->getColour()) { return true; }
                else if (checkPos == pos 
                && prefix == 'X' 
                && !isCapture) { return true; }
            }
            if (urClear) {
                checkPos = (char)(piecePos[0] + i) + (char)(piecePos[0] + i);
                char prefix = gameBoard.getSquare(checkPos)->getPrefix();
                if (prefix != 'X') { urClear = false; }
                if (checkPos == pos 
                && prefix != 'X' 
                && isCapture
                && gameBoard.getSquare(checkPos)->getColour() == !this->getColour()) { return true; }
                else if (checkPos == pos 
                && prefix == 'X' 
                && !isCapture) { return true; }
            }
            if (drClear) {
                checkPos = (char)(piecePos[0] + i) + (char)(piecePos[0] - i);
                char prefix = gameBoard.getSquare(checkPos)->getPrefix();
                if (prefix != 'X') { drClear = false; }
                if (checkPos == pos 
                && prefix != 'X' 
                && isCapture
                && gameBoard.getSquare(checkPos)->getColour() == !this->getColour()) { return true; }
                else if (checkPos == pos 
                && prefix == 'X' 
                && !isCapture) { return true; }
            }
            if (dlClear) {
                checkPos = (char)(piecePos[0] - i) + (char)(piecePos[0] - i);
                char prefix = gameBoard.getSquare(checkPos)->getPrefix();
                if (prefix != 'X') { dlClear = false; }
                if (checkPos == pos 
                && prefix != 'X' 
                && isCapture
                && gameBoard.getSquare(checkPos)->getColour() == !this->getColour()) { return true; }
                else if (checkPos == pos 
                && prefix == 'X' 
                && !isCapture) { return true; }
            }
            if (ulClear) {
                checkPos = (char)(piecePos[0] - i) + (char)(piecePos[0] + i);
                char prefix = gameBoard.getSquare(checkPos)->getPrefix();
                if (prefix != 'X') { ulClear = false; }
                if (checkPos == pos 
                && prefix != 'X' 
                && isCapture
                && gameBoard.getSquare(checkPos)->getColour() == !this->getColour()) { return true; }
                else if (checkPos == pos 
                && prefix == 'X' 
                && !isCapture) { return true; }
            }
        }

        return false;
    };
    
    
    bool Bishop::canSeeSquare(std::string pos, bool isCapture) {
        std::string piecePos = this->getPos();
        int x = Board::colMap2[piecePos[0]];
        int y = piecePos[1];
        bool urClear = true;
        bool drClear = true;
        bool dlClear = true;
        bool ulClear = true;
        std::string checkPos = piecePos;
        for (int i = 1; i <= 7; i++ ){
            if (urClear) {
                checkPos = (char)(piecePos[0] + i) + (char)(piecePos[0] + i);
                char prefix = gameBoard.getSquare(checkPos)->getPrefix();
                if (prefix != 'X') { urClear = false; }
                if (checkPos == pos 
                && prefix != 'X' 
                && isCapture
                && gameBoard.getSquare(checkPos)->getColour() == !this->getColour()) { return true; }
                else if (checkPos == pos 
                && prefix == 'X' 
                && !isCapture) { return true; }
            }
            if (drClear) {
                checkPos = (char)(piecePos[0] + i) + (char)(piecePos[0] - i);
                char prefix = gameBoard.getSquare(checkPos)->getPrefix();
                if (prefix != 'X') { drClear = false; }
                if (checkPos == pos 
                && prefix != 'X' 
                && isCapture
                && gameBoard.getSquare(checkPos)->getColour() == !this->getColour()) { return true; }
                else if (checkPos == pos 
                && prefix == 'X' 
                && !isCapture) { return true; }
            }
            if (dlClear) {
                checkPos = (char)(piecePos[0] - i) + (char)(piecePos[0] - i);
                char prefix = gameBoard.getSquare(checkPos)->getPrefix();
                if (prefix != 'X') { dlClear = false; }
                if (checkPos == pos 
                && prefix != 'X' 
                && isCapture
                && gameBoard.getSquare(checkPos)->getColour() == !this->getColour()) { return true; }
                else if (checkPos == pos 
                && prefix == 'X' 
                && !isCapture) { return true; }
            }
            if (ulClear) {
                checkPos = (char)(piecePos[0] - i) + (char)(piecePos[0] + i);
                char prefix = gameBoard.getSquare(checkPos)->getPrefix();
                if (prefix != 'X') { ulClear = false; }
                if (checkPos == pos 
                && prefix != 'X' 
                && isCapture
                && gameBoard.getSquare(checkPos)->getColour() == !this->getColour()) { return true; }
                else if (checkPos == pos 
                && prefix == 'X' 
                && !isCapture) { return true; }
            }
        }

        return false;
    }; 

    bool Knight::canSeeSquare(std::string pos, bool isCapture) { 
        float squareDistance = 5;
        std::string piecePos = this->getPos();
        int x = Board::colMap2[piecePos[0]];
        int y = piecePos[1];
        std::string checkPos;
        for(int i = x-2; i <= x+2; i++ ){
            for(int j = y-2; i <= x+2; j++ ){
                checkPos = Board::colMap1[i] + (char)j;
                if ((i - x)*(i - x) + (j-y)*(j-y) == squareDistance 
                && checkPos == pos 
                && gameBoard.getSquare(checkPos)->getPrefix() != 'X' 
                && isCapture
                && gameBoard.getSquare(checkPos)->getColour() == !this->getColour()) { return true; }
                else if ((i - x)*(i - x) + (j-y)*(j-y) == squareDistance 
                && checkPos == pos 
                && gameBoard.getSquare(checkPos)->getPrefix() == 'X' 
                && !isCapture) { return true; }
            };
        };
        return false;
    }; 

    bool Rook::canSeeSquare(std::string pos, bool isCapture) { 
        std::string piecePos = this->getPos();
        int x = Board::colMap2[piecePos[0]];
        int y = piecePos[1];
        bool uClear = true;
        bool rClear = true;
        bool dClear = true;
        bool lClear = true;
        std::string checkPos = piecePos;
        for (int i = 1; i <= 7; i++ ){
            if (uClear) {
                checkPos = (char)(piecePos[0] + i) + (char)(piecePos[0]);
                char prefix = gameBoard.getSquare(checkPos)->getPrefix();
                if (prefix != 'X') { uClear = false; }
                if (checkPos == pos 
                && prefix != 'X' 
                && isCapture
                && gameBoard.getSquare(checkPos)->getColour() == !this->getColour()) { return true; }
                else if (checkPos == pos 
                && prefix == 'X' 
                && !isCapture) { return true; }
            }
            if (dClear) {
                checkPos = (char)(piecePos[0] - i) + (char)(piecePos[0]);
                char prefix = gameBoard.getSquare(checkPos)->getPrefix();
                if (prefix != 'X') { dClear = false; }
                if (checkPos == pos 
                && prefix != 'X' 
                && isCapture
                && gameBoard.getSquare(checkPos)->getColour() == !this->getColour()) { return true; }
                else if (checkPos == pos 
                && prefix == 'X' 
                && !isCapture) { return true; }
            }
            if (rClear) {
                checkPos = (char)(piecePos[0]) + (char)(piecePos[0] + i);
                char prefix = gameBoard.getSquare(checkPos)->getPrefix();
                if (prefix != 'X') { rClear = false; }
                if (checkPos == pos 
                && prefix != 'X' 
                && isCapture
                && gameBoard.getSquare(checkPos)->getColour() == !this->getColour()) { return true; }
                else if (checkPos == pos 
                && prefix == 'X' 
                && !isCapture) { return true; }
            }
            if (lClear) {
                checkPos = (char)(piecePos[0]) + (char)(piecePos[0] - i);
                char prefix = gameBoard.getSquare(checkPos)->getPrefix();
                if (prefix != 'X') { lClear = false; }
                if (checkPos == pos 
                && prefix != 'X' 
                && isCapture
                && gameBoard.getSquare(checkPos)->getColour() == !this->getColour()) { return true; }
                else if (checkPos == pos 
                && prefix == 'X' 
                && !isCapture) { return true; }
            }
        }

        return false;
    }; 
} // namespace Chess