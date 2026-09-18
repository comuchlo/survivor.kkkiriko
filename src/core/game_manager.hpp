#ifndef GAME_MANAGER_HPP
#define GAME_MANAGER_HPP

// includes also <raylib.h>, kunai.hpp
#include "../game_elements/player.hpp"
#include "draw_manager.hpp"
#include "modality.hpp"
#include <memory>
#include <raylib.h>

class GameManager {
    private:
        static GameManager* instance;
        static DrawManager* drawer;
        //
        // da mettere nelle singole classi dei game elements
        //
        // const short int playerSpeed = 250, enemySpeed = 250, kunaiSpeed = 500, kunaiDamage = 40;
        // const short int offsetMappe = 50, frameAnimazioneCamminata = 8, fpsAnimazioneCamminata = 8;
        // const short int kunaiSize = 32, map2Width = 15360, map2Height = 8640, rangeSpawnEnemies = 1000;
        // const short int ciambellaSize = 22, ciambellaChadWidth = 128, ciambellaChadHeight = 172, ciambellaKingSize = 128;
        //
        unsigned long long bestSurvivedTime, bestScore;
        // float eSpeedMultiplier = 1, pSpeedMultiplier = 1;// ?
        float deltaTime;

        GameManager();
    public:
        ~GameManager();
        GameManager(const GameManager&) = delete;
        GameManager& operator=(const GameManager&) = delete;
        static GameManager* getInstance();
        std::unique_ptr<Modality> mode;
        std::vector<Player> players;
        std::vector<Camera2D> cameras;
        void resetCamera(int cameraNumber);
        void cameraFollowPlayer(int number);
        float getDeltaTime();
        void updateTime();
        void updateGameTraining();
        void updateGameDuel();

        void initTraining();
        void uninitTraining();

        void initSurvival();
        void uninitSurvival();
};
#endif
