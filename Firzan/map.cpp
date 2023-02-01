#include "../main/pf/helper.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib> // for system()
#include <ctime>   // for time() in srand( time(NULL) );
#include <iomanip> // for setw()
using namespace std;

void Pause()
{
    cout << "Pausing Now" << endl;
    //pf::Pause();
    cout << endl;
}
void ClearScreen()
{
    //pf::ClearScreen();
    cout << endl;
}
void CreateGameBoard()
{
    cout << "Create Game Board" << endl;
    //pf::CreateGameBoard();
    //pf::ShowGameBoard();
}

class Board{
    private:
      vector<vector<char>> map_; // convention to put trailing underscore
    int dimX_, dimY_;          // to indicate private data 

    public:
        Board(int dimX = 15, int dimY = 5){
            init(dimX, dimY);
        };

        void init(int dimX, int dimY){
            dimX_ = dimX;
            dimY_ = dimY;
            char objects[] = {' ', ' ', ' ', ' ', ' ', ' ', 'R', 'P', 'H', ' '};
            int noOfObjects = 10; // number of objects in the objects array
            // create dynamic 2D array using vectors
            map_.resize(dimY_); // create empty rows
            for (int i = 0; i < dimY_; ++i)
            {
                map_[i].resize(dimX_); // resize each row
            }
            // put random characters into the vector array
            for (int i = 0; i < dimY_; ++i)
            {
                for (int j = 0; j < dimX_; ++j)
                {
                    int objNo = rand() % noOfObjects;
                    map_[i][j] = objects[objNo];
                }
            }
        };

        void display() const{
            // comment this out during testing
            // system("cls"); // OR system("clear"); for Linux / MacOS
            cout << " --__--__--__--__--__--__--__--_" << endl;
            cout << " = Curiosity, Welcome to Mars! =" << endl;
            cout << " __--__--__--__--__--__--__--__-" << endl;
            // for each row
            for (int i = 0; i < dimY_; ++i)
            {
                // display upper border of the row
                cout << " ";
                for (int j = 0; j < dimX_; ++j)
                {
                    cout << "+-";
                }
                cout << "+" << endl;
                // display row number
                cout << setw(2) << (dimY_ - i);
                // display cell content and border of each column
                for (int j = 0; j < dimX_; j++)
                {
                    cout << "|" << map_[i][j];
                }
                cout << "|" << endl;
            }
            // display lower border of the last row
            cout << " ";
            for (int j = 0; j < dimX_; ++j)
            {
                cout << "+-";
            }
            cout << "+" << endl;
            // display column number
            cout << " ";
            for (int j = 0; j < dimX_; ++j)
            {
                int digit = (j + 1) / 10;
                cout << " ";
                if (digit == 0)
                    cout << " ";
                else
                    cout << digit;
            }
            cout << endl;
            cout << " ";
            for (int j = 0; j < dimX_; ++j)
            {
                cout << " " << (j + 1) % 10;
            }
            cout << endl << endl;
        };

        int getDimX(){
            return dimX_;
        };
        int getDimY(){
            return dimY_;
        };

        void setDimX(int x){
            dimX_ = x;
        };
        void setDimY(int y){
            dimY_ = y;
        };

        char getObject(int col, int row){
            return map_[dimY_ - row][col - 1];
        };
        void setObject(int col, int row, char object){
            int x = dimY_ - row;
            int y = col -1;

            map_[x][y] = object;
        };

        bool isEmpty(int col, int row){
            int x = dimY_ - row;
            int y = col -1;
            return (map_[x][y] == ' ');
        };
        bool isInsideMap(int col, int row){
            int x = dimY_ - row;
            int y = col -1;
            return ((x>= 0 && x<= dimX_) && (y>= 0 && y<= dimX_));
        };
};

int main()
{
    srand(time(NULL));
    ClearScreen();
    cout << "Default Game Settings" << endl;
    cout << "-----------------------" << endl;
    cout << "Board Rows    : 5" << endl;
    cout << "Board Columns : 9" << endl;
    cout << "Zombie Count  : 1" << endl << endl;
    int rows,cols,zombies;
    rows = 5;
    cols = 9;
    zombies = 1;
    while(true){
        cout << "Do you wish to change game settings? (y/n)? => ";
        char option;
        cin >> option;

        if (option == 'y'){

            change:
            
            cout << "\n\n";

            while(1){
                cout << "Board Rows    : ";
                cin >> rows;
                cout << endl;
                if (rows % 2 == 0){
                    cout << "Use odd number only!!!\n";
                }
                else{
                    break;
                }
            }
            
            while(1){
                cout << "Board Columns : ";
                cin >> cols;
                cout << endl;
                if (cols % 2 == 0){
                    cout << "Use odd number only!!!\n";
                }
                else{
                    break;
                }
            }

            while(1){
                cout << "Zombie Count  : ";
                cin >> zombies;
                cout << endl; 
                if (cols % 2 == 0){
                    cout << "Use odd number only!!!\n";
                }
                else{
                    break;
                }
            }
            
            cout << "Game Settings" << endl;
            cout << "-----------------------" << endl;
            cout << "Board Rows    : " << rows << endl;
            cout << "Board Columns : " << cols << endl;
            cout << "Zombie Count  : " << zombies << endl << endl;
            while(true){
                cout << "Confirm this game settings? (y/n)? => ";
                cin >> option;
                if (option == 'y'){
                    break;
                }
                else if(option == 'n'){
                    goto change;
                }
            }
            break;
        }
        else if (option == 'n'){
            break;
        }
    }

    Board board;
    board.setDimX(cols);
    board.setDimY(rows);

    int x, y;
    x = board.getDimX()/2 + 1;
    y = board.getDimY()/2 + 1;
    
    cout << board.getDimX() << endl;
    cout << x << y;
    
    board.setObject(x, y, 'A');
    board.display();
    
}