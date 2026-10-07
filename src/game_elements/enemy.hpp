#ifndef ENEMY_HPP
#define  ENEMY_HPP

#include <cstdint>
#include <raylib.h>
#include "../core/draw_manager.hpp"

// TODO: spawn enemy

class Enemy{
    private:
        // default enemy displacement per frame
        static constexpr float DEF_MOVE_DONUT = 10,
            DEF_MOVE_KING_DONUT = 9,
            DEF_MOVE_CHAD_DONUT = 8;

        EnemySkinInfo skinInfo;
        Texture2D* texture;

        // displacement of the enemy per frame
        float move,
        // multiplier of the displacement of the enemy (consistent with move)
            moveVel,
        // cooldown between attacks
            attackCooldown,
        // cooldown time remaining since start of attack
            attackCooldownRemainingTime;

        int32_t health, damage;

    public:
        // width & height
        static constexpr int DEF_WIDTH_DONUT = 22, DEF_HEIGHT_DONUT = 22,
            DEF_WIDTH_KING_DONUT = 128, DEF_HEIGHT_KING_DONUT = 128,
            DEF_WIDTH_CHAD_DONUT = 128, DEF_HEIGHT_CHAD_DONUT = 172;

        // min/max health
        static constexpr int32_t MIN_HEALTH = 10, MAX_HEALTH = 10000,
        // default halth
            DEF_HEALTH_DONUT = 75,
            DEF_HEALTH_KING_DONUT = 225,
            DEF_HEALTH_CHAD_DONUT = 450,
        // delta of health
            DELTA_HEALTH = 10,

        // min/max damage
            MIN_DAMAGE = 1, MAX_DAMAGE = 10000,
        // default damage
            DEF_DAMAGE_DONUT = 10,
            DEF_DAMAGE_KING_DONUT = 22,
            DEF_DAMAGE_CHAD_DONUT = 30,
        // delta of damage
            DELTA_DAMAGE = 5;

        // default attack cooldown
        static constexpr float DEF_ATTACK_COOLDOWN = 1.5f,
        // default attack cooldown
            DELTA_ATTACK_COOLDOWN = 0.25f,

        // minimum/maximum values

        // (for multiplicator e.g.:moveVel, enemyDimensionMUl, ...)
            MIN_MUL = 0.25f, MAX_MUL = 10.0f,
        // delta of MUL
            DELTA_MUL = 0.25f,
        // minimum/maximum cooldown between attacks (in seconds)
            MIN_ATTACK_COOLDOWN = 0.0f, MAX_ATTACK_COOLDOWN = 10.0f;

        Rectangle hurtBox;

        // bools: fast comunication enemy <-> game_manager
        // whether enemy is moving in this frame
        bool isMoving, // useful?
        // whether enemy is attacking in this frame
            isAttacking,
        // whether enemy got hurted in this frame
            hurted, // useful?
        // indicate where enemy is watching: false = left | true = right
            currVerse;

        // short int speed = 250;
        // float x, y;
        // short int width, height;
        // int vita;
        // double xVel, yVel;
        // bool hitted;
        // unsigned short frameHit;
        // Rectangle oldRec;
        // TypeEnemy typeEnemy;

    Enemy(
        EnemySkin* skin, // skin of the enemy
        float enemyDimensionMul, // multiplier of the dimension of the enemy
        float moveVel, // multiplier of the displacement of the enemy
        float attackCooldown, // cooldown between two attacks
        int32_t health, // health of the enemy
        int32_t damage // damage of the enemy
    );
    Enemy(EnemySkin* skin);
    Enemy() = default;
    ~Enemy() = default;

    // copy Enemy info
    void copy(const Enemy& enemyCopy);
    // reset all Enemy modifiers (multipliers, ...)
    void resetModifiers();

    // update Enemy
    void updateLogic(float deltaTime, Vector2 verse);

    // draw Enemy
    void draw();

    // setters
    void setSkin(EnemySkin* skin);
    void setEnemyDimensionMul(float enemyDimensionMul);
    void setMoveVel(float moveVel);
    void setAttackCooldown(float attackCooldown);
    void setHealth(int32_t health);
    void setDamage(int32_t damage);

    // getters
    EnemySkinInfo getSkinInfo();
    std::string getSkinName();
    float getEnemyDimensionMul();
    float getMoveVel();
    float getAttackCooldown();
    int32_t getHealth();
    int32_t getDamage();


    // get default health
    static constexpr float getDefHealth(TypeEnemy type);
    // get default damage
    static constexpr float getDefDamage(TypeEnemy type);
    // get default width
    static constexpr float getDefWidth(TypeEnemy type);
    // get default height
    static constexpr float getDefHeight(TypeEnemy type);
    // get default enemy move
    static constexpr float getDefMove(TypeEnemy type);
};

#endif
