#include <raylib.h>
#include "../core/system.hpp"

enum class TypeEnemy {
  CIAMBELLA = 1,
  CIAMBELLACHAD,
  CIAMBELLAKING
};

class Enemy{
    short int speed = 250;
    float x, y;
    short int width, height;
    int vita;
    double xVel, yVel;
    bool hitted;
    unsigned short frameHit;
    Rectangle oldRec;
    TypeEnemy typeEnemy;
    Texture2D texture;

    System* sys= System::getInstance();

    Enemy(TypeEnemy type= TypeEnemy::CIAMBELLA);
    ~Enemy();

    // ciambellaSize = 22, ciambellaChadWidth = 128, ciambellaChadHeight = 172, ciambellaKingSize = 128
};
