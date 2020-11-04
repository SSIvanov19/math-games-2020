#include <iostream>
#include <cmath>

using namespace std;

#define TableSize 8

enum PieceColor { White, Black };
enum PieceKind { KING, QUEEN, ROOK, BISHOP, KNIGHT, PAWN }; // denote the values ​​of the figures

class Piece;

struct FIELD
{
    class Piece* placed;
    class Piece* threats[18];
    short ThreatsNumber;
} **table; // table[TableSize][TableSize]

class Piece
{
public:
    Piece(PieceColor c, PieceKind k, struct FIELD **t) : color(c), kind(k), table(t) { position.row = -1; position.column = -1; }
    PieceKind GetKind() { return kind; }
    PieceColor GetColor() { return color; }
    struct POSITION
    {
        short row;
        short column;
    };
    virtual short GetImportance() = 0; // abstract
    virtual void GetPossibleMoves(struct POSITION** pos, short& n) = 0; // abstract
    virtual void MakeMove(struct POSITION pos) = 0; // abstract
protected:
    virtual bool CheckMove(struct POSITION pos) = 0; // abstract
    struct POSITION position;
    FIELD** table;
    PieceColor color;
    PieceKind kind;
}; // Piece

class King : public Piece
{
public:
    King(PieceColor c, PieceKind k, FIELD** t) : Piece(c, k, t) { HasBeenMoved = false; }
    virtual short GetImportance() { return 32767; }
    virtual void GetPossibleMoves(struct POSITION** pos, short& n);
    virtual void MakeMove(struct POSITION pos);
protected:
    virtual bool CheckMove(struct POSITION pos);
private:
    bool HasBeenMoved;
}; // King

bool King::CheckMove(struct POSITION pos)
{
    if ((pos.row < 0) || (pos.row >= TableSize) || (pos.column < 0) || (pos.column >= TableSize))
        return false;
    short i, row = position.row, column = position.column;
    struct FIELD field = table[pos.row][pos.column];
    if ((field.placed != NULL) && (field.placed->GetColor() == color))
        return false; // the field is occupied by a figure of the same color
    for (i = 0; i < field.ThreatsNumber; i++)
    {
        if (field.threats[i]->GetColor() != color)
            return false; // the field is threatened by a figure of the other color
    }
    if ((abs(row - pos.row) > 1) || (abs(column - pos.column) > 1))
        return false;
    if ((row == pos.row) && (column == pos.column))
        return false;
    return true;
} // King::CheckMove

void King::GetPossibleMoves(struct POSITION** pos, short& n)
{
    struct POSITION positions[8];
    struct POSITION current;
    short i;
    n = 0;
    for (current.row = position.row - 1; current.row <= position.row + 1; current.row++)
    {
        for (current.column = position.column - 1; current.column <= position.column + 1; current.column++)
        {
            if (CheckMove(current))
                positions[n++] = current;
        }
    }
    if (n > 0)
    {
        *pos = new POSITION[n];
        for (i = 0; i < n; i++)
            (*pos)[i] = positions[i];
    }
    else
        *pos = NULL;
} // King::GetPossibleMoves

void King::MakeMove(struct POSITION pos)
{
    if ((position.row >= 0) && (position.column >= 0))
    {
        table[position.row][position.column].placed = NULL;
        HasBeenMoved = true;
    }
    position = pos;
    table[position.row][position.column].placed = this;
} // King::MakeMove

int main()
{
    short row, column;
    table = new FIELD * [TableSize];
    for (row = 0; row < TableSize; row++)
    {
        table[row] = new FIELD[TableSize];
        for (column = 0; column < TableSize; column++)
        {
            table[row][column].placed = NULL;
            table[row][column].ThreatsNumber = 0;
        }
    } // for row...
    struct Piece::POSITION p;
    p.row = 3;
    p.column = 3;
    class King k(White, KING, table);
    k.MakeMove(p);
    struct Piece::POSITION* possible;
    short i, n;
    possible = NULL;
    k.GetPossibleMoves(&possible, n);
    cout << "n = " << n << endl;
    for (i = 0; i < n; i++)
        cout << "row: " << possible[i].row << ", column: " << possible[i].column << endl;
}