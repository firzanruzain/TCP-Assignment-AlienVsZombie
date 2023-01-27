#include "../main/pf/helper.h"
#include <iostream>
using namespace std;

void Pause()
{
    cout << "Pausing Now" << endl;
    pf::Pause();
    cout << endl;
}

void ClearScreen()
{
    pf::ClearScreen();
    cout << endl;
}

void CreateGameBoard()
{
    cout << "Create Game Board" << endl;
    pf::CreateGameBoard();
    pf::ShowGameBoard();
}


int main()
{
    char option;
    ClearScreen();
    cout << "Default Game Settings" << endl;
    cout << "-----------------------" << endl;
    cout << "Board Rows    : 5" << endl;
    cout << "Board Columns : 5" << endl;
    cout << "Zombie Count  : 1" << endl;

    cout << "Do you wish to change game settings? (y/n)? => ";
    cin >> option;
    cout << option;
}