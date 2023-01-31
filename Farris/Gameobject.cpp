#include <iostream>

class Health {
  public:
    int value;
    Health(int val) : value(val) {}
};

class Pod {
  public:
    int x, y;
    float velocityX, velocityY;
    Pod(int xPos, int yPos, float vx, float vy) : x(xPos), y(yPos), velocityX(vx), velocityY(vy) {}
};

class Trail {
  public:
    int x, y;
    Trail(int xPos, int yPos) : x(xPos), y(yPos) {}
};

class Space {
  public:
    int width, height;
    float gravity;
    Space(int w, int h, float g) : width(w), height(h), gravity(g) {}
};

int main() {
  Health playerHealth(100);
  Pod playerPod(0, 0, 10.0f, 5.0f);
  Trail playerTrail(0, 0);
  Space gameSpace(500, 500, 9.8f);
  
  std::cout << "Player health: " << playerHealth.value << std::endl;
  std::cout << "Player pod position: (" << playerPod.x << ", " << playerPod.y << ")" << std::endl;
  std::cout << "Player pod velocity: (" << playerPod.velocityX << ", " << playerPod.velocityY << ")" << std::endl;
  std::cout << "Player trail position: (" << playerTrail.x << ", " << playerTrail.y << ")" << std::endl;
  std::cout << "Game space size: " << gameSpace.width << "x" << gameSpace.height << std::endl;
  std::cout << "Game space gravity: " << gameSpace.gravity << std::endl;
  
  return 0;
}
