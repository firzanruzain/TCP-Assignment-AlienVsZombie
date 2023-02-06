// ********************************************************* 
// Course: TCP1101 PROGRAMMING FUNDAMENTALS 
// Year: Trimester 1, 2022/23 (T2215) 
// Lab: TxxL 
// Names: Muhammad Firzan Ruzain Bin Firdus | Zharfan Mirza Hafiy Ma Bin Suhaidi | Farris Aiman Bin Mohd Harris 
// IDs: 1211103220 | 1211101006 | 1211102060 
// Emails: 1211103220@student.mmu.edu.my | 1211101006@student.mmu.edu.my | 1211102060@student.mmu.edu.my 
// Phones: 01127282086 | 0136311409 | 0196639322 
// ********************************************************* 

#include "pf/helper.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib> // for system()
#include <ctime>   // for time() in srand( time(NULL) );
#include <iomanip> // for setw()
using namespace std;

int ClearScreen()
    {
        #if defined(_WIN32)
            return std::system("cls");
        #elif defined(__linux__) || defined(__APPLE__)
            return std::system("clear");
        #endif
    }

int Pause()
{
    #if defined(_WIN32)
        return std::system("pause");
    #elif defined(__linux__) || defined(__APPLE__)
        return std::system(R"(read -p "Press any key to continue . . . " dummy)");
    #endif
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
            cout << " = Alien VS Zombie =" << endl;
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

class Player{
    private:
        int x_, y_;
        int life_, attack_;
    public:
        Player(Board &board, int life = 100, int attack = 0){
            x_ = board.getDimX()/2 + 1;
            y_ = board.getDimY()/2 + 1; 
            life_ = life;
            attack_ = attack;
            board.setObject(x_, y_, 'A');
        }
        int getX(){
            return x_;
        }
        int getY(){
            return y_;
        }
        void setLife(int life){
        life_ = life;
        }
        void setAttack(int attack){
            attack_ = attack;
        }
        int getLife(){
            return life_;
        }
        int getAttack(){
            return attack_;
        }
        void move(char dir, Board &board){

            char possibleHeading[] = {'^', '>', '<', 'v'};
            char heading = possibleHeading[rand() % 4];
            cout << heading << " ";

            char objects[] = {' ', ' ', ' ', ' ', ' ', ' ', 'R', 'P', 'H', ' '};
            int noOfObjects = 10; // number of objects in the objects array
            int objNo = rand() % noOfObjects;
            board.setObject(x_, y_, objects[objNo]);

            switch (dir)
            {
            case '^':
                y_ += 1;
                cout << "Moving up" << endl;
                break;
            case '>':
                x_ += 1;
                cout << "Moving right" << endl;
                break;
            case '<':
                x_ -= 1;
                cout << "Moving left" << endl;
                break;
            case 'v':
                y_ -= 1;
                cout << "Moving down" << endl;
                break;
            }

            board.setObject(x_, y_, 'A');
        }


        
};

class Zombie{
    private:
        int x_,y_, life_, attack_, range_ ;
        char id_;
    public:
        Zombie(int life = 100, int attack = 20, int range = 3){
            life_ = life;
            attack_ = attack;
            range_ = range;
        }
        void spawn(Board &board){
            while(1){
                x_ = rand() % board.getDimX() + 1;
                y_ = rand() % board.getDimY() + 1;
                if (board.getObject(x_, y_) == ' '){
                    break;
                }
            }
            board.setObject(x_, y_, id_);
        }
        char getId(){
            return id_;
        }
        void setId(char id){
            id_ = id;
        }

        int getX(){
            return x_;
        }
        int getY(){
            return y_;
        }
        int getLife(){
            return life_;
        }
        int getAttack(){
            return attack_;
        }
        int getRange(){
            return range_;
        }
        void setLife(int life){
            life_ = life;
        }
        void setAttack(int attack){
            attack_ = attack;
        }
        void setRange(int range){
            range_ = range;
        }
        

        void move(Board &board){
            char possibleHeading[] = {'^', '>', '<', 'v'};
            char heading = possibleHeading[rand() % 4];
            cout << heading << " ";

            char objects[] = {' ', ' ', ' ', ' ', ' ', ' ', 'R', 'P', 'H', ' '};
            int noOfObjects = 10; // number of objects in the objects array
            int objNo = rand() % noOfObjects;
            board.setObject(x_, y_, objects[objNo]);

            switch(heading){
                case '^':
                    y_ += 1;
                    cout << "Moving up" << endl;
                    break;
                case '>':
                    x_ += 1;
                    cout << "Moving right" << endl;
                    break;
                case '<':
                    x_ -= 1;
                    cout << "Moving left" << endl;
                    break;
                case 'v':
                    y_ -= 1;
                    cout << "Moving down" << endl;
                    break;

            }
            board.setObject(x_, y_, id_);
        }
};

int main()
{
    srand(time(NULL));
    pf::ClearScreen();
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
    pf::ClearScreen();
    Board board;
    board.setDimX(cols);
    board.setDimY(rows);

    Player alien(board);

	vector<Zombie> zom;
    Zombie s;

    for (int i = 0; i<zombies; i++){
        char id = '0'+i+1;
        s.setId(id);
        zom.push_back(s);
    }

	for (int i = 0; i<zombies; i++){
        zom[i].spawn(board);
    }
    
	board.display();

    while(true){
        cout << "Alien's Turn....." << endl;
        cout << "Alien   : Life " << alien.getLife() << ", Attack " << alien.getAttack() << endl;
        for (int i = 0; i<zombies; i++){
        cout << "Zombie 1: Life " << zom[i].getLife() << ", Attack " << zom[i].getAttack() << ", Range " << zom[i].getAttack() << endl << endl;
        }

        char move;
        cout << "Enter command => ";
        cin >> move;
        cout << endl;
        alien.move(move, board);
        cout << endl;
        pf::Pause();
        pf::ClearScreen();
        board.display();

    }
}