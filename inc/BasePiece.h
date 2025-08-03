#include <string>

class BasePiece
{
    public:
        BasePiece(bool colour, std::string prefix) { clr = colour; prefix = prefix; }; // Constructor
        ~BasePiece(); // Destructor
        
        // getters
        bool getColour() { return clr; };
        char getPRefix() { return prefix; };    

        // setters
        void pieceMoved() { hasMoved = true; };

    private:
        char prefix;
        bool hasMoved = false;
        bool clr; /// 0 = black, 1 = white

};
