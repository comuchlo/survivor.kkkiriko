#include "enemy.hpp"

#include <cmath>
#include <raylib.h>
#include <cstdlib>
#include <ctime>

Enemy::Enemy(TypeEnemy type){
    hitted=false;
    frameHit=0;
    speed=250;
    vita=75;

    //random point outside the screen
    std::uniform_real_distribution<double> angle(0.0, PI*2);
    double phi= angle(sys->rng);
    auto [width,height] = sys->getScreenSizeWH();
    x= ((sqrt(2) * cos(phi)) * width*0.5) + width*0.5;
    y= ((sqrt(2) * sin(phi)) * height*-0.5) + height*0.5;

    // vettoreVelocitaNemico = normalizeVector(
    //   (Vector2) {
    //     player1.x + player1.width / 2 - enemy.x - enemy.width / 2,
    //     player1.y + player1.height / 2 - enemy.y - enemy.height / 2
    //   }
    // );
    // xVel=;
    // xVel=;
    typeEnemy=type;
    switch (type) {
        case TypeEnemy::CIAMBELLA:
            width=66;
            height=66;
            texture= LoadTexture("./textures/temp donut.png");
            break;
        case TypeEnemy::CIAMBELLACHAD:
            width=128;
            height=172;
            texture= LoadTexture("./textures/VeroChad.png");
            break;
        case TypeEnemy::CIAMBELLAKING:
            width=128;
            height=128;
            texture= LoadTexture("./textures/ciambella king.png");
            break;
        default:
            width=66;
            height=66;
            texture= LoadTexture("./textures/temp donut.png");
            break;
    }
}
