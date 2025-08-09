
#include "BasePiece.h"

namespace Chess {
    class Pawn : public BasePiece{ 
        public: 
            Pawn(bool colour, std::string prefix, std::string pos, Board* board); 
            bool canSeeSquare(std::string pos, bool isCapture); 
        private: 
            std::string prefix = "P";
    };

    class King : public BasePiece{ 
        public: 
            King(bool colour, std::string prefix, std::string pos, Board* board);
            bool canSeeSquare(std::string pos, bool isCapture);  
            bool moveIsCheck(std::string pos);
        private:
            std::string prefix = "K";
    };

    class Queen : public BasePiece{ 
        public: 
            Queen(bool colour, std::string prefix, std::string pos, Board* board); 
            bool canSeeSquare(std::string pos, bool isCapture); 
        private: 
            std::string prefix = "Q";
    };

    class Bishop : public BasePiece{ 
        public: 
            Bishop(bool colour, std::string prefix, std::string pos, Board* board); 
            bool canSeeSquare(std::string pos, bool isCapture); 
        private: 
            std::string prefix = "B";
    };

    class Knight : public BasePiece{ 
        public: 
            Knight(bool colour, std::string prefix, std::string pos, Board* board); 
            bool canSeeSquare(std::string pos, bool isCapture); 
        private: 
            std::string prefix = "N";
    };

    class Rook : public BasePiece{ 
        public: 
            Rook(bool colour, std::string prefix, std::string pos, Board* board); 
            bool canSeeSquare(std::string pos, bool isCapture); 
        private: 
            std::string prefix = "R"; 
    };

    class NoPiece : public BasePiece{ 
        public: 
            NoPiece(bool colour, std::string prefix, std::string pos, Board* board);
            bool canSeeSquare(std::string pos, bool isCapture);
        private: 
            std::string prefix = " ";
    };

}