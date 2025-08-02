class Piece
{
    public:
        Piece(bool colour, int xposition, int yposition); // Constructor
        ~Piece(); // Destructor
        
        // getters
        bool getIsCaptured() { return isCaptured; };
        bool getClr() { return clr; };
        int getXpos() { return xpos; };
        int getYpos() { return ypos; };

        // setters
        void switchIsCaptured() { !isCaptured; }
        void setPos(int newXpos, int newYpos)  { xpos = newXpos; ypos = newYpos; };

    private:
        bool isCaptured = false;
        bool clr;
        int xpos;
        int ypos;
};
