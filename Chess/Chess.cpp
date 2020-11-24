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
    virtual short GetImportance() { return 32767; }
    virtual void GetPossibleMoves(struct POSITION** pos, short& n);
    virtual void MakeMove(struct POSITION pos);
protected:
    virtual bool CheckMove(struct POSITION pos);
private:
    bool HasBeenMoved;
}; // King

class Rook : public Piece
{
public:
    Rook(PieceColor c, PieceKind k, short n, short row, short column, FIELD** t) : Piece(c, k, n, 'R', t), HasBeenMoved(false) { struct POSITION pos; pos.row = row; pos.column = column; MakeMove(pos); }
    virtual short GetImportance() { return 5; }
    virtual void GetPossibleMoves(struct POSITION** pos, short& n);
    virtual void MakeMove(struct POSITION pos);
protected:
    virtual bool CheckMove(struct POSITION pos);
private:
    bool HasBeenMoved;
}; // Rook

class Pawn : public Piece
{
public:
    Pawn(PieceColor c, PieceKind k, short n, short row, short column, FIELD** t) : Piece(c, k, n, 'P', t), HasBeenMoved(false), LongMoveHasBeenPerformed(false) { struct POSITION pos; pos.row = row; pos.column = column; MakeMove(pos); }
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
    virtual short GetImportance() { return 9; }
    virtual void GetPossibleMoves(struct POSITION** pos, short& n);
protected:
    virtual bool CheckMove(struct POSITION pos);
}; // Queen

class Bishop : public Piece
{
public:
    Bishop(PieceColor c, PieceKind k, short n, short row, short column, FIELD** t) : Piece(c, k, n, 'B', t) { struct POSITION pos; pos.row = row; pos.column = column; MakeMove(pos); }
    virtual short GetImportance() { return 3; }
    virtual void GetPossibleMoves(struct POSITION** pos, short& n);
protected:
    virtual bool CheckMove(struct POSITION pos);
}; // Bishop

class Knight : public Piece
{
public:
    Knight(PieceColor c, PieceKind k, short n, short row, short column, FIELD** t) : Piece(c, k, n, 'N', t) { struct POSITION pos; pos.row = row; pos.column = column; MakeMove(pos); }
    virtual short GetImportance() { return 3; }
    virtual void GetPossibleMoves(struct POSITION** pos, short& n);
protected:
    virtual bool CheckMove(struct POSITION pos);
}; // Knight

bool Piece::CheckMove(struct POSITION pos)
{
    if ((position.row == pos.row) && (position.column == pos.column))
        return false;
    if ((pos.row < 0) || (pos.row >= TableSize) || (pos.column < 0) || (pos.column >= TableSize))
        return false;
    struct FIELD field = table[pos.row][pos.column];
    if ((field.placed != NULL) && (field.placed->GetColor() == color))
        return false; // полето е заето от фигура със същия цвят
    return true;
} // Piece::CheckMove

void Piece::MakeMove(struct POSITION pos)
{
    //cout << "Piece::MakeMove" << endl;
    struct POSITION* possible = NULL;
    struct FIELD* field;
    short i, j, k, n;
    if ((position.row >= 0) && (position.column >= 0))
    { // не е първоначално поставяне
        //cout << "removing threads" << endl;
        table[position.row][position.column].placed = NULL; // клетката, в която е била фигурата става празна
        GetPossibleMoves(&possible, n);
        for (i = 0; i < n; i++)
        { // обхождане на възможните ходове
            field = &(table[possible[i].row][possible[i].column]);
            for (j = 0; j < field->ThreadsNumber; j++)
            { //обхождане на заплахите за клетката
                if (field->threads[j]->GetNumber() == number)
                { // j - индекс на нашата фигура в масива със заплахите
                    // премахваме j-тия елемент
                    for (k = j; k < field->ThreadsNumber - 1; k++)
                        field->threads[k] = field->threads[k + 1];
                    field->ThreadsNumber -= 1;
                    break;
                }
            } // for j...
        } // for i...
    }
    //cout << "placing the figure" << endl;
    position = pos; // текуща става зададената позиция
    table[position.row][position.column].placed = this; // клетката от таблото е заета с фигурата
    GetPossibleMoves(&possible, n); // възможните ходове (заплахите) от новата позиция
    //cout << n << " possible moves was found" << endl;
    for (i = 0; i < n; i++)
    { // обхождане на възможните ходове
        field = &(table[possible[i].row][possible[i].column]);
        // добавяне на указателя към нашата фигура към масива със заплахите
        field->threads[field->ThreadsNumber++] = this;
    } // for i...
    //cout << "end of Piece::MakeMove" << endl;
} // Piece::MakeMove

// Figure King

void King::MakeMove(struct POSITION pos)
{
    //cout << "King::MakeMove" << endl;
    Piece::MakeMove(pos);
    HasBeenMoved = true;
} // King::MakeMove

bool King::CheckMove(struct POSITION pos)
{
    if (!Piece::CheckMove(pos))
        return false;
    short i, row = position.row, column = position.column;
    struct FIELD field = table[pos.row][pos.column];
    for (i = 0; i < field.ThreadsNumber; i++)
    {
        if (field.threads[i]->GetColor() != color)
            return false; // полето е заплашено от фигура от другия цвят
    }
    if ((abs(row - pos.row) > 1) || (abs(column - pos.column) > 1))
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
    cout << "end of King::GetPossibleMoves" << endl;
} // King::GetPossibleMoves

// Figure Rook

void Rook::MakeMove(struct POSITION pos)
{
    Piece::MakeMove(pos);
    HasBeenMoved = true;
} // Rook::MakeMove

bool Rook::CheckMove(struct POSITION pos)
{
    if (!Piece::CheckMove(pos))
        return false;
    short i, row = position.row, column = position.column;
    if ((pos.row != row) && (pos.column != column))
        return false;
    if (pos.row == row)
    { // движение по реда
        if (pos.column < column)
        { // движение наляво
            for (i = column - 1; i > pos.column; i--)
                if (table[row][i].placed != NULL)
                    return false; // опит да се прескочи фигура
        }
        else
        { // движение надясно
            for (i = column + 1; i < pos.column; i++)
                if (table[row][i].placed != NULL)
                    return false; // опит да се прескочи фигура
        }
    } // движение по реда
    if (pos.column == column)
    { // движение по колоната
        if (pos.row < row)
        { // движение надолу
            for (i = row - 1; i > pos.row; i--)
                if (table[i][column].placed != NULL)
                    return false; // опит да се прескочи фигура
        }
        else
        { // движение нагоре
            for (i = row + 1; i < pos.row; i++)
                if (table[i][column].placed != NULL)
                    return false; // опит да се прескочи фигура
        }
    } // движение по колоната
    return true;
} // Rook::CheckMove

void Rook::GetPossibleMoves(struct POSITION** pos, short& n)
{
    struct POSITION positions[14];
    struct POSITION current;
    short i;
    n = 0;
    current.row = position.row;
    for (current.column = 0; current.column < TableSize; current.column++)
    {
        if (CheckMove(current))
            positions[n++] = current;
    }
    current.column = position.column;
    for (current.row = 0; current.row < TableSize; current.row++)
    {
        if (CheckMove(current))
            positions[n++] = current;
    }
    if (n > 0)
    {
        *pos = new POSITION[n];
        for (i = 0; i < n; i++)
            (*pos)[i] = positions[i];
    }
    else
        *pos = NULL;
} // Rook::GetPossibleMoves

// Figure Pawn

void Pawn::MakeMove(struct POSITION pos)
{
    if (abs(position.column - pos.column) > 1)
        LongMoveHasBeenPerformed = true;
    if ((position.row >= 0) && (position.column >= 0))
        HasBeenMoved = true;
    Piece::MakeMove(pos);
} // Pawn::MakeMove

bool Pawn::CheckMove(struct POSITION pos)
{
    if (!Piece::CheckMove(pos))
        return false;
    class Piece* AnotherFigure;
    short i, jump, ColumnDistance, row = position.row, column = position.column;
    i = abs(row - pos.row);
    if (i > 1)
        return false;
    ColumnDistance = abs(column - pos.column);
    if (i == 1)
    { // вземане на фигура
        if (ColumnDistance > 1)
            return false;
        AnotherFigure = table[pos.row][pos.column].placed;
        if ((AnotherFigure == NULL) || (AnotherFigure->GetColor() == color))
            return false; // полето не  е заето или там стои фигура от същия цвят
        if (ColumnDistance == 0)
            if (AnotherFigure->GetKind() == PAWN)
            { // пасианс
                class Pawn* AnotherPawn = dynamic_cast<class Pawn*>(AnotherFigure);
                if (!AnotherPawn->GetLongMoveHasBeenPerformed())
                    return false; // другата пешка не е правила ход през поле
            }
            else
                return false; // другата фигура не е пешка
    }
    else
    { // ход без вземане на фигура
        jump = (HasBeenMoved) ? 1 : 2; // с колко колони може да е ходът
        if (ColumnDistance > jump)
            return false;
        if (color == White)
        {
            if (pos.column <= column)
                return false;
            for (i = column + 1; i <= pos.column; i++)
                if (table[row][i].placed != NULL)
                    return false; //по пътя има фигура
        }
        else
        { // color != White
            if (column <= pos.column)
                return false;
            for (i = column - 1; i >= pos.column; i--)
                if (table[row][i].placed != NULL)
                    return false; //по пътя има фигура
        }
    }

    return true;
} // Pawn::CheckMove

void Pawn::GetPossibleMoves(struct POSITION** pos, short& n)
{
    struct POSITION positions[6];
    struct POSITION current;
    short i, direction;
    direction = (color == White) ? 1 : -1; // посока на движение
    n = 0;
    // проверка на ходовете по посока на движение
    current.row = position.row;
    current.column = position.column + direction;
    cout << "row: " << current.row << ", column:" << current.column << endl;
    if (CheckMove(current))
        positions[n++] = current;
    else
        cout << "impossible" << endl;
    current.column += direction;
    if (CheckMove(current))
        positions[n++] = current;
    // проверка на ходовете при вземане на фигура
    for (current.column = position.column + direction, current.row = position.row - 1; current.row <= position.row + 1; current.row += 2)
        if (CheckMove(current))
            positions[n++] = current;
    // проверка на ходовете при пасианс
    for (current.column = position.column, current.row = position.row - 1; current.row <= position.row + 1; current.row += 2)
        if (CheckMove(current))
            positions[n++] = current;
    if (n > 0)
    {
        *pos = new POSITION[n];
        for (i = 0; i < n; i++)
            (*pos)[i] = positions[i];
    }
    else
        *pos = NULL;
} // Pawn::GetPossibleMoves

// Figure Bishop

bool Bishop::CheckMove(struct POSITION pos)
{
    if (!Piece::CheckMove(pos))
        return false;
    short RowStep, ColumnStep, row = position.row, column = position.column;
    if ((row + column != pos.row + pos.column) && (row - column != pos.row - pos.column))
        return false; // полето, на което е фигурата и полето, на което ще се прави ход, не са на един и същ диагонал
            // проверка дали няма фигура на полетата между това, на което е фигурата и това, на което се прави ход
    RowStep = (pos.row > row) ? 1 : -1;
    ColumnStep = (pos.column > column) ? 1 : -1;
    for (row += RowStep, column += ColumnStep; table[row][column].placed == NULL; row += RowStep, column += ColumnStep)
        if (row == pos.row)
            break;
    if (row != pos.row)
        return false; // по пътя към полето, на което се прави ход, има фигура
    else // достигнато е полето, на което се прави ход
        if ((table[row][column].placed != NULL) && (table[row][column].placed->GetColor() == color))
            return false; // фигурата в полето, на което се прави ход, е от същия цвят

    return true;
} // Bishop::CheckMove

void Bishop::GetPossibleMoves(struct POSITION** pos, short& n)
{
    struct POSITION positions[13];
    struct POSITION current;
    n = 0;
    for (current.row = position.row + position.column, current.column = 0; current.row >= 0; current.row--, current.column++) // движение по левия диагонал
        if (CheckMove(current))
            positions[n++] = current;
    for (current.row = position.row - position.column, current.column = 0; (current.row < TableSize) && (current.column < TableSize); current.row++, current.column++) // движение по десния диагонал
        if (CheckMove(current))
            positions[n++] = current;
    if (n > 0)
    {
        *pos = new POSITION[n];
        for (short i = 0; i < n; i++)
            (*pos)[i] = positions[i];
    }
    else
        *pos = NULL;
} // Bishop::GetPossibleMoves

// Figure Knight

bool Knight::CheckMove(struct POSITION pos)
{
    if (!Piece::CheckMove(pos))
        return false;
    short RowDisparity = abs(position.row - pos.row);
    short ColumnDisparity = abs(position.column - pos.column);
    if (RowDisparity == ColumnDisparity)
        return false;
    if ((RowDisparity < 1) || (RowDisparity > 2) || (ColumnDisparity < 1) || (ColumnDisparity > 2))
        return false;
    return true;
} // Knight::CheckMove

void Knight::GetPossibleMoves(struct POSITION** pos, short& n)
{
    struct POSITION positions[8];
    struct POSITION current;
    short RowStep, ColumnStep;
    n = 0;
    for (RowStep = 1; RowStep <= 2; RowStep++)
    {
        ColumnStep = (RowStep == 1) ? 2 : 1;
        for (current.row = position.row - RowStep; current.row <= position.row + RowStep; current.row += (RowStep + RowStep))
            for (current.column = position.column - ColumnStep; current.column <= position.column + ColumnStep; current.column += (ColumnStep + ColumnStep))
                if (CheckMove(current))
                    positions[n++] = current;
    } // for RowStep ...
    if (n > 0)
    {
        *pos = new POSITION[n];
        for (short i = 0; i < n; i++)
            (*pos)[i] = positions[i];
    }
    else
        *pos = NULL;
} // Knight::GetPossibleMoves

// Figure Queen

bool Queen::CheckMove(struct POSITION pos)
{
    if (!Piece::CheckMove(pos))
        return false;
    short i, j, row = position.row, column = position.column;
    if ((pos.row != row) && (pos.column != column))
        return false;
    if (pos.row == row)
    { // движение по реда
        if (pos.column < column)
        { // движение наляво
            for (i = column - 1; i > pos.column; i--)
                if (table[row][i].placed != NULL)
                    return false; // опит да се прескочи фигура
        }
        else
        { // движение надясно
            for (i = column + 1; i < pos.column; i++)
                if (table[row][i].placed != NULL)
                    return false; // опит да се прескочи фигура
        }
    } // движение по реда
    if (pos.column == column)
    { // движение по колоната
        if (pos.row < row)
        { // движение надолу
            for (i = row - 1; i > pos.row; i--)
                if (table[i][column].placed != NULL)
                    return false; // опит да се прескочи фигура
        }
        else
        { // движение нагоре
            for (i = row + 1; i < pos.row; i++)
                if (table[i][column].placed != NULL)
                    return false; // опит да се прескочи фигура
        }
    } // движение по колоната

    if (abs(row - pos.row) == abs(column - pos.column)) {
        if ((pos.row > row) && (pos.column > column)) {
            for (i = row + 1, j = column + 1; i < pos.row, j < pos.column; i++, j++)
                if (table[i][j].placed != NULL)
                    return false; // опит да се прескочи фигура
        }
        else {
            for (i = row - 1, j = column - 1; i > pos.row, j > pos.column; i--, j--)
                if (table[i][j].placed != NULL)
                    return false; // опит да се прескочи фигура
        }
        if ((pos.row > row) && (pos.column < column)) {
            for (i = row + 1, j = column - 1; i < pos.row, j > pos.column; i++, j--)
                if (table[i][j].placed != NULL)
                    return false; // опит да се прескочи фигура
        }
        else {
            for (i = row - 1, j = column + 1; i > pos.row, j < pos.column; i--, j++)
                if (table[i][j].placed != NULL)
                    return false; // опит да се прескочи фигура
        }
    }

    return true;
} // Queen::CheckMove

void Queen::GetPossibleMoves(struct POSITION** pos, short& n)
{
    struct POSITION positions[28];
    struct POSITION current;
    short i;
    n = 0;
    current.row = position.row;
    for (current.column = 0; current.column < TableSize; current.column++)
    {
        if (CheckMove(current))
            positions[n++] = current;
    }
    current.column = position.column;
    for (current.row = 0; current.row < TableSize; current.row++)
    {
        if (CheckMove(current))
            positions[n++] = current;
    }
    if (n > 0)
    {
        *pos = new POSITION[n];
        for (i = 0; i < n; i++)
            (*pos)[i] = positions[i];
    }
    else
        *pos = NULL;
} // Queen::GetPossibleMoves

void printLine(int row)
{
    const char whiteSquare = 0xDB;
    const char blackSquare = 0xFF;

    if (row % 2 == 0)
    {
        for (int subRow = 1; subRow <= 3; subRow++)
        {
            for (int cells = 1; cells <= 4; cells++)
            {
                for (int subCells = 1; subCells <= 6; subCells++)
                {
                    if (subCells == 3 && subRow == 2)
                    {
                        cout << whiteSquare;
                    }
                    else
                    {
                        cout << whiteSquare;
                    }
                }

                for (int subCells = 1; subCells <= 6; subCells++)
                {
                    cout << blackSquare;
                }
            }

            if (subRow == 2)
            {
                cout << "   " << row;
            }
            cout << endl << " ";
        }
    }
    if (row % 2 != 0)
    {
        for (int subRow = 1; subRow <= 3; subRow++)
        {
            for (int cells = 1; cells <= 4; cells++)
            {
                for (int subCells = 1; subCells <= 6; subCells++)
                {
                    cout << blackSquare;
                }

                for (int subCells = 1; subCells <= 6; subCells++)
                {
                    cout << whiteSquare;
                }
            }
            if (subRow == 2)
            {
                cout << "   " << row;
            }

            cout << endl << " ";
        }
    }
}

void printBoard()
{
    for (int row = 8; row >= 1; row--)
    {
        printLine(row);
    }
}

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
    } // for row...

    cout << " ";
    printBoard();

    struct Piece::POSITION* possible;
    short i, n;

    possible = NULL;

    class Piece* WhiteFigures[16];
    WhiteFigures[0] = new class King(White, KING, 1, 4, 0, table);
    cout << "King - OK" << endl;
    WhiteFigures[1] = new class Queen(White, QUEEN, 2, 3, 0, table);
    cout << "Queen - OK" << endl;
    WhiteFigures[2] = new class Rook(White, ROOK, 3, 7, 0, table);
    WhiteFigures[3] = new class Rook(White, ROOK, 4, 0, 0, table);
    cout << "Rooks - OK" << endl;
    WhiteFigures[4] = new class Bishop(White, BISHOP, 5, 2, 0, table);
    WhiteFigures[5] = new class Bishop(White, BISHOP, 6, 5, 0, table);
    cout << "Bishops - OK" << endl;
    WhiteFigures[6] = new class Knight(White, KNIGHT, 4, 5, 0, table);
    WhiteFigures[7] = new class Knight(White, KNIGHT, 8, 6, 0, table);
    cout << "Knights - OK" << endl;
    for (i = 8; i < 16; i++)
        WhiteFigures[i] = new class Pawn(White, PAWN, i + 1, i - 8, 1, table);
    cout << "Pawns - OK" << endl;

    //delete possible;
    //possible = NULL;
    class Piece* BlackFigures[16];
    BlackFigures[0] = new class King(Black, KING, 17, 4, 7, table);
    BlackFigures[1] = new class Queen(Black, QUEEN, 18, 3, 7, table);
    BlackFigures[2] = new class Rook(Black, ROOK, 19, 7, 7, table);
    BlackFigures[3] = new class Rook(Black, ROOK, 20, 0, 7, table);
    BlackFigures[4] = new class Bishop(Black, BISHOP, 21, 2, 7, table);
    BlackFigures[5] = new class Bishop(Black, BISHOP, 22, 5, 7, table);
    BlackFigures[6] = new class Knight(Black, KNIGHT, 23, 1, 7, table);
    BlackFigures[7] = new class Knight(Black, KNIGHT, 24, 6, 7, table);
    for (i = 8; i < 16; i++)
        BlackFigures[i] = new class Pawn(Black, PAWN, i + 17, i - 8, 6, table);

    //BlackFigures[8]->GetPossibleMoves(&possible, n);
}