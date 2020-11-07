#include <iostream>
#include <cmath>

using namespace std;

#define TableSize 8

enum PieceColor { White, Black };
enum PieceKind { KING, QUEEN, ROOK, BISHOP, KNIGHT, PAWN };

class Piece;

struct FIELD
{
    class Piece* placed;
    class Piece* threads[18];
    short ThreadsNumber;
} **table;

class Piece
{
public:
    Piece(PieceColor c, PieceKind k, short n, struct FIELD** t) : color(c), kind(k), table(t) { position.row = -1; position.column = -1; }
    PieceKind GetKind() { return kind; }
    PieceColor GetColor() { return color; }
    short GetNumber() { return number; }
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
    short number;
}; // Piece

class King : public Piece
{
public:
    King(PieceColor c, PieceKind k, short n, FIELD** t) : Piece(c, k, n, t) { HasBeenMoved = false; }
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
        return false; // полето е заето от фигура със същия цвят
    for (i = 0; i < field.ThreadsNumber; i++)
    {
        if (field.threads[i]->GetColor() != color)
            return false; // полето е заплашено от фигура от другия цвят
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
    struct POSITION* possible = NULL;
    struct FIELD* field;
    short i, j, k, n;
    if ((position.row >= 0) && (position.column >= 0))
    { // not originally placed
        table[position.row][position.column].placed = NULL; // the cell in which the figure was became free
        GetPossibleMoves(&possible, n);
        for (i = 0; i < n; i++)
        { // crawling possible moves
            field = &(table[possible[i].row][possible[i].column]);
            for (j = 0; j < field->ThreadsNumber; j++)
            { // crawling cell threats
                if (field->threads[j]->GetNumber() == number)
                { // j - index of our figure in the array with threats
                    // Remove the j element
                    for (k = j; k < field->ThreadsNumber - 1; k++) {
                        field->threads[k] = field->threads[k + 1];
                    }                     
                    field->ThreadsNumber -= 1;
                    break;
                }
            } // for j...
        } // for i...
        HasBeenMoved = true;
    } 
    position = pos; // the set position becomes current
    table[position.row][position.column].placed = this; // the cell on the dashboard is occupied with the figure
    GetPossibleMoves(&possible, n); // the possible moves (threats) from the new position
    for (i = 0; i < n; i++)
    { // crawling possible moves
        field = &(table[possible[i].row][possible[i].column]);
        // we add the pointer to our figure to the threat array
        field->threads[field->ThreadsNumber++] = this;
    } // for i...
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
            table[row][column].ThreadsNumber = 0;
        }
    } // for line...
    struct Piece::POSITION p;
    p.row = 3;
    p.column = 3;
    class King k(White, KING, 1, table);
    k.MakeMove(p);
    struct Piece::POSITION* possible;
    short i, n;
    possible = NULL;
    k.GetPossibleMoves(&possible, n);
    cout << "n = " << n << endl;
    for (i = 0; i < n; i++)
        cout << "row: " << possible[i].row << ", column: " << possible[i].column << endl;
}