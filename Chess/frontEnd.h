#pragma once
#include<iostream>
#include <Windows.h>

//All function are global declare for easier access
void printMenu(bool , bool , bool , bool);
void printSettings(bool , bool);
void printLine(int );
void printBoard(bool, std::string error = "noProblem");
void newGame();
std::string checkPos(short, short, short, short);