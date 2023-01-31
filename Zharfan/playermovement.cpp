#include <iostream>
#include <string>

class Player
{
private:
    int l, m;

public:
    Player(int l = 0, int m = 0) : l(l), m(m) {}
    int getL() const { return l; }
    int getM() const { return m; }
    void moveUp() { m++; }
    void moveDown() { m--; }
    void moveLeft() { l--; }
    void moveRight() { l++; }
};

int main()
{
    Player player;
    while (true)
    {
        std::cout << "Player position: " << player.getL() << "," << player.getM() << std::endl;
        std::cout << "Enter a move (W for up, S for down, A for left, D for right): ";
        std::string move;
        std::cin >> move;
        if (move == "W")
        {
            player.moveUp();
        }
        else if (move == "S")
        {
            player.moveDown();
        }
        else if (move == "A")
        {
            player.moveLeft();
        }
        else if (move == "D")
        {
            player.moveRight();
        }
        else
        {
            std::cout << "Invalid move" << std::endl;
        }
    }
    return 0;
}
