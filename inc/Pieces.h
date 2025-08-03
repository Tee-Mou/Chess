#include "BasePiece.h"

class Pawn : public BasePiece{ using BasePiece::BasePiece; };
class King : public BasePiece{ using BasePiece::BasePiece; };
class Queen : public BasePiece{ using BasePiece::BasePiece; };
class Bishop : public BasePiece{ using BasePiece::BasePiece; };
class Knight : public BasePiece{ using BasePiece::BasePiece; };
class Rook : public BasePiece{ using BasePiece::BasePiece; };
class NoPiece : public BasePiece{ using BasePiece::BasePiece; };