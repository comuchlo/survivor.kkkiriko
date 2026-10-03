#include "enemy.hpp"

#include <algorithm>
#include <cmath>
#include <raylib.h>
#include <cstdlib>
#include <ctime>

Enemy::Enemy(
    EnemySkin* skin, // skin of the enemy
    float enemyDimensionMul, // multiplier of the dimension of the enemy
    float moveVel, // multiplier of the displacement of the enemy
    float attackCooldown, // cooldown between two attacks
    int32_t health, // health of the enemy
    int32_t damage // damage of the enemy
) {
    this->skinInfo = skin->skinInfo;
    this->texture = &skin->texture;;

    this->moveVel = moveVel;

    this->attackCooldown = attackCooldown;
    this->attackCooldownRemainingTime = 0.0f;

    this->health = health;
    this->damage = damage;

    this->isMoving = false;
    this->isAttacking = false;
    this->hurted = false;
    this->currVerse = false;

    // x,y random point outside the screen
    System* sys = System::getInstance();
    std::uniform_real_distribution<double> angle(0.0, PI*2);
    double phi= angle(sys->rng);
    auto [width,height] = sys->getScreenSizeWH();
    this->hurtBox.x = ((sqrt(2) * cos(phi)) * width*0.5) + width*0.5;
    this->hurtBox.y = ((sqrt(2) * sin(phi)) * height*-0.5) + height*0.5;

    switch (this->skinInfo.type) {
        case TypeEnemy::DONUT:
            this->hurtBox.width = DEF_WIDTH_DONUT*enemyDimensionMul;
            this->hurtBox.height = DEF_HEIGHT_DONUT*enemyDimensionMul;
            this->move = DEF_MOVE_DONUT*moveVel;
            break;
        case TypeEnemy::KING_DONUT:
            this->hurtBox.width = DEF_WIDTH_KING_DONUT*enemyDimensionMul;
            this->hurtBox.height = DEF_HEIGHT_KING_DONUT*enemyDimensionMul;
            this->move = DEF_MOVE_KING_DONUT*moveVel;
            break;
        case TypeEnemy::CHAD_DONUT:
            this->hurtBox.width = DEF_WIDTH_CHAD_DONUT*enemyDimensionMul;
            this->hurtBox.height = DEF_HEIGHT_CHAD_DONUT*enemyDimensionMul;
            this->move = DEF_MOVE_CHAD_DONUT*moveVel;
            break;
    }
}

Enemy::Enemy(EnemySkin* skin)
    : Enemy(
        skin, // skin of the enemy
        1.0f, // multiplier of the dimension of the enemy
        1.0f, // multiplier of the displacement of the enemy
        DEF_ATTACK_COOLDOWN, // cooldown between two attacks
        getDefHealth(skin->skinInfo.type), // health of the enemy
        getDefDamage(skin->skinInfo.type) // damage of the enemy
    )
{}

void Enemy::copy(const Enemy& enemyCopy) {
    this->skinInfo = enemyCopy.skinInfo;
    this->texture = enemyCopy.texture;
    this->hurtBox = enemyCopy.hurtBox;
    this->moveVel = enemyCopy.moveVel;
    this->move = enemyCopy.move;

    this->health = enemyCopy.health;
    this->damage = enemyCopy.damage;

    this->attackCooldown = enemyCopy.attackCooldown;
    this->attackCooldownRemainingTime = enemyCopy.attackCooldownRemainingTime;

    this->isMoving = enemyCopy.isMoving;
    this->isAttacking = enemyCopy.isAttacking;
    this->hurted = enemyCopy.hurted;
    this->currVerse = enemyCopy.currVerse;
}

void Enemy::resetModifiers() {
    this->moveVel = 1.0f;

    this->attackCooldown = DEF_ATTACK_COOLDOWN;
    this->attackCooldownRemainingTime = 0.0f;

    this->isMoving = false;
    this->isAttacking = false;
    this->hurted = false;
    this->currVerse = false;

    switch (this->skinInfo.type) {
        case TypeEnemy::DONUT:
            this->hurtBox.width = DEF_WIDTH_DONUT;
            this->hurtBox.height = DEF_HEIGHT_DONUT;
            this->move = DEF_MOVE_DONUT*moveVel;
            this->health = DEF_HEALTH_DONUT;
            this->damage = DEF_DAMAGE_DONUT;
            break;
        case TypeEnemy::KING_DONUT:
            this->hurtBox.width = DEF_WIDTH_KING_DONUT;
            this->hurtBox.height = DEF_HEIGHT_KING_DONUT;
            this->move = DEF_MOVE_KING_DONUT*moveVel;
            this->health = DEF_HEALTH_KING_DONUT;
            this->damage = DEF_DAMAGE_KING_DONUT;
            break;
        case TypeEnemy::CHAD_DONUT:
            this->hurtBox.width = DEF_WIDTH_CHAD_DONUT;
            this->hurtBox.height = DEF_HEIGHT_CHAD_DONUT;
            this->move = DEF_MOVE_CHAD_DONUT*moveVel;
            this->health = DEF_HEALTH_CHAD_DONUT;
            this->damage = DEF_DAMAGE_CHAD_DONUT;
            break;
    }
}

void Enemy::updateLogic(float deltaTime, Vector2 verse) {
    // update logic
    // decrease remaining time
    attackCooldownRemainingTime-= deltaTime;

    // enemy movements
    // upddate verse of the enemy
    currVerse = (verse.x != -1);

    // if movement occured
    if(verse.x != 0 || verse.y != 0) {
        isMoving = true;

        // transform unit vector into a slope
        float verse2d = std::atan2(verse.y, verse.x);

        // update enemy coords
        hurtBox.x+= std::cos(verse2d)*move;
        hurtBox.y+= std::sin(verse2d)*move;
    } else {
        isMoving = false;
    }

    // attack
    if(attackCooldownRemainingTime <= 0.0f) {
        // if enemy can attack -> start attacking
        isAttacking = true;
        attackCooldownRemainingTime = attackCooldown;
    }
}


void Enemy::draw() {
    // enemy body
    DrawTexturePro(
        *texture,
        {
            0.0f,
            0.0f,
            (currVerse) ? skinInfo.width : -skinInfo.width,
            skinInfo.height
        },
        hurtBox,
        {0.0f, 0.0f},
        0.0f,
        WHITE
    );
}


void Enemy::setSkin(EnemySkin* skin) {
    float enemyDimensionMul = getEnemyDimensionMul();

    this->texture = &skin->texture;
    this->skinInfo = skin->skinInfo;

    switch (this->skinInfo.type) {
        case TypeEnemy::DONUT:
            this->hurtBox.width = DEF_WIDTH_DONUT*enemyDimensionMul;
            this->hurtBox.height = DEF_HEIGHT_DONUT*enemyDimensionMul;
            break;
        case TypeEnemy::KING_DONUT:
            this->hurtBox.width = DEF_WIDTH_KING_DONUT*enemyDimensionMul;
            this->hurtBox.height = DEF_HEIGHT_KING_DONUT*enemyDimensionMul;
            break;
        case TypeEnemy::CHAD_DONUT:
            this->hurtBox.width = DEF_WIDTH_CHAD_DONUT*enemyDimensionMul;
            this->hurtBox.height = DEF_HEIGHT_CHAD_DONUT*enemyDimensionMul;
            break;
    }
}

void Enemy::setEnemyDimensionMul(float enemyDimensionMul) {
    float mul = std::clamp(enemyDimensionMul, MIN_MUL, MAX_MUL);
    hurtBox.width = getDefWidth(skinInfo.type)*mul;
    hurtBox.height = getDefHeight(skinInfo.type)*mul;
}

void Enemy::setMoveVel(float moveVel) {
    this->moveVel = std::clamp(moveVel, MIN_MUL, MAX_MUL);
    this->move = getDefMove(skinInfo.type)*this->moveVel;
}

void Enemy::setAttackCooldown(float attackCooldown) {
    this->attackCooldown = std::clamp(attackCooldown, MIN_ATTACK_COOLDOWN, MAX_ATTACK_COOLDOWN);
}

void Enemy::setHealth(int32_t health) {
    this->health = std::clamp(health, MIN_HEALTH, MAX_HEALTH);
}

void Enemy::setDamage(int32_t damage) {
    this->damage = std::clamp(damage, MIN_DAMAGE, MAX_DAMAGE);
}


EnemySkinInfo Enemy::getSkinInfo() {
    return skinInfo;
}

std::string Enemy::getSkinName() {
    return skinInfo.name;
}

float Enemy::getEnemyDimensionMul() {
    return hurtBox.width/skinInfo.width;
}

float Enemy::getMoveVel() {
    return  moveVel;
}

float Enemy::getAttackCooldown() {
    return attackCooldown;
}

int32_t Enemy::getHealth() {
    return health;
}

int32_t Enemy::getDamage() {
    return damage;
}

constexpr float Enemy::getDefHealth(TypeEnemy type) {
    switch (type) {
        case TypeEnemy::DONUT:
            return DEF_HEALTH_DONUT;
        case TypeEnemy::KING_DONUT:
            return DEF_HEALTH_KING_DONUT;
        case TypeEnemy::CHAD_DONUT:
            return DEF_HEALTH_CHAD_DONUT;
    }
}

constexpr float Enemy::getDefDamage(TypeEnemy type) {
    switch (type) {
        case TypeEnemy::DONUT:
            return DEF_DAMAGE_DONUT;
        case TypeEnemy::KING_DONUT:
            return DEF_DAMAGE_KING_DONUT;
        case TypeEnemy::CHAD_DONUT:
            return DEF_DAMAGE_CHAD_DONUT;
    }
}

constexpr float Enemy::getDefWidth(TypeEnemy type) {
    switch (type) {
        case TypeEnemy::DONUT:
            return DEF_WIDTH_DONUT;
        case TypeEnemy::KING_DONUT:
            return DEF_WIDTH_KING_DONUT;
        case TypeEnemy::CHAD_DONUT:
            return DEF_WIDTH_CHAD_DONUT;
    }
}

constexpr float Enemy::getDefHeight(TypeEnemy type) {
    switch (type) {
        case TypeEnemy::DONUT:
            return DEF_HEIGHT_DONUT;
        case TypeEnemy::KING_DONUT:
            return DEF_HEIGHT_KING_DONUT;
        case TypeEnemy::CHAD_DONUT:
            return DEF_HEIGHT_CHAD_DONUT;
    }
}

constexpr float Enemy::getDefMove(TypeEnemy type) {
    switch (type) {
        case TypeEnemy::DONUT:
            return DEF_MOVE_DONUT;
        case TypeEnemy::KING_DONUT:
            return DEF_MOVE_KING_DONUT;
        case TypeEnemy::CHAD_DONUT:
            return DEF_MOVE_CHAD_DONUT;
    }
}
