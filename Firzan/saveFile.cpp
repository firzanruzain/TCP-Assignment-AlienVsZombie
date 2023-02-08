// #include "../pf/helper.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib> // for system()
#include <ctime>   // for time() in srand( time(NULL) );
#include <iomanip> // for setw()
#include <fstream> // save load file
using namespace std;

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
            char objects[] = {' ', ' ', ' ', ' ', ' ', ' ', '^', 'v', '<', 'R', 'P', 'H', '>'};
            int noOfObjects = 13; // number of objects in the objects array
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
            string title = "= Alien VS Zombie =";
            cout << setw((dimX_*2) - ((dimX_*2 - title.length())/2)) << title << endl;
            // for each row
            for (int i = 0; i < dimY_; ++i)
            {
                // display upper border of the row
                cout << "  ";
                for (int j = 0; j < dimX_; ++j)
                {
                    cout << "+-";
                }
                cout << "+" << endl;
                // display row number
                cout << (dimY_ - i) << " ";
                // display cell content and border of each column
                for (int j = 0; j < dimX_; j++)
                {
                    cout << "|" << map_[i][j];
                }
                cout << "|" << endl;
            }
            // display lower border of the last row
            cout << "  ";
            for (int j = 0; j < dimX_; ++j)
            {
                cout << "+-";
            }
            cout << "+" << endl;
            // display column number
            cout << "  ";
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
            cout << "  ";
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
        char getObjectRaw(int x, int y){
            return map_[x][y];
        }
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

int main() {

    Board board;
    board.init(5, 9);
    board.display();

    ofstream myfile;
    cout << "Enter String => ";
    string line;
    cin >> line;
    myfile.open("test.txt");

    myfile << board.getDimX() << endl; // print dimX
    myfile << board.getDimY() << endl << endl;

    for (int i = 0; i<board.getDimY(); i++){
        for (int j = 0; j<board.getDimX(); j++){
            myfile << board.getObjectRaw(i,j) << "|";
        }
        myfile << endl;
    }

    myfile.close();
    return 0;
}