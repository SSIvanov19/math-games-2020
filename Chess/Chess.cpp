#include <iostream>
#include <Windows.h>
#include "frontEnd.h"
#include "backEnd.h"

using namespace std;

int main()
{
    //Set text to white
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

	//Initiate backend
    initBackEnd();

    while (true)
    {
    	//print menu
        printMenu(true, false, false, false);
    }
}