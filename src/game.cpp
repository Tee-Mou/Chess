#include "../inc/Game.h"
#include <iostream>
#include <ostream>
#include <string>
#include <fstream>
#include <windows.h> 
#include <conio.h>

namespace Chess{
        
    Game::Game(){
        Board* board = new Board();
        gameBoard = board;
    };

    void Game::startGame()
    {
        for (int i = 1; i <= 8; i++)
        {
            std::string x = Board::colMap1[i];
            for (int j = 1; j <= 8; j++)
            {
                std::string pos = x + std::to_string(j);
                if (j == 1){
                    if (i == 1 || i == 8){
                        addPiece<Rook>(&pos, 1);
                    } else if (i == 2 || i ==7){
                        addPiece<Knight>(&pos, 1);
                    } else if (i == 3 || i == 6){
                        addPiece<Bishop>(&pos, 1);
                    } else if (i == 4) {
                        addPiece<Queen>(&pos, 1);
                    } else if (i == 5) {
                        addPiece<King>(&pos, 1);
                    };
                } else if (j == 2){
                    addPiece<Pawn>(&pos, 1);
                } else if (j == 7){
                    addPiece<Pawn>(&pos, 0);
                } else if (j == 8){
                    if (i == 1 || i == 8){
                        addPiece<Rook>(&pos, 0);
                    } else if (i == 2 || i == 7){
                        addPiece<Knight>(&pos, 0);
                    } else if (i == 3 || i == 6){
                        addPiece<Bishop>(&pos, 0);
                    } else if (i == 4) {
                        addPiece<Queen>(&pos, 0);
                    } else if (i == 5) {
                        addPiece<King>(&pos, 0);
                    };
                } else {
                    addNullPiece(pos);
                };
            }
        }
        boardHistory.push_back(gameBoard->getboard());
        std::cout << "Done!" << std::endl;
    };

    void Game::printBoard(std::map<std::string, BasePiece*> boardToPrint){
        
        std::cout << "========================================================================\n";
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        for (int j = 26; j >= 3; j--){
            for (int i = 1; i <= 8; i++) {
                std::string pos = Board::colMap1[i] + std::to_string(j / 3);
                std::string prefix;
                prefix = boardToPrint[pos]->getPrefix();
                int k;
                if (boardToPrint[pos]->getColour() && (i + j / 3) % 2 == 0) { k = 143; }
                else if (boardToPrint[pos]->getColour() && (i + j / 3) % 2 == 1) { k = 127; }
                else if ((i + j / 3) % 2 == 0) { k = 128; }
                else { k = 112; }
                SetConsoleTextAttribute(hConsole, k);
                if (j % 3 != 1) {
                    std::cout << "         ";
                }
                else {
                    std::cout << "   " << prefix << prefix << prefix << "   "; 
                };
                SetConsoleTextAttribute(hConsole, 15);
                if (i == 8) { std::cout << "\n"; }; 
            };
        };
        std::cout << "========================================================================\n"
                  << "========================================================================\n";
    };

    void Game::gameOver() {
        std::cout << "================GAME OVER================\n" << "===========" << (currentTurn ? "WHITE" : "BLACK") << " IS THE WINNER" << "===========\n\n";
        this-> printBoard(gameBoard->getboard());
        std::cout << "\n\nEnter any letter to close... ";
        char noUse;
        std::cin >> noUse;
        std::cin.ignore();
    };

    std::string Game::receiveMove(){
        std::string args;
        std::cout << (currentTurn ? "White >> " : "Black >> ");
        std::getline(std::cin, args);
        return args;
    }

    int Game::turn(std::string args){
        std::string move;
        std::string quantityStr = "1";
        if (args.find(" ") != std::string::npos){
            move = args.substr(0, args.find(" "));
            std::string rest = args.substr(args.find(" "));
            quantityStr = rest.substr(1);
        }
        else { move = args; };

        if (move != "peekback") {
            int validMove;
            if (move == "O-O-O"){
                validMove = validateCastle(true);
            }
            else if (move == "O-O") {
                validMove = validateCastle(false);
            } 
            else {
                std::tuple<std::string, std::string, std::string, bool> parsedMove = parseMove(move);
                BasePiece* movedPiece = this->findPiece(parsedMove);
                if (movedPiece->getPrefix() == " ") { return 0; };
                std::tuple<std::string, std::string> moveTuple = {movedPiece->getPos(), std::get<2>(parsedMove)};
                validMove = this->validateMove(moveTuple, movedPiece);
            };
            
            if (validMove == 0) { return 0; };

            boardHistory.push_back(gameBoard->getboard());
            return validMove; 
        }
        else if (move == "peekback") {
            int quantity;
            try{
                quantity = std::stoi(quantityStr);
            }

            catch (std::invalid_argument) { quantity = 0; };
            if (quantity < 1 || quantity > boardHistory.size() - 1) { return 0; };
            
            std::map<std::string, BasePiece*> boardToPeek = boardHistory.at(boardHistory.size() - 1 - quantity);
            this->printBoard(boardToPeek);
            std::cout << "Press enter twice to return to the game ";
            getchar();
            std::cin.ignore();
            currentTurn = !currentTurn;
            return 1;
        }
        else { ; return 0; };

    };

    int Game::validateMove(std::tuple<std::string, std::string> moveTuple, BasePiece* piece) {
        std::map<std::string, BasePiece*> lastBoard = gameBoard->getboard();
        std::vector<BasePiece*>::iterator it;
        for (it = remainingPieces.begin(); it != remainingPieces.end(); ++it) {
            BasePiece* anyPiece = *it;
            anyPiece->setEnPassantable(false);
        }

        bool enPassant = false;
        std::string oldPos = std::get<0>(moveTuple);
        std::string newPos = std::get<1>(moveTuple);
        std::string enPassantPos;

        if (newPos[0] == oldPos[0] 
            && currentTurn ? newPos[1] == oldPos[1] + 2 : newPos[1] == oldPos[1] - 2 
            && piece->getPrefix() == "P") { piece->setEnPassantable(true); }
        if (oldPos[0] != newPos[0]
            && piece->getPrefix() == "P"
            && gameBoard->getSquare(newPos)->getPrefix() == " ") { 
                enPassant = true;
                enPassantPos = newPos;
                currentTurn ? enPassantPos[1]-- : enPassantPos[1]++; 
        }

        piece->setPos(newPos);
        piece->pieceMoved();
        this->addNullPiece(oldPos);
        if (enPassant) { this->addNullPiece(enPassantPos); }
        gameBoard->setSquare(newPos, piece);

        int status = this->validateChecks();
        if (status == 0) { gameBoard->setBoard(lastBoard); }
        return status;
    };

    int Game::validateCastle(bool longCastle){
        std::map<std::string, BasePiece*> lastBoard = gameBoard->getboard();
        std::string oldKingPos = currentTurn ? "e1" : "e8";
        std::string newKingPos = oldKingPos;
        std::string oldRookPos = oldKingPos;
        std::string newRookPos = oldRookPos;
        oldRookPos[0] = longCastle ? 'a' : 'h';
        newRookPos[0] = longCastle ? 'c' : 'f';
        BasePiece* king = gameBoard->getSquare(oldKingPos);
        BasePiece* rook = gameBoard->getSquare(oldRookPos);
        if (king->getHasMoved() || rook->getHasMoved() || king->getCheck()) { return 0; };

        for (int i = 0; i <  2; i++) {
            longCastle ? newKingPos[0]-- : newKingPos[0]++;
            if (lastBoard[newKingPos]->getPrefix() != " ") { return 0; }  
            king->setPos(newKingPos);
            gameBoard->setSquare(newKingPos, king);
            if (king->checkForCheck()) { gameBoard->setBoard(lastBoard); return 0; };
        };
        this->addNullPiece(oldKingPos);
        rook->setPos(newRookPos);
        this->addNullPiece(oldRookPos);
        gameBoard->setSquare(newRookPos, rook);
        int status = this->validateChecks();
        if (status == 0) { gameBoard->setBoard(lastBoard); }
        return status;
    }

    int Game::validateChecks() {
        std::vector<BasePiece*>::iterator it;
        bool isCheckMate = false;
        bool checksSelf = false;
        bool checksOpp = false;
        BasePiece* opposingKing;
        for (it = remainingPieces.begin(); it != remainingPieces.end(); ++it) {
            BasePiece* checkPiece = *it;
            std::string prefix = checkPiece->getPrefix();
            bool colour = checkPiece->getColour();
            if (prefix == "K") { colour == currentTurn ? checksSelf = checkPiece->checkForCheck() : checksOpp = checkPiece->checkForCheck(); 
                if (colour != currentTurn) { opposingKing = checkPiece; }
            }
        };
        if (checksSelf) { return 0; }
        if (checksOpp && !mCheckingCheckmate) {  mCheckingCheckmate = true; ; isCheckMate = this->checkCheckmate(); }
        if (isCheckMate) { return 2; }
        opposingKing->setCheck(checksOpp);
        return 1;
    }

    bool Game::checkCheckmate()
    {
        std::vector<BasePiece*>::iterator pieceIt;
        std::map<std::string, BasePiece*>::iterator posIt;

        for (pieceIt = remainingPieces.end(); pieceIt != remainingPieces.end(); ++pieceIt){
            BasePiece* piece = *pieceIt;
            std::map<std::string, BasePiece*> board = gameBoard->getboard();
            if (piece->getColour() == currentTurn) { continue; };
            for (posIt = board.begin(); posIt != board.end(); ++posIt){
                if (!piece->canSeeSquare(posIt->first, true) || !piece->canSeeSquare(posIt->first, false)) { continue; }
                std::tuple<std::string, std::string> moveTuple = {piece->getPos(), posIt->first};
                if (this->validateMove(moveTuple, piece) != 0) { mCheckingCheckmate = false; return false; };
            };
        }; 
        mCheckingCheckmate = false;
        return true;
    }

    template <class T> 
    void Game::addPiece(std::string* pos, bool colour)
    {
        std::string name = typeid(T).name();
        std::string typeName = name;
        std::string prefix;
        prefix = Board::prefixMap[typeName];
        T* piece = new T(colour, prefix, *pos, gameBoard);
        gameBoard->removeFromBoard(pos);
        gameBoard->addToBoard(pos, piece);
        if (prefix != " ") { remainingPieces.push_back(piece); };
    };

    void Game::addNullPiece(std::string pos)
    {
        int x = Board::colMap2[pos[0]];
        int y = pos[1];
        this->addPiece<NoPiece>(&pos, (x+y) % 2);
    };

    std::tuple<std::string, std::string, std::string, bool> Game::parseMove(std::string move)
    {
        std::string piecePrefixes = "KQBNR";
        BasePiece* piece = remainingPieces[0];
        std::string piecePrefix = "P";
        std::string oldPos = "xx";
        std::string newPos = "xx";
        if (piecePrefixes.find(move[0]) != std::string::npos){
            piecePrefix = move[0];
        }
        bool isCapture = false;
        int len = move.length();
        if (len < 2) { piecePrefix = " "; }
        else {
            newPos = move.substr(len-2);
            oldPos = move;
            if (piecePrefix != "P") { oldPos.erase(0, 1); };
            len = oldPos.length();
            if (len > 2) {
                oldPos.pop_back();
                len--;
                oldPos.pop_back();
                len--;
                if (oldPos.find('x') != std::string::npos) { oldPos.pop_back(); ; isCapture = true; } 
            }
            else { oldPos = "xx"; }
            std::string cols = "abcdefgh";
            std::string rows = "12345678";
            char anyCoord = 'x';
            if (oldPos.length() == 1) { 
                if (cols.find(oldPos[0])) { oldPos.push_back(anyCoord); } 
                else if (rows.find(oldPos[0])) { oldPos.insert(0, &anyCoord); }
            } else if (oldPos.length() == 0) { oldPos = "xx"; };
        }
        return {piecePrefix, oldPos, newPos, isCapture};
    }

    BasePiece* Game::findPiece(std::tuple<std::string, std::string, std::string, bool> moveTuple)
    {
        std::string lookingForPrefix = std::get<0>(moveTuple);
        std::string oldPos = std::get<1>(moveTuple);
        std::string newPos = std::get<2>(moveTuple);
        bool isCapture = std::get<3>(moveTuple);
        std::vector<BasePiece*> matches;
        std::vector<BasePiece*>::iterator it; 
        for (it = remainingPieces.begin(); it != remainingPieces.end(); ++it) {
            BasePiece* piece = *it;
            if (piece->getColour() != currentTurn) { continue; };
            std::string piecePos = piece->getPos();
            bool posMatch;
            if ( oldPos == "xx" ){ posMatch = true; }
            else if (oldPos[0] == 'x' && oldPos[1] == piecePos[1]) { posMatch = true; }
            else if (oldPos[1] == 'x' && oldPos[0] == piecePos[0]) { posMatch = true; }
            else if (oldPos == piecePos) { posMatch = true; }
            else { posMatch = false; };
            if ((piece->getPrefix()) == lookingForPrefix && posMatch && piece->canSeeSquare(newPos, isCapture) ) { 
                matches.push_back(piece);
            };
        };
        if (matches.size() != 1) {
            std::string emptyPos = "xx";
            BasePiece* emptyPiece = new NoPiece(0, " ", emptyPos, gameBoard);
            return emptyPiece;
        };
        return matches[0];
    };
} // namespace Chess