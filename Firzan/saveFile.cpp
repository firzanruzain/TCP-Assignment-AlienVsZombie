#include "../pf/helper.h"
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

class Player{
    private:
        int x_, y_;
        int life_, attack_;
    public:
        Player(int life = 100, int attack = 0){
            life_ = life;
            attack_ = attack;
        }
        int getX(){
            return x_;
        }
        int getY(){
            return y_;
        }
        void setX(int x){
            x_ = x;
        }
        void setY(int y){
            y_ = y;
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
        void spawn(Board &board){
            x_ = board.getDimX()/2 + 1;
            y_ = board.getDimY()/2 + 1; 
            board.setObject(x_, y_, 'A');
        }
        void move(string command, Board &board){

            char objects[] = {' ', ' ', ' ', ' ', ' ', ' ', '^', 'v', '<', 'R', 'P', 'H', '>'};
            int noOfObjects = 13; // number of objects in the objects array
            int objNo = rand() % noOfObjects;
            board.setObject(x_, y_, objects[objNo]);
            int move;
            if (command == "up"){
                move = board.getDimY() - y_;
            }else if(command == "down"){
                move = y_ - 1;
            }else if(command == "right"){
                move = board.getDimX() - x_;
            }else if(command == "left"){
                move = x_ - 1;
            }

            for(int i = 0; i<move; i++){
                    board.setObject(x_,y_, '.');
                    if (command == "up"){
                        y_++;
                    }else if(command == "down"){
                        y_--;
                    }else if(command == "right"){
                        x_++;
                    }else if(command == "left"){
                        x_--;
                    }
                    char obj = board.getObject(x_,y_);
                    switch (obj)
                    {
                    case ' ':
                        cout << "\nAlien finds a empty space.\n\n";
                        board.setObject(x_,y_, 'A');
                        pf::Pause();
                        pf::ClearScreen();
                        board.display();
                        break;
                    
                    default:
                        cout << "\nAlien finds a.\n\n";
                        board.setObject(x_,y_, 'A');
                        pf::Pause();
                        pf::ClearScreen();
                        board.display();
                        break;
                    }
                    
                }


            board.setObject(x_, y_, 'A');
        }

        void display(){
            cout << "Alien   : Life " << life_ << ", Attack " << attack_ << endl;
        }


        
};

class Zombie{
    private:
        int x_,y_, life_, attack_, range_ ;
        char id_;
    public:
        Zombie(){
            life_ = (rand()%5+1)*50;
            attack_ = (rand()%6+1)*5;
            range_ = (rand()%10+1);
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
        void randomizeAttributes(){
            life_ = ((rand()%5)+1)*50;
            attack_ = ((rand()%6)+1)*5;
            range_ = (rand()%5)+1;
        }
        

        void move(Board &board){
            char possibleHeading[] = {'^', '>', '<', 'v'};
            bool invalid = true;
            char heading;
            while(invalid){
                heading = possibleHeading[rand() % 4];
                if (heading == '^' && y_ < board.getDimY()){
                    invalid = false;
                }
                else if (heading == 'v' && y_ > 1){
                    invalid = false;
                }
                else if (heading == '>' && x_ < board.getDimX()){
                    invalid = false;
                }
                else if (heading == '<' && x_ > 1){
                    invalid = false;
                }
            }
            

            cout << "\nZombie " << id_ << " ";

            char objects[] = {' ', ' ', ' ', ' ', ' ', ' ', '^', 'v', '<', 'R', 'P', 'H', '>'};
            int noOfObjects = 13; // number of objects in the objects array
            int objNo = rand() % noOfObjects;
            board.setObject(x_, y_, objects[objNo]);

            switch(heading){
                case '^':
                    y_ += 1;
                    cout << "moves up." << endl;
                    break;
                case '>':
                    x_ += 1;
                    cout << "moves right." << endl;
                    break;
                case '<':
                    x_ -= 1;
                    cout << "moves left." << endl;
                    break;
                case 'v':
                    y_ -= 1;
                    cout << "moves down." << endl;
                    break;

            }
            pf::Pause();
            board.setObject(x_, y_, id_);
        }
        void display(){
            cout << "Zombie " << id_ << ": Life " << life_ << ", Attack " << attack_ << ", Range " << range_ << endl;
        }
};

vector<Zombie> zom; // create zombies
Zombie s;
int zombies = 2;

int main() {
    srand(time(NULL));
    Board board;
    Player alien;
    board.init(11, 3);
    alien.spawn(board);
    for (int i = 0; i<zombies; i++){
        char id = '0'+i+1;
        s.setId(id);
        s.randomizeAttributes();
        zom.push_back(s);
    }

    // spawn zombies
	for (int i = 0; i<zombies; i++){
        zom[i].spawn(board);
    }
    board.display();

    ofstream myfile;
    myfile.open("test.txt");

    myfile << board.getDimX() << endl; // print dimX
    myfile << board.getDimY() << endl;

    for (int i = 0; i<board.getDimY(); i++){
        for (int j = 0; j<board.getDimX(); j++){
            myfile << board.getObjectRaw(i,j) << "|";
        }
        myfile << endl;
    }

    myfile << alien.getLife() << "," << alien.getAttack() << endl;

    for (int i = 0; i<zombies; i++){
        myfile << zom[i].getId() << "," << zom[i].getLife() << "," << zom[i].getAttack() << "," << zom[i].getRange();

        if (i != zombies-1){
            myfile << endl;
        }
    }

    myfile.close();
    return 0;
}