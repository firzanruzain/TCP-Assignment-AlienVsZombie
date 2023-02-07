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
            cout << "  " << setw((dimX_*2) - ((dimX_*2 - title.length())/2)) << title << endl;
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
        void resetTrail(){
            char objects[] = {' ', ' ', ' ', ' ', ' ', ' ', '^', 'v', '<', 'R', 'P', 'H', '>'};
            int noOfObjects = 13; // number of objects in the objects array
            for (int i = 0; i < dimY_; ++i)
            {
                for (int j = 0; j < dimX_; ++j)
                {
                    if (map_[i][j] == '.'){
                        int objNo = rand() % noOfObjects;
                        map_[i][j] = objects[objNo];
                    }
                }
            }
        }
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
Board board; // create board
Player alien; // create player
int rows,cols,zombies;
int turn = 0;

void mainDisp(Board &board, Player &alien){
    pf::ClearScreen();
	board.display(); //board display

    if (turn >= zombies+1){
        turn = 0;
    }
    string arrow = "->  ";
    string empty = "    ";
    if (turn == 0){
        cout << arrow;
    }else{
        cout << empty;
    }
    alien.display();
    for (int i = 0; i<zombies; i++){
        if (turn == i+1){
            cout << arrow;
        }else{
            cout << empty;
        }
        zom[i].display();
        }
}

void command(Player &alien, Board &board){
    string command;
    cout << "\nEnter Command => ";
    cin >> command;
    
    if (command == "help"){
        cout << "\nCommands\n";
        cout << "1. up      - Move up.\n";
        cout << "2. down    - Move down.\n";
        cout << "3. left    - Move left.\n";
        cout << "4. right   - Move right.\n";
        cout << "5. arrow   - Change arrows direction.\n";
        cout << "6. save    - Save the game.\n";
        cout << "7. load    - Load up a game.\n";
        cout << "8. quit    - Quit the game.\n";
        cout << "9. help    - Display available commands.\n\n";
        pf::Pause();
        mainDisp(board, alien);
    }else if (command == "up" || command == "down" || command == "left" || command == "right" ){
        //alien.move(command, board);
        int y_ = alien.getY();
        int x_ = alien.getX();
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
        string direction = command;
        for(int i = 0; i<move; i++){
                board.setObject(x_,y_, '.');
                if (direction == "up"){
                    y_++;
                    if (alien.getY() == board.getDimY()){
                        break;
                    }
                }else if(direction == "down"){
                    y_--;
                }else if(direction == "right"){
                    x_++;
                }else if(direction == "left"){
                    x_--;
                }
                char obj = board.getObject(x_,y_);

                if (obj == ' '){
                    cout << "\nAlien finds a empty space.\n\n";
                    board.setObject(x_,y_, 'A');
                    alien.setX(x_);
                    alien.setY(y_);
                    pf::Pause();
                    pf::ClearScreen();
                    mainDisp(board, alien);
                }
                else if (obj == 'P'){
                    cout << "\nAlien finds a Pod.\n\n";
                    board.setObject(x_,y_, 'A');
                    alien.setX(x_);
                    alien.setY(y_);
                    pf::Pause();
                    pf::ClearScreen();
                    mainDisp(board, alien);
                }
                else if (obj == 'H'){
                    cout << "\nAlien finds health.\n\n";
                    board.setObject(x_,y_, 'A');
                    alien.setX(x_);
                    alien.setY(y_);
                    pf::Pause();
                    pf::ClearScreen();
                    mainDisp(board, alien);
                }
                else if (obj == 'R'){
                    cout << "\nAlien finds a rock.\n\n";
                    if (direction == "up"){
                    y_--;
                    if (alien.getY() == board.getDimY()){
                        break;
                    }
                    }else if(direction == "down"){
                        y_++;
                    }else if(direction == "right"){
                        x_--;
                    }else if(direction == "left"){
                        x_++;
                    }
                    board.setObject(x_,y_, 'A');
                    alien.setX(x_);
                    alien.setY(y_);
                    pf::Pause();
                    pf::ClearScreen();
                    mainDisp(board, alien);
                    break;
                }
            }
            turn++;
            board.resetTrail();
            cout << "\nAlien's turn ends. The trail reset.\n" << endl;
            pf::Pause();
    }else{
        cout << "\nPlease enter valid commands only\n";
        cout << "Enter help for a list of available commands\n\n";
        pf::Pause();
        pf::ClearScreen();
    }

    
}

void zombieTurn(){
    for (int i=0; i<zombies; i++){
        pf::ClearScreen();
        mainDisp(board, alien);
        zom[i].move(board);
        turn++;
    }

}

int main()
{
    srand(time(NULL));
    pf::ClearScreen();
    cout << "Default Game Settings" << endl;
    cout << "-----------------------" << endl;
    cout << "Board Rows    : 5" << endl;
    cout << "Board Columns : 9" << endl;
    cout << "Zombie Count  : 1" << endl << endl;
    rows = 5;
    cols = 9;
    zombies = 1;

    while(true){
        cout << "Do you wish to change game settings? (y/n)? => ";
        char option;
        cin >> option;

        if (option == 'y'){
            
            change:
            pf::ClearScreen();

            while(1){
                cout << "Board Rows    : ";
                cin >> rows;
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
                if (cols % 2 == 0){
                    cout << "Use odd number only!!!\n";
                }
                else{
                    break;
                }
            }
            pf::ClearScreen();
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

    
    board.setDimX(cols); // set board cols and rows 
    board.setDimY(rows);
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

    while(true){
        mainDisp(board, alien);
        if(turn == 0){
            command(alien, board);
        }
        else if (turn>0){
            zombieTurn();
        }
    }
}