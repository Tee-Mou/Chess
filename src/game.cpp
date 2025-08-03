#include "../inc/Game.h"
#include <string>
#include <typeinfo>

Game::Game(){
    this->generateBoard();
};

void Game::generateBoard()
{
    for (int i = 1; i <= 8; i++)
    {
        std::string x = colMap1[i];
        for (int j = 1; j <= 8; j++)
        {
            std::string pos = x + std::to_string(j);
            if (j == 1){
                if (i == 1 || i ==8){
                    addPiece<Rook>(pos, 1);
                } else if (i == 2 || i ==7){
                    addPiece<Knight>(pos, 1);
                } else if (i == 3 || i == 6){
                    addPiece<Bishop>(pos, 1);
                } else if (i == 4) {
                    addPiece<Queen>(pos, 1);
                } else if (i == 5) {
                    addPiece<King>(pos, 1);
                };
                
            } else if (j == 2){
                addPiece<Pawn>(pos, 1);
            } else if (j == 7){
                addPiece<Pawn>(pos, 0);
            } else if (j == 8){
                if (i == 0 || i ==7){
                    addPiece<Rook>(pos, 0);
                } else if (i == 1 || i ==6){
                    addPiece<Knight>(pos, 0);
                } else if (i == 2 || i == 5){
                    addPiece<Bishop>(pos, 0);
                } else if (i == 3) {
                    addPiece<Queen>(pos, 0);
                } else if (i == 5) {
                    addPiece<King>(pos, 1);
                };
            } else {
                removePiece(pos);
            };
        }
    }
    return;
};

template <class T> 
BasePiece* Game::addPiece(std::string pos, bool colour)
{
    std::string type_name = typeid(T).name();
    T* piece = new T(colour, type_name);
    board.emplace(pos, piece);
};

void Game::removePiece(std::string pos)
{
    int x = colMap2[std::to_string(pos[0])];
    int y = pos[1];
    addPiece<NoPiece>(pos, (x+y) % 2);
};

void Game::ParseMove(std::string move)
{
    char piece_notation = move[0];
    std::string piece;
    std::string piece_list = "abcdefgh";
    if (piece_list.find(piece_notation)){
        piece = "Pawn";                                             
    } else if (piece_notation == 'K'){
        piece = "King";
    } else if (piece_notation == 'Q'){
        piece = "Queen";
    } else if (piece_notation == 'B'){
        piece = "Bishop";
    } else if (piece_notation == 'N'){
        piece = "Knight";
    } else if (piece_notation == 'R'){
        piece = "Rook";
    };
    std::string newPos = move.substr(-2, 2);
};

template <class T>
bool Game::checkSquare(std::string pos, std::string lookingForPiece)
{
    int x = colMap2[std::to_string(pos[0])];
    int y = pos[1];
    std::string oldPos;
    if(std::is_same<T, Pawn>()){
        return;
    } else if (std::is_same<T, King>()) {
        for(int i = x - 1; i <= x + 1; i++){
            for(int j = y - 1; j <= y + 1; j++){
                std::string checkPos = colMap1[i] + std::to_string(j);
                BasePiece* piece = getSquare(checkPos);
                std::string name = piece->getName();
                bool colour = piece->getColour();
                if (colour == currentTurn && name == lookingForPiece){
                    oldPos = checkPos 
                };
            } 
        }
    } else if (std::is_same<T, Queen>()) {
        return;
    } else if (std::is_same<T, Bishop>()) {
        return;
    } else if (std::is_same<T, Knight>()) {
        return;
    } else if (std::is_same<T, Rook>()) {
        return;
    }
};