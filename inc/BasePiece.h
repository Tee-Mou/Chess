#include <string>

class BasePiece
{
    public:
        BasePiece(bool colour, std::string name) { clr = colour; name = name; }; // Constructor
        ~BasePiece(); // Destructor
        
        // getters
        bool getColour() { return clr; };
        std::string getName() { return name; };    

        // setters
        void pieceMoved() { hasMoved = true; };

    private:
        std::string name;
        bool hasMoved = false;
        bool clr; /// 0 = black, 1 = white

};
