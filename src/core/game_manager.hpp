#ifndef GAME_MANAGER_HPP
#define GAME_MANAGER_HPP

// includes also <raylib.h>, kunai.hpp
#include "../game_elements/player.hpp"
// // includes also <raylib.h>
// #include "sound_manager.hpp"

class GameManager {
    private:
        static GameManager* instance;
        Camera2D camera1, camera2;
        //
        // da mettere nelle singole classi dei game elements
        //
        // const short int playerSpeed = 250, enemySpeed = 250, kunaiSpeed = 500, kunaiDamage = 40;
        // const short int offsetMappe = 50, frameAnimazioneCamminata = 8, fpsAnimazioneCamminata = 8;
        // const short int kunaiSize = 32, map2Width = 15360, map2Height = 8640, rangeSpawnEnemies = 1000;
        // const short int ciambellaSize = 22, ciambellaChadWidth = 128, ciambellaChadHeight = 172, ciambellaKingSize = 128;
        //
        unsigned long long bestSurvivedTime, bestScore;
        float eSpeedMultiplier = 1, pSpeedMultiplier = 1;
        std::vector<Player> players;

        GameManager();
    public:
        ~GameManager();
        GameManager(const GameManager&) = delete;
        GameManager& operator=(const GameManager&) = delete;
        static GameManager* getInstance();
};
#endif
