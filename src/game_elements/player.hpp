#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <cstdint>
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

    public:
        static const int DEF_WIDTH = 67, DEF_HEIGHT = 72, DEF_HEALTH = 100,
            DEF_BASE_KUNAI_DAMAGE = 40, DEF_KUNAI_WIDTH = 32, DEF_KUNAI_HEIGHT = 8;

        PlayerSkinInfo skinInfo;
        Texture2D* texture;

        Rectangle hurtBox;

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
        uint16_t health;

        unsigned long long score;

        // bools: fast comunication player <-> game_manager
        // whether player is moving in this frame
        bool isMoving,
        // whether player is attacking in this frame
            isAttacking,
        // whether player got hurted in this frame
            hurted,
        // indicate where player is watching: false = left | true = right
            currVerse;

        // keep track of the region of the texture for draw
        Rectangle srcTopDraw, srcBottomDraw;

        // kunai vars (useful to spawn)

        // multiplier of the dimension of the kunai
        float kunaiDimensionMul,
        // multiplier of the displacement of the kunai
            kunaiVel,
        // multiplier of the damage of the kunai
            kunaiDamageMul;

        std::vector<Kunai> kunais;

        // keep track of every region of the texture of the kunai
        std::vector<Rectangle> kunaisSrcDraw;

        Player(
            PlayerSkin* skin, // skin of the player
            float playerDimensionMul, // multiplier of the dimension of the player
            float kunaiDimensionMul, // multiplier of the dimension of the kunai
            float moveVel, // multiplier of the displacement of the player
            float attackVel, // multiplier of the speed of the player attacks
            float attackCooldown, // cooldown between two attacks
            uint16_t health, // health of the player
            float kunaiVel, // multiplier of the displacement of the kunai
            uint16_t kunaiDamageMul // multiplier of the damage of the kunai
        );
        Player(PlayerSkin* skin);

        // update player and kunais frames
        void updateGraphics(float deltaTime);
        // update player and kunais
        void updateLogic(float deltaTime, Vector2 verse);

        // draw player and kunais
        void draw();
};


#endif
