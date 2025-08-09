#include "../inc/Pieces.h"

namespace Chess{

    Pawn::Pawn(bool colour, std::string prefix, std::string pos, Board* board) : BasePiece(colour, prefix, pos, board) { };
    King::King(bool colour, std::string prefix, std::string pos, Board* board) : BasePiece(colour, prefix, pos, board) { };
    Queen::Queen(bool colour, std::string prefix, std::string pos, Board* board) : BasePiece(colour, prefix, pos, board) { };
    Bishop::Bishop(bool colour, std::string prefix, std::string pos, Board* board) : BasePiece(colour, prefix, pos, board) { };
    Knight::Knight(bool colour, std::string prefix, std::string pos, Board* board) : BasePiece(colour, prefix, pos, board) { }
    Rook::Rook(bool colour, std::string prefix, std::string pos, Board* board) : BasePiece(colour, prefix, pos, board) { };
    NoPiece::NoPiece(bool colour, std::string prefix, std::string pos, Board* board) : BasePiece(colour, prefix, pos, board) { };

    bool Pawn::canSeeSquare(std::string pos, bool isCapture) {
        std::string piecePos = this->getPos();
        bool pathClear = true;
        std::string checkPos;
        checkPos = piecePos;
        int d = 1;
        if (!this->getColour()) { d = -1; }
        checkPos[1] += d;
        if (!isCapture){
            if (this->getBoard()->getSquare(checkPos)->getPrefix() == " "){
                if (checkPos == pos) { return true; }
                else {
                    checkPos[1] += d;
                    if (this->getBoard()->getSquare(checkPos)->getPrefix() == " " && checkPos == pos && !this->getHasMoved()) { return true; }
                }
            }
        }
        else{
            checkPos[0]--;
            if (checkPos == pos 
                && (this->getBoard()->getSquare(checkPos)->getPrefix()) != " " 
                && this->getBoard()->getSquare(checkPos)->getColour() == !this->getColour()) { return true; };
            checkPos[0]++; checkPos[0]++;
            if (checkPos == pos 
                && (this->getBoard()->getSquare(checkPos)->getPrefix()) != " " 
                && this->getBoard()->getSquare(checkPos)->getColour() == !this->getColour()) { return true; };
        }
        return false;
    };
    
    bool King::canSeeSquare(std::string pos, bool isCapture) { 
        std::string piecePos = this->getPos();
        int x = Board::colMap2[piecePos[0]];
        int y = piecePos[1] - '0';
        std::string checkPos = "xx";
        Board board = *this->getBoard();
        for(int i = x-1; i <= x+1; i++ ){
            for(int j = y-1; j <= y+1; j++ ){
                checkPos[0] = Board::colMap1[i][0]; checkPos[1] = j + '0';
                if (checkPos == piecePos) { continue; };
                if (checkPos == pos 
                    && (this->getBoard()->getSquare(checkPos)->getPrefix()) != " " 
                    && isCapture
                    && !this->moveIsCheck(pos) 
                    && this->getBoard()->getSquare(checkPos)->getColour() == !this->getColour()) { return true; }
                else if (checkPos == pos 
                    && (this->getBoard()->getSquare(checkPos)->getPrefix()) == " " 
                    && !isCapture 
                    && !this->moveIsCheck(pos)) { return true; }
                else if (checkPos == pos) { return false; }
            }
        }
        return false;
    };
    
    bool King::moveIsCheck(std::string pos) { return false; }

    bool Queen::canSeeSquare(std::string pos, bool isCapture) { 
        return this->checkLine(pos, isCapture);
    };
    
    bool Bishop::canSeeSquare(std::string pos, bool isCapture) {
        return this->checkLine(pos, isCapture, "diagonal");
    };

    bool Knight::canSeeSquare(std::string pos, bool isCapture) {
        std::string piecePos = this->getPos();
        int x = Board::colMap2[(piecePos[0])];
        int y = piecePos[1] - '0';
        std::string checkPos = "xx";
        Board* board = this->getBoard();
        for(int i = x-2; i <= x+2; i++ ){
            for(int j = y-2; j <= y+2; j++ ){
                if (j < 1 || j > 8 || i < 1 || i > 8) { continue; }
                checkPos[0] = Board::colMap1[i][0]; checkPos[1] = j + '0';
                int squareProd;
                squareProd = std::abs(j - y) * std::abs(j - y) + std::abs(i - x) * std::abs(i - x);
                if (squareProd == 5 
                && checkPos == pos 
                && (this->getBoard()->getSquare(checkPos)->getPrefix()) != " " 
                && isCapture
                && this->getBoard()->getSquare(checkPos)->getColour() == !this->getColour()) { return true; }
                else if ((i - x)*(i - x) + (j - y)*(j - y) == 5 
                && checkPos == pos 
                && (this->getBoard()->getSquare(checkPos)->getPrefix()) == " " 
                && !isCapture) { return true; }
                else { continue; }
            };
        };
        return false;
    }; 

    bool Rook::canSeeSquare(std::string pos, bool isCapture) { 
        return this->checkLine(pos, isCapture, "cardinal");
    }; 

    bool NoPiece::canSeeSquare(std::string pos, bool isCapture) { return false; }

} // namespace Chess 