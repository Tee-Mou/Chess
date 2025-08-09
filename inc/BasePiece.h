#include <string>
#include "Board.h"

namespace Chess{
    class BasePiece
    {
        public:
            BasePiece(bool colour, std::string prefix, std::string pos, Board* board) : mClr( colour ), mPrefix( prefix ), mPos( pos ), mGameBoard( board ) {}; // Constructor
            virtual bool canSeeSquare(std::string pos, bool isCapture) { return false; };
            bool checkLine(std::string pos, bool isCapture, std::string type = "both");
            bool checkForCheck();
            
            // getters
            bool getColour() { return mClr; };
            std::string getPrefix() { return mPrefix; };    
            std::string getPos() { return mPos; };
            bool getHasMoved() { return mHasMoved; };
            bool getEnPassantable() { return mEnPassantable; }
            Board* getBoard() { return mGameBoard; };
            bool getCheck() { return mInCheck; };
            //setters
            void setCheck(bool isCheck) { mInCheck = isCheck; };
            void setPos(std::string pos) { mPos = pos; }
            void pieceMoved() { mHasMoved = true; };
            void setEnPassantable(bool justMoved) { mEnPassantable = justMoved; }

        private:
            bool mInCheck;
            std::string mPrefix;
            Board* mGameBoard;
            std::string mPos;
            bool mHasMoved = false;
            bool mEnPassantable = false; 
            bool mClr; /// 0 = black, 1 = white

    };
} // namespace Chess
