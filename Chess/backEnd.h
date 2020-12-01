#pragma once 

#include <iostream>
#include <cmath>
#include <stdlib.h>
#include "frontEnd.h"

using namespace std;

#define TableSize 8

enum PieceColor { White, Black };
enum PieceKind { KING, QUEEN, ROOK, BISHOP, KNIGHT, PAWN };

class Piece;

string checkPos(int, int, int, int);

void initBackEnd();

struct FIELD
{
    class Piece* placed;
    class Piece* threats[18];
    short ThreadsNumber, ThreatsFromWhiteFigures, ThreatsFromBlackFigures;
} ;

class Piece
{
public:
    Piece(PieceColor c, PieceKind k, short n, char l, struct FIELD** t) : color(c), kind(k), number(n), letter(l), table(t) { position.row = -1; position.column = -1; }
    PieceKind GetKind() { return kind; }
    PieceColor GetColor() { return color; }
    short GetNumber() { return number; }
    short GetLetter() { return letter; }
    struct POSITION
    {
        short row;
        short column;
    };
    struct POSITION GetPosition() { return position; }
    virtual short GetImportance() = 0; // abstract
    virtual void GetPossibleMoves(struct POSITION** pos, short& n) = 0; // abstract
    virtual void MakeMove(struct POSITION pos);
protected:
    virtual bool CheckMove(struct POSITION pos);
    void AddThreat(struct POSITION pos);
    void RemoveThreat();
    struct POSITION position;
    FIELD** table;
    PieceColor color;
    PieceKind kind;
    short number;
    char letter;
}; // Piece

class King : public Piece
{
public:
    King(PieceColor c, PieceKind k, short n, short row, short column, FIELD** t) : Piece(c, k, n, 'K', t), HasBeenMoved(false) { struct POSITION pos; pos.row = row; pos.column = column; MakeMove(pos); }
    ~King() { RemoveThreat(); }
    virtual short GetImportance() { return 32767; }
    virtual void GetPossibleMoves(struct POSITION** pos, short& n);
    virtual void MakeMove(struct POSITION pos);
    bool GetHasBeenMove() { return HasBeenMoved; }
    short GetThreatsNumber() { return (color == Black) ? table[position.row][position.column].ThreatsFromBlackFigures : table[position.row][position.column].ThreatsFromWhiteFigures; }
    bool IsMate();
protected:
    virtual bool CheckMove(struct POSITION pos);
private:
    bool HasBeenMoved;
}; // King

class Rook : public Piece
{
public:
    Rook(PieceColor c, PieceKind k, short n, short row, short column, FIELD** t) : Piece(c, k, n, 'R', t), HasBeenMoved(false) { struct POSITION pos; pos.row = row; pos.column = column; MakeMove(pos); }
    ~Rook() { RemoveThreat(); }
    virtual short GetImportance() { return 5; }
    virtual void GetPossibleMoves(struct POSITION** pos, short& n);
    virtual void MakeMove(struct POSITION pos);
    bool GetHasBeenMove() { return HasBeenMoved; }
protected:
    virtual bool CheckMove(struct POSITION pos);
private:
    bool HasBeenMoved;
}; // Rook

class Pawn : public Piece
{
public:
    Pawn(PieceColor c, PieceKind k, short n, short row, short column, FIELD** t) : Piece(c, k, n, 'P', t), HasBeenMoved(false), LongMoveHasBeenPerformed(false) { struct POSITION pos; pos.row = row; pos.column = column; MakeMove(pos); }
    ~Pawn() { RemoveThreat(); }
    virtual short GetImportance() { return 1; }
    virtual void GetPossibleMoves(struct POSITION** pos, short& n);
    virtual void MakeMove(struct POSITION pos);
    bool GetLongMoveHasBeenPerformed() { return LongMoveHasBeenPerformed; }
protected:
    virtual bool CheckMove(struct POSITION pos);
private:
    bool HasBeenMoved;
    bool LongMoveHasBeenPerformed;
}; // Pawn

class Queen : public Piece
{
public:
    Queen(PieceColor c, PieceKind k, short n, short row, short column, FIELD** t) : Piece(c, k, n, 'Q', t) { struct POSITION pos; pos.row = row; pos.column = column; MakeMove(pos); }
    ~Queen() { RemoveThreat(); }
    virtual short GetImportance() { return 9; }
    virtual void GetPossibleMoves(struct POSITION** pos, short& n);
protected:
    virtual bool CheckMove(struct POSITION pos);
}; // Queen

class Bishop : public Piece
{
public:
    Bishop(PieceColor c, PieceKind k, short n, short row, short column, FIELD** t) : Piece(c, k, n, 'B', t) { struct POSITION pos; pos.row = row; pos.column = column; MakeMove(pos); }
    ~Bishop() { RemoveThreat(); }
    virtual short GetImportance() { return 3; }
    virtual void GetPossibleMoves(struct POSITION** pos, short& n);
protected:
    virtual bool CheckMove(struct POSITION pos);
}; // Bishop

class Knight : public Piece
{
public:
    Knight(PieceColor c, PieceKind k, short n, short row, short column, FIELD** t) : Piece(c, k, n, 'N', t) { struct POSITION pos; pos.row = row; pos.column = column; MakeMove(pos); }
    ~Knight() { RemoveThreat(); }
    virtual short GetImportance() { return 3; }
    virtual void GetPossibleMoves(struct POSITION** pos, short& n);
protected:
    virtual bool CheckMove(struct POSITION pos);
}; // Knight