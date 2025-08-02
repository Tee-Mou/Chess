#include "BasePiece.h"
#include <list>

class Game
{
    public:
        Game();
        void MakePieces();

        //getters
        std::list<Piece> getActivePiece();

        //setters
        void addActivePiece(Piece piece);

        std::list<Piece> activePieces;


};