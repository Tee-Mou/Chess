#include <string>
#include <list>
#include <map>
#include <vector>
#include <typeinfo>

namespace Chess{
    class BasePiece
    {
        public:
            BasePiece(bool colour, char prefix, std::string pos) { clr = colour; prefix = prefix; pos=pos; }; // Constructor
            ~BasePiece(); // Destructor
            virtual bool canSeeSquare(std::string pos);
            
            // getters
            bool getColour() { return clr; };
            char getPrefix() { return prefix; };    
            std::string getPos() { return pos; };
            bool getHasMoved() { return hasMoved; }

            // setters
            void pieceMoved() { hasMoved = true; };

        private:
            char prefix;
            std::string pos;
            bool hasMoved = false;
            bool clr; /// 0 = black, 1 = white

    };
} // namespace Chess
