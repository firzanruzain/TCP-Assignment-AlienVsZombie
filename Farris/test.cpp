#include <iostream>
#include <string>
#include <string>
using namespace std;

 class Alien
  {
  private:
    int life_, attack_;          // to indicate private data

  public:
    Alien(int life = 100, int attack = 0){
        setLife(life);
        setAttack(attack);
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

    void display() const{
        cout<<"life =" << life_ << endl;
        cout<<"Attack =" << attack_ << endl;
    };
  };



  int main()
  {
    Alien alien(200, 20);
    alien.display();    
    return 0;
  }