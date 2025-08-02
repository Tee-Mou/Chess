#include "Game.h"

Game::Game(){
    for (int i; i < 64; i++){
        Piece newPiece = Piece(true, 0, 0);
        addActivePiece(newPiece);
    }
}

void Game::addActivePiece(Piece piece){
    activePieces.push_back(piece);
}