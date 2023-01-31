#include <iostream>
#include <string>
#include <vector>

class Character {
public:
  Character() {
    x = 0;
    y = 0;
    dx = 0;
    dy = 0;
    health = 100;
    strength = 10;
    defense = 5;
    level = 1;
    experience = 0;
    facing_right = true;
    animation_state = 0;
  }

  int x, y;
  int dx, dy;
  int health;
  int strength;
  int defense;
  int level;
  int experience;
  bool facing_right;
  int animation_state;
  std::vector<std::string> inventory;

  void addItem(std::string item) {
    inventory.push_back(item);
  }

  void removeItem(std::string item) {
    auto it = std::find(inventory.begin(), inventory.end(), item);
    if (it != inventory.end()) {
      inventory.erase(it);
    }
  }
};
