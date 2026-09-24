#include "game_manager.hpp"
#include "../components/lobby/lobby.hpp"
#include "draw_manager.hpp"
#include <algorithm>
#include <raylib.h>

GameManager* GameManager::instance = nullptr;
DrawManager* GameManager::drawer = nullptr;

GameManager::GameManager() {
    drawer = DrawManager::getInstance();
    mode = std::make_unique<Lobby>();

    cameras.push_back({{ 0, 0 }, { 0, 0 }, 0.0f, 1.0f });
    cameras.push_back({{ 0, 0 }, { 0, 0 }, 0.0f, 1.0f });
}

GameManager::~GameManager() {
    cameras.clear();
}

GameManager* GameManager::getInstance(){
    if (instance == nullptr){
        instance = new GameManager();

    }
    return instance;
}

void GameManager::resetCamera(int cameraNumber) {
    cameras[cameraNumber] = {(Vector2){ 0.0f, 0.0f}, (Vector2){ 0.0f, 0.0f}, 0.0f, 1.0f };
}

void GameManager::cameraFollowPlayer(int number) {
    cameras[number] = {
        {
            (float)DrawManager::RENDER_WIDTH/2,
            (float)DrawManager::RENDER_HEIGHT/2
        },
        {
            players[number].hurtBox.x + players[number].hurtBox.width / 2,
            players[number].hurtBox.y + players[number].hurtBox.height / 2
        },
        0.0f,
        1.0f
    };
}

float GameManager::getDeltaTime() {
    return deltaTime;
}

void GameManager::updateTime() {
    deltaTime = GetFrameTime();
}

void GameManager::updateGameTraining() {
    // UPDATE PLAYER 1
    Player* p = &players[0];
    Camera2D *cam = &cameras[0];
    Vector2 verse = {0.0f, 0.0f};


    if(p->getHealth() > 0) {
        if(IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) verse.y--;
        if(IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) verse.y++;
        if(IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) verse.x++;
        if(IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) verse.x--;

        p->updateLogic(deltaTime, verse);

        // limit player to map limits
        p->hurtBox.x = std::clamp(
            p->hurtBox.x,
            -(float)DrawManager::RENDER_WIDTH,
            (float)DrawManager::RENDER_WIDTH-p->hurtBox.width
        );

        p->hurtBox.y = std::clamp(
            p->hurtBox.y,
            -(float)DrawManager::RENDER_HEIGHT,
            (float)DrawManager::RENDER_HEIGHT-p->hurtBox.height
        );

        // limit camera to the map
        cam->target = {
            std::clamp(
                p->hurtBox.x + p->hurtBox.width / 2,
                -(float)DrawManager::RENDER_WIDTH / 2,
                (float)DrawManager::RENDER_WIDTH / 2
            ),
            std::clamp(
                p->hurtBox.y + p->hurtBox.height / 2,
                -(float)DrawManager::RENDER_HEIGHT / 2,
                (float)DrawManager::RENDER_HEIGHT / 2
            ),
        };

        // UPDATE ENEMIES

        // CHECK COLLISIONS


        p->updateGraphics(deltaTime);
    }
}

void GameManager::updateGameDuel() {
    Player *p1 = &players[0], *p2 = &players[1];
    Camera2D *cam1 = &cameras[0], *cam2 = &cameras[1];
    Vector2 verse = {0.0f, 0.0f};

    if(p1->getHealth() > 0 && p2->getHealth() > 0) {
        // PLAYER 1 UPDATE
        if(IsKeyDown(KEY_W)) verse.y++;
        if(IsKeyDown(KEY_S)) verse.y--;
        if(IsKeyDown(KEY_D)) verse.x++;
        if(IsKeyDown(KEY_A)) verse.x--;

        p1->updateLogic(deltaTime, verse);

        cam1->target = {
            p1->hurtBox.x + p1->hurtBox.width / 2,
            p1->hurtBox.y + p1->hurtBox.height / 2
        };

        // PLAYER 2 UPDATE
        verse = {0.0f, 0.0f};

        if(IsKeyDown(KEY_UP)) verse.y++;
        if(IsKeyDown(KEY_DOWN)) verse.y--;
        if(IsKeyDown(KEY_RIGHT)) verse.x++;
        if(IsKeyDown(KEY_LEFT)) verse.x--;

        p2->updateLogic(deltaTime, verse);

        cam2->target = {
            p2->hurtBox.x + p2->hurtBox.width / 2,
            p2->hurtBox.y + p2->hurtBox.height / 2
        };

        // UPDATE ENEMIES

        // CHECK COLLISIONS

         p1->updateGraphics(deltaTime);
         p2->updateGraphics(deltaTime);
    }
}

void GameManager::initTraining() {
    // load player 1 with default params
    players.push_back(Player(drawer->initTrainingTextures()));
    cameraFollowPlayer(0);
    // TODO: init enemies, ...
}

void GameManager::uninitTraining() {
    this->drawer->destroyTrainingTextures();
    players.clear();
}

void GameManager::initSurvival() {
    // load player 1 with default params
    players.push_back(Player(drawer->initSurvivorTextures()));
    cameraFollowPlayer(0);

    // TODO: init enemies, ...
}

void GameManager::uninitSurvival() {
    drawer->destroySurvivorTextures();
    players.clear();
}
