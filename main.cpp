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

        system("cls");
        std::cin.ignore();
        int state = 1;
        std::cout << "========================================================================\n";
        while (state != 2){
            state = game.turn();
            if (state == 1) { 
                game.nextTurn(); 
                std::cout << "========================================================================\n";
            }
            else if (state == 0) { std::cout << "=================Entered invalid move, please try again=================\n"; }
        }
        game.gameOver();
        return 0;
    }