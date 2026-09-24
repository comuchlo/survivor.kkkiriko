#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <cstdint>
#include <list>
#include <raylib.h>
#include <vector>
#include "kunai.hpp"
#include "../core/draw_manager.hpp"

enum class PlayerActions {
  IDLE = 1,
  RUN,
  ATTACK_IDLE,
  ATTACK_RUN
};

class Player {
    private:
        // curent action of the frame
        PlayerActions currAction;
        // current frame
        uint8_t currTopActionFrame, currBottomActionFrame;
        // time remaining since start of action
        float topActionRemainingTime, bottomActionRemainingTime,
        // ( =hurtBox.height*(skinInfo.topHeight/(skinInfo.topHeight+skinInfo.bottomHeight)) )
            topHeight;

        PlayerSkinInfo skinInfo;
        Texture2D* texture;

        // keep track of the region of the texture for draw
        Rectangle srcTopDraw, srcBottomDraw;

        unsigned long long score;

        // displacement of the player per frame
        float move,
        // multiplier of the displacement of the player (consistent with move)
            moveVel,
        // speed of the attack
            attackVel,
        // cooldown between attacks
            attackCooldown,
        // cooldown time remaining since start of attack
            attackCooldownRemainingTime;

        int32_t health;

        // kunai vars (useful to spawn)

        // multiplier of the dimension of the kunai
        float kunaiDimensionMul,
        // multiplier of the displacement of the kunai
            kunaiVel,
        // multiplier of the damage of the kunai
            kunaiDamageMul;

        // keep track of every region of the texture of the kunai
        std::vector<Rectangle> kunaisSrcDraw;

    public:
        Rectangle hurtBox;

        // bools: fast comunication player <-> game_manager
        // whether player is moving in this frame
        bool isMoving,
        // whether player is attacking in this frame
            isAttacking,
        // whether player got hurted in this frame
            hurted,
        // indicate where player is watching: false = left | true = right
            currVerse;

        // O(1) for push_front & pop_back
        // begin (older kunais) -> end (newer kunais)
        std::list<Kunai> kunais;


        Player(
            PlayerSkin* skin, // skin of the player
            float playerDimensionMul, // multiplier of the dimension of the player
            float kunaiDimensionMul, // multiplier of the dimension of the kunai
            float moveVel, // multiplier of the displacement of the player
            float attackVel, // multiplier of the speed of the player attacks
            float attackCooldown, // cooldown between two attacks
            int32_t health, // health of the player
            float kunaiVel, // multiplier of the displacement of the kunai
            float kunaiDamageMul // multiplier of the damage of the kunai
        );
        Player(PlayerSkin* skin);
        Player() = default; // expose default constructor
        // Player(const Player& playerCopy);

        // copy player info
        void copy(const Player& playerCopy);
        // reset all player modifiers (multipliers, ...)
        void resetModifiers();

        // update player and kunais frames
        void updateGraphics(float deltaTime);
        // update player and kunais
        void updateLogic(float deltaTime, Vector2 verse);

        // draw player and kunais
        void draw();

        // setters
        void setSkin(PlayerSkin* skin);
        void setPlayerDimensionMul(float playerDimensionMul);
        void setKunaiDimensionMul(float kunaiDimensionMul);
        void setMoveVel(float moveVel);
        void setAttackVel(float attackVel);
        void setAttackCooldown(float attackCooldown);
        void setHealth(int32_t health);
        void setKunaiVel(float kunaiVel);
        void setKunaiDamageMul(float kunaiDamageMul);
        void incrementScore(unsigned long long int inc);

        // getters
        PlayerSkinInfo getSkinInfo();
        std::string getSkinName();
        float getPlayerDimensionMul();
        float getKunaiDimensionMul();
        float getMoveVel();
        float getAttackVel();
        float getAttackCooldown();
        int32_t getHealth();
        float getKunaiVel();
        float getKunaiDamageMul();
        unsigned long long int getScore();

        // get minimum multiplier value
        static float getMinMul();
        // get maximum multiplier value
        static float getMaxMul();
        //get minimum player health
        static int32_t getMinHealth();
        //get maximum player health
        static int32_t getMaxHealth();
        //get minimum attack cooldown
        static float getMinAttackCooldown();
        //get maximum attack cooldown
        static float getMaxAttackCooldown();
};


#endif
