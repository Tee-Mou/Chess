#include "../inc/Game.h"

namespace Chess{
        
    Game::Game(){
        gameBoard = Board();
        this->startGame();
    };

    void Game::startGame()
    {
        for (int i = 1; i <= 8; i++)
        {
            char x = Board::colMap1[i];
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
    void Game::addPiece(std::string pos, bool colour)
    {
        std::string typeName = typeid(T).name();
        char prefix = Board::prefixMap[typeName][0];
        T* piece = new T(colour, prefix, pos, gameBoard);
        gameBoard.addToBoard(pos, piece);
        remainingPieces.push_back(piece);
    };

    void Game::removePiece(std::string pos)
    {
        int x = Board::colMap2[pos[0]];
        int y = pos[1];
        addPiece<NoPiece>(pos, (x+y) % 2);
    };

    std::tuple<char, std::string, std::string, bool> Game::ParseMove(std::string move)
    {
        std::string piecePrefixes = "KQBNR";
        char piecePrefix = 'P';
        char captureChar = ' ';
        if (piecePrefixes.find(move[0])){
            piecePrefix = move[0];
        }
        bool isCapture = false;
        if (move.find('x')){
            captureChar = 'x';
            isCapture = true;
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
        } else if (oldPos.length() == 0) { oldPos = "xx"; };

        return {piecePrefix, oldPos, newPos, isCapture};
    }

    template <class T>
    bool Game::checkSquare(std::tuple<char, std::string, std::string, bool> moveTuple)
    {
        char lookingForPrefix = std::get<0>(moveTuple);
        std::string oldPos = std::get<1>(moveTuple);
        std::string newPos = std::get<2>(moveTuple);
        bool isCapture = std::get<3>(moveTuple);

        std::vector<BasePiece*>::iterator it;
        for (it = remainingPieces.begin(); it != remainingPieces.end(); ++it) {
            BasePiece* piece = *it;
            std::string piecePos = piece->getPos();
            bool posMatch;
            if ( oldPos == "xx" ){ posMatch = true; }
            else if (oldPos[0] == 'x' and oldPos[1] == piecePos[1]) { posMatch = true; }
            else if (oldPos[1] == 'x' and oldPos[0] == piecePos[0]) { posMatch = true; }
            else if (oldPos == piecePos) { posMatch = true; }
            else { posMatch = false; };
            if (piece->getPrefix() == lookingForPrefix && posMatch) { piece->canSeeSquare(newPos, isCapture); };
        }

    };
} // namespace Chess