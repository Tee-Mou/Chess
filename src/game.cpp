#include "../inc/Game.h"
#include <string>

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

std::tuple<char, std::string, std::string> Game::ParseMove(std::string move)
{
    std::string piecePrefixes = "KQBNR";
    char piecePrefix = 'P';
    char captureChar = ' ';
    if (piecePrefixes.find(move[0])){
        piecePrefix = move[0];
    }
    if (move.find('x')){
        captureChar = 'x';
    }
    int len = move.length();
    std::string newPos = move.substr(len-2);

    std::string oldPos;
    oldPos.pop_back();
    oldPos.pop_back();
    if (oldPos[len-1] == 'x') { oldPos.pop_back(); };
    if (piecePrefix != 'P') { oldPos.erase(0); };

    std::string cols = "abcdefgh";
    std::string rows = "12345678";
    char anyCoord = 'x';
    if (oldPos.length() == 1) { 
        if (cols.find(oldPos[0])) { oldPos.push_back(anyCoord); } 
        else if (rows.find(oldPos[0])) { oldPos.insert(0, &anyCoord); }
    }

    return {piecePrefix, oldPos, newPos};
}

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
                    oldPos = checkPos;
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