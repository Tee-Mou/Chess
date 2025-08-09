#include "inc/Game.h"

using namespace Chess;

    int main(){
        std::cout << "############## WELCOME TO CHESS ##############\n\n";
        std::string startChar;
        std::cout << "Start game? (Y/N) ";
        std::cin >> startChar;
        std::cout << std::endl;
        std::transform(startChar.begin(), startChar.end(), startChar.begin(), [](unsigned char c) { return std::tolower(c); });
        Game game;
        if (startChar == "n") { 
            std::cout << "Oh..." << std::endl;
            std::getchar();
            std::exit(0); 
        } else if (startChar != "y") { 
            std::cout << "What?? Let's try this again\n\n";
            main();
        }
        
        game = Game();
        game.startGame();
        while (true) { 
            game.printBoard();
            game.turn(); 
        }

        return 0;
    }