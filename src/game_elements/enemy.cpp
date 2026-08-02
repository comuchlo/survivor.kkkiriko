#include <cmath>
#include <raylib.h>
#include <cstdlib>
#include <ctime>
#include "enemy.hpp"

Enemy::Enemy(TypeEnemy type){
    this->hitted=false;
    this->frameHit=0;
    this->speed=250;
    this->vita=75;

    //random point outside the screen
    std::uniform_real_distribution<double> angle(0.0, PI*2);
    double phi= angle(sys->rng);
    auto [width,height] = sys->getScreenSizeWH();
    this->x= ((sqrt(2) * cos(phi)) * width*0.5) + width*0.5;
    this->y= ((sqrt(2) * sin(phi)) * height*-0.5) + height*0.5;

    // vettoreVelocitaNemico = normalizeVector(
    //   (Vector2) {
    //     player1.x + player1.width / 2 - enemy.x - enemy.width / 2,
    //     player1.y + player1.height / 2 - enemy.y - enemy.height / 2
    //   }
    // );
    // this->xVel=;
    // this->xVel=;
    this->typeEnemy=type;
    switch (type) {
        case TypeEnemy::CIAMBELLA:
            this->width=66;
            this->height=66;
            this->texture= LoadTexture("./textures/temp donut.png");
            break;
        case TypeEnemy::CIAMBELLACHAD:
            this->width=128;
            this->height=172;
            this->texture= LoadTexture("./textures/VeroChad.png");
            break;
        case TypeEnemy::CIAMBELLAKING:
            this->width=128;
            this->height=128;
            this->texture= LoadTexture("./textures/ciambella king.png");
            break;
        default:
            this->width=66;
            this->height=66;
            this->texture= LoadTexture("./textures/temp donut.png");
            break;
    }
}
