#include <iostream>
#include <string>
using namespace std;

class Alien
{
private:
    int x_, y_;
    char heading_;

public:
    Alien(int x = 0, int y = 0) : x_(x), y_(y) {}
    int getX() const { return x_; }
    int getY() const { return y_; }
    void moveUp() { y_++; }
    void moveDown() { y_--; }
    void moveLeft() { x_--; }
    void moveRight() { x_++; }
};

int main()
{
    Alien alien;
    while (true)
    {
        cout << "Alien position: " << alien.getX() << "," <<alien.getY() << std::endl;
        cout << "Enter a move (up for up, down for down, left for left, right for right): ";
        string move;
        cin >> move;
        if (move == "up")
        {
            alien.moveUp();
        }
        else if (move == "down")
        {
            alien.moveDown();
        }
        else if (move == "left")
        {
            alien.moveLeft();
        }
        else if (move == "right")
        {
            alien.moveRight();
        }
        else
        {
            cout << "Invalid move" << endl;
        }
    }
    return 0;
}
