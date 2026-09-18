#include "player.hpp"
#include "kunai.hpp"
#include "../core/draw_manager.hpp"
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <raylib.h>
#include <vector>

// problem: float cant be static -> workaround like this
// specify duration of the action
const float IDLE_FRAME_PERIOD = 1.0f, RUN_FRAME_PERIOD = 2.0f,
    ATTACK_FRAME_PERIOD = 1.5f,
// default player displacement per frame
    DEF_PLAYER_MOVE = 10,
// default attack cooldown
    DEF_ATTACK_COOLDOWN = 5.0f,
// default kunai frame period
    KUNAI_FRAME_PERIOD = 0.2f,
// default kunai displacement per frame
    DEF_KUNAI_MOVE = 20,
// default kunai damage
    DEF_KUNAI_DAMAGE = 10,
// max time limit before kunai should despawn
    KUNAI_MAX_TTL = 2.0f;


Player::Player(PlayerSkin* skin)
    : Player(
        skin, // skin of the player
        3.0f, // multiplier of the dimension of the player
        5.0f, // multiplier of the dimension of the kunai
        1.0f, // multiplier of the displacement of the player
        1.0f, // multiplier of the speed of the player attacks
        DEF_ATTACK_COOLDOWN, // cooldown between two attacks
        DEF_HEALTH, // health of the player
        1.0f, // multiplier of the displacement of the kunai
        1.0f// multiplier of the damage of the kunai
    )
{}

Player::Player(
    PlayerSkin* skin, // skin of the player
    float playerDimensionMul, // multiplier of the dimension of the player
    float kunaiDimensionMul, // multiplier of the dimension of the kunai
    float moveVel, // multiplier of the displacement of the player
    float attackVel, // multiplier of the speed of the player attacks
    float attackCooldown, // cooldown between two attacks
    uint16_t health, // health of the player
    float kunaiVel, // multiplier of the displacement of the kunai
    uint16_t kunaiDamageMul // multiplier of the damage of the kunai
) {
    this->skinInfo = skin->skinInfo;
    this->texture = &skin->texture;
    this->hurtBox = {0.0f, 0.0f, DEF_WIDTH*playerDimensionMul, DEF_HEIGHT*playerDimensionMul};
    this->topHeight = hurtBox.height*(skinInfo.topHeight/(skinInfo.topHeight+skinInfo.bottomHeight));
    this->moveVel = moveVel;
    this->move = DEF_PLAYER_MOVE*moveVel;
    this->attackVel = attackVel;
    this->attackCooldown = attackCooldown;
    this->health = health;
    this->kunaiDimensionMul = kunaiDimensionMul;
    this->kunaiDamageMul = kunaiDamageMul;
    this->kunaiVel = kunaiVel;

    this->currAction = PlayerActions::IDLE;
    this->currTopActionFrame = 0;
    this->currBottomActionFrame = 0;
    this->topActionRemainingTime = 0.0f;
    this->bottomActionRemainingTime = 0.0f;
    this->attackCooldownRemainingTime = 0.0f;

    this->isMoving = false;
    this->isAttacking = false;
    this->hurted = false;
    this->currVerse = false;
    this->score = 0;

    this->srcTopDraw = {skinInfo.topIdleY, 0.0f, skinInfo.width, skinInfo.topHeight};
    this->srcBottomDraw = {skinInfo.bottomIdleY, 0.0f, skinInfo.width, skinInfo.bottomHeight};
    this->kunaisSrcDraw.reserve(skinInfo.kunaiTotFrame);
    for(int i = 0; i<skinInfo.kunaiTotFrame; i++) {
        this->kunaisSrcDraw.push_back({
            i*skinInfo.kunaiWidth,
            skinInfo.kunaiY,
            skinInfo.kunaiWidth,
            skinInfo.kunaiHeight
        });
    }

}

void Player::updateGraphics(float deltaTime) {
    // check if still alive
    if(health > 0) {
        // update currAction
        PlayerActions newAction = (isAttacking) ?
            (
                (isMoving) ?
                PlayerActions::ATTACK_RUN : PlayerActions::ATTACK_IDLE
            ) : (
                (isMoving) ?
                PlayerActions::RUN : PlayerActions::IDLE
            );

        // fast checks
        bool topActionEnded = (topActionRemainingTime <= 0.0f),
            bottomActionEnded = (bottomActionRemainingTime <= 0.0f),
            isActionNew = (currAction != newAction),
            wasntAttacking = (currAction != PlayerActions::ATTACK_IDLE && currAction != PlayerActions::ATTACK_RUN);

        switch (newAction) {
            case PlayerActions::IDLE:
                if(isActionNew) {
                    currTopActionFrame = 0;
                    currBottomActionFrame = 0;
                    topActionRemainingTime = IDLE_FRAME_PERIOD;
                    bottomActionRemainingTime = IDLE_FRAME_PERIOD;
                    srcTopDraw.y = skinInfo.topIdleY;
                    srcBottomDraw.y = skinInfo.bottomIdleY;

                } else {
                    // idle: top & bottom synced
                    if(topActionEnded) {
                        topActionRemainingTime = IDLE_FRAME_PERIOD;
                        currTopActionFrame = 0;
                        bottomActionRemainingTime = IDLE_FRAME_PERIOD;
                        currBottomActionFrame = 0;
                    } else { // update frame
                        currTopActionFrame = ((float)skinInfo.idleTotFrame-(topActionRemainingTime/(IDLE_FRAME_PERIOD/(float)skinInfo.idleTotFrame)));
                        currBottomActionFrame = currTopActionFrame;
                    }
                }
                break;

            case PlayerActions::RUN:
                if(isActionNew) {
                    currTopActionFrame = 0;
                    currBottomActionFrame = 0;
                    topActionRemainingTime = RUN_FRAME_PERIOD/moveVel;
                    bottomActionRemainingTime = RUN_FRAME_PERIOD/moveVel;
                    srcTopDraw.y = skinInfo.topRunY;
                    srcBottomDraw.y = skinInfo.bottomRunY;
                } else {
                    // run: top & bottom synced
                    if(topActionEnded) {
                        topActionRemainingTime = RUN_FRAME_PERIOD/moveVel;
                        currTopActionFrame = 0;
                        bottomActionRemainingTime = RUN_FRAME_PERIOD/moveVel;
                        currBottomActionFrame = 0;
                    } else { // update frame
                        currTopActionFrame = (float)skinInfo.runTotFrame-(topActionRemainingTime/((RUN_FRAME_PERIOD/moveVel)/(float)skinInfo.runTotFrame));
                        currBottomActionFrame = currTopActionFrame;
                    }
                }
                break;

            case PlayerActions::ATTACK_IDLE:
                if(isActionNew) {
                    currBottomActionFrame = 0;
                    bottomActionRemainingTime = IDLE_FRAME_PERIOD;
                    srcBottomDraw.y = skinInfo.bottomIdleY;

                    if(wasntAttacking) {
                        currTopActionFrame = 0;
                        topActionRemainingTime = ATTACK_FRAME_PERIOD/attackVel;
                        srcTopDraw.y = skinInfo.topAttackY;
                    }
                } else {
                    if(topActionEnded) {
                        topActionRemainingTime = ATTACK_FRAME_PERIOD/attackVel;
                        currTopActionFrame = 0;
                    } else { // update frame
                        currTopActionFrame = (float)skinInfo.attackTotFrame-(topActionRemainingTime/((ATTACK_FRAME_PERIOD/attackVel)/(float)skinInfo.attackTotFrame));
                    }

                    if(bottomActionEnded) {
                        bottomActionRemainingTime = IDLE_FRAME_PERIOD;
                        currBottomActionFrame = 0;
                    } else { // update frame
                        currBottomActionFrame = (float)skinInfo.idleTotFrame-(bottomActionRemainingTime/(IDLE_FRAME_PERIOD/(float)skinInfo.idleTotFrame));
                    }
                }
                break;

            case PlayerActions::ATTACK_RUN:
                if(isActionNew) {
                    currBottomActionFrame = 0;
                    bottomActionRemainingTime = RUN_FRAME_PERIOD/moveVel;
                    srcBottomDraw.y = skinInfo.bottomRunY;

                    if(wasntAttacking) {
                        currTopActionFrame = 0;
                        topActionRemainingTime = ATTACK_FRAME_PERIOD/attackVel;
                        srcTopDraw.y = skinInfo.topAttackY;
                    }
                } else {
                    if(topActionEnded) {
                        topActionRemainingTime = ATTACK_FRAME_PERIOD/attackVel;
                        currTopActionFrame = 0;
                    } else { // update frame
                        currTopActionFrame = (float)skinInfo.attackTotFrame-(topActionRemainingTime/((ATTACK_FRAME_PERIOD/attackVel)/(float)skinInfo.attackTotFrame));
                    }

                    if(bottomActionEnded) { // update frame
                        bottomActionRemainingTime = RUN_FRAME_PERIOD/moveVel;
                        currBottomActionFrame = 0;
                    } else {
                        currBottomActionFrame = (float)skinInfo.runTotFrame-(bottomActionRemainingTime/((RUN_FRAME_PERIOD/moveVel)/(float)skinInfo.runTotFrame));
                    }
                }
                break;
        }
        // update action
        currAction = newAction;
        // set srcDraw.x based on new frame
        srcTopDraw.x = currTopActionFrame*skinInfo.width;
        srcBottomDraw.x = currBottomActionFrame*skinInfo.width;

        // update kunais
        for(Kunai& kunai : kunais) {
            // decrease time
            kunai.periodElapsedTime-= deltaTime;


            if(kunai.periodElapsedTime <= 0.0f) { // refresh if animation ended
                kunai.periodElapsedTime = KUNAI_FRAME_PERIOD;
                kunai.currFrame = 0;
                // kunai.srcDraw.y = skinInfo.kunaiY;
            } else { // update frame
                kunai.currFrame = skinInfo.kunaiTotFrame-(kunai.periodElapsedTime/(KUNAI_FRAME_PERIOD/skinInfo.kunaiTotFrame));
            }
        }
    }
}

void Player::updateLogic(float deltaTime, Vector2 verse) {
    // update logic
    // decrease remaining time
    topActionRemainingTime-= deltaTime;
    bottomActionRemainingTime-= deltaTime;
    attackCooldownRemainingTime-= deltaTime;

    // player movements
    // upddate verse of the player
    currVerse = (verse.x != -1);

    // if movement occured
    if(verse.x != 0 || verse.y != 0) {
        isMoving = true;

        // transform unit vector into a slope
        float verse2d = std::atan2(verse.y, verse.x);

        // update player coords
        hurtBox.x+= std::cos(verse2d)*move;
        hurtBox.y+= std::sin(verse2d)*move;
    } else {
        isMoving = false;
    }

    // attack
    if(attackCooldownRemainingTime <= 0.0f) {
        // if player can attack -> start attacking
        isAttacking = true;
        attackCooldownRemainingTime =
            (ATTACK_FRAME_PERIOD/moveVel)+attackCooldown;


    } else if(isAttacking && topActionRemainingTime <= 0.0f) {
        // if player is attacking && ended animation
        isAttacking = false;

        // launch kunai
        kunais.push_back({
            (Rectangle) { // hitBox
                hurtBox.x + hurtBox.width/2,
                hurtBox.y + hurtBox.height/2,
                Player::DEF_KUNAI_WIDTH*kunaiDimensionMul,
                Player::DEF_KUNAI_HEIGHT*kunaiDimensionMul
            },
            DEF_KUNAI_MOVE*kunaiVel, // move
            0.0f, // slope // TODO: adjust slope to nearest enemy
            0.0f, // nearest
            0, // nearestIndex
            (uint16_t)(DEF_KUNAI_DAMAGE*kunaiDamageMul), // damage
            KUNAI_FRAME_PERIOD/kunaiVel, // periodElapsedTime
            0, // currFrame
            KUNAI_MAX_TTL // ttl
        });
    }

    for(int i = kunais.size()-1; i>=0; i--) {
        Kunai& k = kunais[i];

        k.ttl-= deltaTime;
        if(k.ttl > 0.0f) {
            // update kunai pos if is still valid (ttl not exceeded)
            k.hitBox.x+= std::cos(k.slope)*k.move;
            k.hitBox.y+= std::sin(k.slope)*k.move;
        } else {
            kunais.pop_back();
        }
    }
}

void Player::draw() {
    //draw player
    DrawTexturePro(
        *texture,
        {
            srcTopDraw.x,
            srcTopDraw.y,
            (currVerse) ? srcTopDraw.width : -srcTopDraw.width,
            srcTopDraw.height
        },
        {
            hurtBox.x,
            hurtBox.y,
            hurtBox.width,
            topHeight
        },
        {0.0f, 0.0f},
        0.0f,
        WHITE
    );

    // bottom body
    DrawTexturePro(
        *texture,
        {
            srcBottomDraw.x,
            srcBottomDraw.y,
            (currVerse) ? srcBottomDraw.width : -srcBottomDraw.width,
            srcBottomDraw.height
        },
        {
            hurtBox.x,
            hurtBox.y+topHeight,
            hurtBox.width,
            hurtBox.height-topHeight
        },
        {0.0f, 0.0f},
        0.0f,
        WHITE
    );

    // draw kunai
    for(const Kunai& k : kunais) {
        DrawTexturePro(
            *texture,
            kunaisSrcDraw[k.currFrame],
            k.hitBox,
            {0.0f, 0.0f},
            k.slope, // ok?
            WHITE
        );
    }
}
