#pragma once
#include<iostream>
#include <Windows.h>

void printMenu(bool , bool , bool , bool, bool, bool);
void printSettings(bool , bool);
void printLine(int );
void printBoard(bool, std::string error = "noProblem");
void newGame();
void printAbout();
void printHowToPlay();
void playerOneWin();
void playerTwoWin();