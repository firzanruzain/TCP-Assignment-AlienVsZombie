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
#include <fstream> // for saving/loading files
#include <cmath>
#include<ctype.h>
using namespace std;
// declare objects
char objects[] = {' ', ' ', ' ', ' ', ' ', ' ', '^', 'v', '<', 'R', 'P', 'H', '>'};
int noOfObjects = 13; // number of objects in the objects array

// list classes
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
            string titleM[3] = {"Alien", "=   VS   =", "Zombie"};
            if (title.length() > dimX_*4){
                for (int i = 0; i<3; i++){
                    cout << "  " << setw((dimX_*4) - ((dimX_*4 - titleM[i].length())/2)) << titleM[i] << endl;
                }
            }else{
                cout << "  " << setw((dimX_*4) - ((dimX_*4 - title.length())/2)) << title << endl;
            }
            
            // for each row
            for (int i = 0; i < dimY_; ++i)
            {
                // display upper border of the row
                cout << "  ";
                for (int j = 0; j < dimX_; ++j)
                {
                    cout << "+---";
                }
                cout << "+" << endl;
                // display row number
                cout << (dimY_ - i) << " ";
                // display cell content and border of each column
                for (int j = 0; j < dimX_; j++)
                {
                    cout << "|" << " " << map_[i][j] << " ";
                }
                cout << "|" << endl;
            }
            // display lower border of the last row
            cout << "  ";
            for (int j = 0; j < dimX_; ++j)
            {
                cout << "+---";
            }
            cout << "+" << endl;
            // display column number
            if (dimX_>9){
                cout << " ";
                for (int j = 0; j < dimX_; ++j)
                {
                    int digit = (j + 1) / 10;
                    cout << "  ";
                    if (digit == 0)
                        cout << "  ";
                    else
                        cout << " " << digit;
                }
                cout << endl;
            }
            cout << " ";
            for (int j = 0; j < dimX_; ++j)
            {
                cout << "   " << (j + 1) % 10;
            }
            cout << endl << endl;
        };
        char getRandomObj(){
            int objNo = rand() % noOfObjects;
            return objects[objNo];
        }
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
        void setObjectRaw(int x, int y, char obj){
            map_[x][y] = obj;
        }
        bool isEmpty(int col, int row){
            int x = dimY_ - row;
            int y = col -1;
            return (map_[x][y] == ' ');
        };
        bool isInsideMap(int col, int row){
            int x = dimY_ - row;
            int y = col -1;
            if ((col>= 1 && col<= dimX_) && (row>= 1 && row<= dimY_)){
                return true;
            }else{
                return false;
            }
        };
        void resetTrail(){
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
        int getObjectX(char obj){
            int x;
            for (int i = 0; i < dimY_; ++i)
            {
                for (int j = 0; j < dimX_; ++j)
                {
                    if (map_[i][j] == obj){
                        x = j+1;
                    }
                }
            }
            return x;
        }
        int getObjectY(char obj){
            int y;
            for (int i = 0; i < dimY_; ++i)
            {
                for (int j = 0; j < dimX_; ++j)
                {
                    if (map_[i][j] == obj){
                        y = dimY_ - i;
                    }
                }
            }
            return y;
        }
        void rock(int col, int row){
            int x = dimY_ - row;
            int y = col -1;
            char newObj;
            while(true){
                newObj = getRandomObj();
                if (newObj != 'R'){
                    break;
                }
            }
            string object;
            switch (newObj)
            {
            case 'H':
                object = "a Health";
                break;
            case 'P':
                object = "a Pod";
                break;
            case ' ':
                object = "Nothing";
                break;
            case '>':
                object = "a Right arrow";
                break;
            case '<':
                object = "a Left arrow";
                break;
            case 'v':
                object = "a Down arrow";
                break;
            case '^':
                object = "a Up arrow";
                break;

            default:
                break;
            }
            cout << endl << "There is " << object << " beneath it." << endl << endl;
            map_[x][y] = newObj;
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
        void display(){
            cout << "Alien   : Life " << life_ << ", Attack " << attack_ << endl;
        }
        void health(){
            life_ += 20;
        }
        void arrow(){
            attack_ += 20;
        }
        void resetAttack(){
            attack_ = 0;
        }
        void attacked(int damage){
            life_ -= damage;
            cout << "\nAlien gets damaged by " << damage << ".\n" <<endl;
            pf::Pause();
            if (life_ <= 0){
                life_ = 0;
            }
        }
        bool alive(){
            return (life_ != 0);
        }
        void reset(){
            life_ = 100;
            attack_ = 0;
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
        void setX(int x){
            x_ = x;
        }
        int getY(){
            return y_;
        }
        void setY(int y){
            y_ = y;
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
            range_ = (rand()%5)+2;
        }
        void move(Board &board){
            char possibleHeading[] = {'^', '>', '<', 'v'};
            bool invalid = true;
            char heading;
            string moves = "";
            board.setObject(x_, y_, board.getRandomObj());
            for (int i = 0; i<1000; i++){
                int x = x_;
                int y = y_;
                heading = possibleHeading[rand() % 4];
                switch(heading){
                    case '^':
                        y += 1;
                        moves = "moves up.";
                        break;
                    case '>':
                        x += 1;
                        moves = "moves right.";
                        break;
                    case '<':
                        x -= 1;
                        moves = "moves left.";
                        break;
                    case 'v':
                        y -= 1;
                        moves = "moves down.";
                        break;
                }
                if (board.isInsideMap(x, y) && !isdigit(board.getObject(x, y)) && board.getObject(x, y) != 'A'){
                    x_ = x;
                    y_ = y;
                    invalid = false;
                    break;
                }
            }
            if(invalid == true){
                moves = "cannot move.";
            }
            cout << "\nZombie " << id_ << " " << moves << endl;
            board.setObject(x_, y_, id_);
        }
        void display(){
            cout << "Zombie " << id_ << ": Life " << life_ << ", Attack " << attack_ << ", Range " << range_ << endl;
        }
        void attacked(int damage){
            life_ -= damage;
            cout << "\nZombie " << id_ << " gets damaged by " << damage << ".\n" <<endl;
            if (life_ < 0){
                life_ = 0;
            }
            if (!alive()){
                cout << "Zombie " << id_ << " is dead\n.";
            }
        }
        bool alive(){
            if (life_ == 0){
                return false;
            }else{
                return true;
            }
        }
};

// declaring important objects and variables
vector<Zombie> zom; // create zombies
Zombie s;
Board board; // create board
Player alien; // create player
int rows,cols,zombies;
int turn = 0;
bool playing = true;

// list of standalone functions
void playGame(); // declare playgame
void init(){
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
    board.init(cols,rows);
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
}
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
void refreshScreen(){
    pf::Pause();
    mainDisp(board, alien);
}
void saveGame(){
    ofstream myfile;
    ifstream testFile;
    string filename;

    while(true){
        filename.clear();
        cout << endl << "Enter file name => ";
        cin >> filename;
        filename += ".txt";

        testFile.open(filename);
        if (testFile){
            char option;
            cout << "File already exists. You want to overwrite? (y/n) => ";
            cin >> option;
            if (option == 'y'){
                break;
            }else{
                mainDisp(board, alien);
            }
        }else{
            break;
        }
        testFile.close();
    }
    


    myfile.open(filename);
    cout << endl << "Saving file in " << filename << endl << endl;

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
    cout << "File is saved." << endl << endl;
    pf::Pause();
    myfile.close();
}
void loadGame(){
    // starts here for load file
    string filename;
    ifstream readFile;
    while(true){
        cout << "\nEnter file name to load => ";
        cin >> filename;
        filename = filename + ".txt";
        cout << "File name = " << filename << endl;
        readFile.open(filename);
        if(readFile){
            cout << "File found...." << endl;
            cout << "Loading game..." << endl;
            pf::Pause();
            break;
        }else{
            cout << "File not found." << endl;
            pf::Pause();
        }
    }
    string myText;
    int counter = 1;
    int dimX;
    int dimY;
    // get dimx and dimy first
    while(getline(readFile, myText)){
        if(counter == 1){
            dimX = stoi(myText);
        }
        else if(counter == 2){
            dimY = stoi(myText);
            break;
        }
        counter++;
    }
    board.init(dimX, dimY); // create game board with new dimx dimy
    cols = dimX;
    rows = dimY;
    counter = 0; // reset counter
    // get game objects & characters on map
    while(getline(readFile, myText)){
        for (int i = 0; i<myText.length(); i++){
            if (myText[i] != '|'){
                char obj = myText[i];
                board.setObjectRaw(counter, i/2, obj);
            }
        }
        counter++;
        if (counter == dimY){
            break;
        }
    }

    string attributes = "";
    vector<vector<int>> att;
    int lines = 1;
    int size = 0;
    att.resize(lines);
    att[0].resize(size);

    while(getline(readFile,myText)){
        for (int i = 0; i<myText.length(); i++){
            if (myText[i] == ','){
                int num = stoi(attributes);
                att[lines-1].push_back(num);
                size++;
                att[lines-1].resize(size);

                attributes.clear();
            }else if (i == myText.length()-1){
                attributes.push_back(myText[i]);
                int num = stoi(attributes);
                att[lines-1].push_back(num);
                size++;
                att[lines-1].resize(size);

                attributes.clear();
            }else if (myText[i] != ','){
                attributes.push_back(myText[i]);
            }
        }
        lines++;
        size = 0;
        att.resize(lines);
    }
    lines--;
    att.resize(lines);
    zombies = lines-1;

    alien.setLife(att[0][0]);
    alien.setAttack(att[0][1]);

    zom.clear();
    for (int i = 1; i<zombies+1; i++){
        char idw;
        size = att[i].size();
        for(int j = 0; j<size; j++){
            switch (j)
            {
            case 0:
                idw = '0'+att[i][j];
                s.setId(idw);
                break;
            
            case 1:
                s.setLife(att[i][j]);
                break;
            
            case 2:
                s.setAttack(att[i][j]);
                break;
            
            case 3:
                s.setRange(att[i][j]);
                break;
            default:
                break;
            }
        }
        zom.push_back(s);
    }

    // setting characters x and y back
    alien.setX(board.getObjectX('A'));
    alien.setY(board.getObjectY('A'));

    for (int i = 0; i<zombies; i++){
        zom[i].setX(board.getObjectX(zom[i].getId()));
        zom[i].setY(board.getObjectY(zom[i].getId()));
    }

    readFile.close();

    // end here for load file
}
void quit(){
    cout << "\nQuiting the game now... goodbye.\n";
    pf::Pause();
    pf::ClearScreen();
    playing = false;
}
void restart(){
    string option;
    while(true){
        cout << "\nDo you want to restart the game? (y/n/cancel) => ";
        cin >> option;
        if (option == "y"){
            alien.reset();
            zom.clear();
            init();
            playGame();
            break;
        }else if (option == "n"){
            quit();
            break;
        }else if (option == "cancel"){
            break;
        }
    }
}
double getDistance(double x1, double x2){
    return abs(x1 - x2);
}
void pod(int x, int y){
    double closestDistance = 100;
    char attackZombie;
    for (int i=0; i<zombies; i++){
        double distance;
        double dx = getDistance(x,zom[i].getX());
        double dy = getDistance(y,zom[i].getY());

        if (dx == 0){
            distance = dy;
        }else if (dy ==0){
            distance = dx;
        }else{
            distance = sqrt(pow(dx,2) + pow(dy,2));
        }
        if (distance < closestDistance){
            closestDistance = distance;
            attackZombie = i;
        }
    }
    zom[attackZombie].attacked(10);
}
void alienAttack(string attacker, string victim){
    zom[stoi(victim)-1].attacked(alien.getAttack());
}
void zombieAttack(int id){
    cout << "\nZombie " << id+1 << " tries to attack alien.\n" <<endl;
    refreshScreen();
    int zomid = id;
    int dx = getDistance(alien.getX(), zom[zomid].getX());
    int dy = getDistance(alien.getY(), zom[zomid].getY());
    int distance = 100;
    if (dx == 0){
        distance = dy;
    }else if(dy == 0){
        distance = dx;
    }
    if (distance <= zom[zomid].getRange()){
        alien.attacked(zom[zomid].getAttack());
    }else{
        cout << "\nAlien is out of zombie's range." << endl;
        pf::Pause();
    }
}
void arrow(){
    int col, row;
    char arrow;
    string newDirection;
    char newArrow;
    arrow:
    bool arrowExist = false;
    while (!arrowExist){
        cout << "\nEnter col and row of arrow to change direction => ";
        cin >> col >> row;
        arrow = board.getObject(col, row);
        if (arrow == '>' || arrow == 'v' || arrow == '<' || arrow == '^'){
            cout << "Arrow found on (" << col << "," << row << ")" << endl << endl;
            arrowExist = true;
        }
        else{
            cout << "Arrow does not found on (" << col << "," << row << ")" << endl << endl;
        }
    }
    while(true){
        cout << "Enter new direction for the arrow (up, down, left right) => ";
        cin >> newDirection;
        if (newDirection == "up"){
            newArrow = '^';
            break;
        }else if (newDirection == "down"){
            newArrow = 'v';
            break;
        }else if (newDirection == "left"){
            newArrow = '<';
            break;
        }else if (newDirection == "right"){
            newArrow = '>';
            break;
        }else{
            cout << "Enter valid direction only." << endl << endl;
        }
    }
    cout << "Changing arrow " << arrow << " on (" << col << "," << row << ") to " << newArrow << endl << endl;
    board.setObject(col,row,newArrow);
    refreshScreen();
    while(true){
        string option;
        cout << "\nDo you want to change another arrow? (y/n) => ";
        cin >> option;
        if (option == "y"){
            goto arrow;
            break;
        }
        else if (option == "n"){
            break;
        }
    }
}
void zombieTurn(){
    for (int i=0; i<zombies; i++){
        mainDisp(board, alien);
        if (zom[i].alive()){ 
            zom[i].move(board);
            refreshScreen();
            zombieAttack(i);
        }
        turn++;
    }
}
bool allZombiesDead(){
    int deadZombies = 0;
    for (int i = 0; i<zombies; i++){
        if (!zom[i].alive()){
            deadZombies++;
        }
    }
    return(deadZombies == zombies);
}
void command(Player &alien, Board &board){
    string command;
    cout << "\nEnter Command => ";
    cin >> command;
    pf::ClearScreen();
    mainDisp(board, alien);
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
        cout << "9. restart - Restart the game.\n";
        cout << "10. help    - Display available commands.\n\n";
        pf::Pause();
        mainDisp(board, alien);
    }else if (command == "save"){
        saveGame();
    }else if (command == "load"){
        loadGame();
    }else if (command == "quit"){
        string option;
        cout << "\nWant to save the game? (y/n/cancel) => ";
        while (true){
            cin >> option;
            if (option == "cancel"){
                break;
            }else if(option == "y"){
                saveGame();
                quit();
                break;
            }else if(option == "n"){
                quit();
                break;
            }
        }
    }else if (command == "restart"){
        restart();
    }else if (command == "arrow"){
        arrow();
    }else if (command == "up" || command == "down" || command == "left" || command == "right" ){
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
                }
                else if (obj == '.'){
                }
                else if (obj == 'P'){
                    cout << "\nAlien finds a Pod.\n";
                    pod(x_, y_);
                }
                else if (obj == 'H'){
                    cout << "\nAlien finds a health pack.\n\n";
                    cout << "Alien's life is increased by 20.\n\n";
                    alien.health();
                }
                else if (obj == 'R'){
                    cout << "\nAlien hits a rock.\n\n";
                    pf::Pause();
                    board.rock(x_,y_);
                    if (direction == "up"){
                        y_--;
                    }else if(direction == "down"){
                        y_++;
                    }else if(direction == "right"){
                        x_--;
                    }else if(direction == "left"){
                        x_++;
                    }
                    move = 0;
                }
                else if (isdigit(obj)){
                    cout << "\nAlien attack zombie " << obj << ".\n\n";
                    pf::Pause();
                    string zombietAttacked(1, obj);
                    alienAttack("A", zombietAttacked);
                    if (direction == "up"){
                        y_--;
                    }else if(direction == "down"){
                        y_++;
                    }else if(direction == "right"){
                        x_--;
                    }else if(direction == "left"){
                        x_++;
                    }
                    move = 0;
                }
                else if (obj == '>' || obj == '<' || obj == '^' || obj == 'v'){
                    cout << "\nAlien finds an arrow.\n\n";
                    cout << "Alien's attack increased by 20.\n\n";
                    alien.arrow();
                    switch (obj)
                    {
                    case '>':
                        direction = "right";
                        move = board.getDimX() - x_;
                        break;
                    case '<':
                        direction = "left";
                        move = x_ - 1;
                        break;
                    case '^':
                        direction = "up";
                        move = board.getDimY() - y_;
                        break;
                    case 'v':
                        direction = "down";
                        move = y_ - 1;
                        break;
                    
                    default:
                        break;
                    }
                    i=-1;
                }
                board.setObject(x_,y_, 'A');
                alien.setX(x_);
                alien.setY(y_);
                refreshScreen();
            }
            turn++;
            board.resetTrail();
            if ((alien.getX() == 1 && direction == "left") || (alien.getY() == 1 && direction == "down") || (alien.getX() == cols && direction == "right") || (alien.getY() == rows && direction == "up")){
                cout << "\nAlien hits the boudaries." << endl;
            }
            cout << "\nAlien's turn ends. The trail reset.\n" << endl;
            alien.resetAttack();
            pf::Pause();
    }else{
        cout << "\nPlease enter valid commands only\n";
        cout << "Enter help for a list of available commands\n\n";
        pf::Pause();
    }  
}
void playGame(){
    while(playing){
        mainDisp(board, alien);
        if (allZombiesDead()){
            cout << "Congratulations! You have killed all zombies." << endl;
            restart();
        }
        if (!alien.alive()){
            cout << "You are dead.";
            restart();
        }
        if(turn == 0){
            command(alien, board);
        }else if (turn>0){
            zombieTurn();
        }
    }
}

int main()
{
    init(); // intialize all game settings
    playGame(); // starts the game
}