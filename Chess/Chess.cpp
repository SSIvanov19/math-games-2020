#include <iostream>
#include <cmath>
#include <stdlib.h>
#include "frontEnd.h"
#include "backEnd.h"

using namespace std;

int main()
{
    //Set text to white
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

    initBackEnd();

    while (true)
    {
        printMenu(true, false, false, false);
    }
}