#include "../inc/BasePiece.h"

namespace Chess {

    bool BasePiece::checkLine(std::string pos, bool isCapture, std::string type){
        int dir = -1; // U = 0, UR = 1 R = 2, DR = 3, D = 4, DL = 5, L = 6, UL = 7;
        bool pathClear = true;
        if (type == "cardinal" || type == "both"){
            if (pos[0] == mPos[0] && pos[1] > mPos[1]) { dir = 0; }
            if (pos[0] > mPos[0] && pos[1] == mPos[1]) { dir = 2; }
            if (pos[0] == mPos[0] && pos[1] < mPos[1]) { dir = 4; }
            if (pos[0] < mPos[0] && pos[1] == mPos[1]) { dir = 6; }
        }
        if (type == "diagonal" || type == "both"){
            if (pos[0] > mPos[0] && pos[1] > mPos[1]) { dir = 1; }
            if (pos[0] > mPos[0] && pos[1] < mPos[1]) { dir = 3; }
            if (pos[0] < mPos[0] && pos[1] < mPos[1]) { dir = 5; }
            if (pos[0] < mPos[0] && pos[1] > mPos[1]) { dir = 7; }
        }
        if (dir == -1) { return false; }
        std::string checkPos = "xx";
        for (int i = 1; i <= 7; i++ ){
            switch (dir)
            {
                case 0: checkPos[0] = mPos[0]; checkPos[1] = mPos[1] + i; break;
                case 1: checkPos[0] = mPos[0] + i; checkPos[1] = mPos[1] + i; break;
                case 2: checkPos[0] = mPos[0] + i; checkPos[1] = mPos[1]; break;
                case 3: checkPos[0] = mPos[0] + i; checkPos[1] = mPos[1] - i; break;
                case 4: checkPos[0] = mPos[0]; checkPos[1] = mPos[1] - i; break;
                case 5: checkPos[0] = mPos[0] - i; checkPos[1] = mPos[1] - i; break;
                case 6: checkPos[0] = mPos[0] - i; checkPos[1] = mPos[1]; break;
                case 7: checkPos[0] = mPos[0] - i; checkPos[1] = mPos[1] + i; break;
            }
            if (checkPos[0] < 'a' || checkPos[0] > 'h' || checkPos[1] < '1' || checkPos[1] > '8' || !pathClear) { break; }
            std::string prefix = mGameBoard->getSquare(checkPos)->getPrefix();
            if (prefix != " ") { pathClear = false; }
            if (checkPos == pos 
            && prefix != " " 
            && isCapture
            && mGameBoard->getSquare(checkPos)->getColour() == !this->getColour()) { return true; }
            else if (checkPos == pos 
            && prefix == " " 
            && !isCapture) { return true; }
        };
        return false;
    }

    bool BasePiece::checkForCheck() {
        std::string checkPrefix;
        std::string checkPos;

        //Checked by Pawn?
        checkPrefix = "P";
        checkPos = mPos;
        checkPos[1] = mClr ? mPos[1] + 1: mPos[1] - 1;
        if (checkPos[1] >= '1' && checkPos[1] <= '8') {
            checkPos[0]--;
            if (checkPos[0] >= 'a') { 
                if (mGameBoard->getSquare(checkPos)->getPrefix() == checkPrefix 
                    && mGameBoard->getSquare(checkPos)->getColour() != mClr) { 
                        return true; 
                }; 
            }
            checkPos[0] += 2;
            if (checkPos[0] <= 'h') { 
                if (mGameBoard->getSquare(checkPos)->getPrefix() == checkPrefix 
                && mGameBoard->getSquare(checkPos)->getColour() != mClr) { 
                    return true; 
                }; 
            }
        };

        // Checked by Knight?
        checkPrefix = "N";
        checkPos = "xx";
        int x = Board::colMap2[mPos[0]];
        int y = mPos[1] - '0';
        for(int i = x-2; i <= x+2; i++ ){
            for(int j = y-2; j <= y+2; j++ ){
                if (j < 1 || j > 8 || i < 1 || i > 8) { continue; }
                checkPos[0] = Board::colMap1[i][0]; checkPos[1] = j + '0';
                int squareProd;
                squareProd = std::abs(j - y) * std::abs(j - y) + std::abs(i - x) * std::abs(i - x);
                if (mGameBoard->getSquare(checkPos)->getPrefix() == checkPrefix 
                    && mGameBoard->getSquare(checkPos)->getColour() != mClr
                    && squareProd == 5 ) { return true; }
            }
        }

        // Checked by Queen/Bishop/Rook?
        std::vector<int> blocked;
        for (int i = 1; i <= 7; i++ ){
            for (int dir = 0; dir <= 7; dir++) {
                if (std::find(blocked.begin(), blocked.end(), dir) != blocked.end()) { continue; }
                switch (dir)
                {
                    case 0: checkPos[0] = mPos[0]; checkPos[1] = mPos[1] + i; checkPrefix = "R"; break;
                    case 1: checkPos[0] = mPos[0] + i; checkPos[1] = mPos[1] + i; checkPrefix = "B"; break;
                    case 2: checkPos[0] = mPos[0] + i; checkPos[1] = mPos[1]; checkPrefix = "R"; break;
                    case 3: checkPos[0] = mPos[0] + i; checkPos[1] = mPos[1] - i; checkPrefix = "B"; break;
                    case 4: checkPos[0] = mPos[0]; checkPos[1] = mPos[1] - i; checkPrefix = "R"; break;
                    case 5: checkPos[0] = mPos[0] - i; checkPos[1] = mPos[1] - i; checkPrefix = "B"; break;
                    case 6: checkPos[0] = mPos[0] - i; checkPos[1] = mPos[1]; checkPrefix = "R"; break;
                    case 7: checkPos[0] = mPos[0] - i; checkPos[1] = mPos[1] + i; checkPrefix = "B"; break;
                }
                if (checkPos[0] < 'a' || checkPos[0] > 'h' || checkPos[1] < '1' || checkPos[1] > '8' ) { continue; }
                std::string prefix = mGameBoard->getSquare(checkPos)->getPrefix();
                if (prefix != " ") { blocked.push_back(dir); }
                bool colour = mGameBoard->getSquare(checkPos)->getColour();
                if ((prefix == checkPrefix || prefix == "Q") 
                    && colour != mClr) { return true; }
            }
        };
        return false;
    }

} // namespace Chess