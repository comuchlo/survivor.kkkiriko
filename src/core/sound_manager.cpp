#include "sound_manager.hpp"
#include <algorithm>
#include <raylib.h>

SoundManager* SoundManager::instance = nullptr;

SoundManager::SoundManager() {
    InitAudioDevice();
    while(!IsAudioDeviceReady()) { WaitTime(0.01f); } // profilactic tactics

    slash = LoadSound("./audio/slash.mp3");

    lobbyMusic = LoadMusicStream("./audio/temp lobby8bit.mp3");
	survivalMusic = LoadMusicStream("./audio/temp survival8bit.mp3");
	duelMusic = LoadMusicStream("./audio/temp duel8bit.mp3");

	//sound
    currentSound = slash;//use currentSound to play all the sound with adjusted volume

    //music
    currentMusic = lobbyMusic;//use currentMusic to play all the music with adjusted volume
    currentMusic.looping = true;

    SetSoundVolume(currentSound, effects*global);
    SetMusicVolume(currentMusic, music*global);
    PlayMusicStream(currentMusic);
}

SoundManager::~SoundManager() {
    UnloadSound(slash);

    UnloadMusicStream(lobbyMusic);
    UnloadMusicStream(duelMusic);
    UnloadMusicStream(survivalMusic);

    CloseAudioDevice();
}

SoundManager* SoundManager::getInstance() {
    if (instance == nullptr){
        instance = new SoundManager();
    }
    return instance;
}

void SoundManager::updateAudio() {
    UpdateMusicStream(currentMusic);
}

// void SoundManager::setGlobal(float level){
//     global = level;
//     SetMusicVolume(currentMusic, music*global);
//     SetSoundVolume(currentSound, effects*global);
// }

// void SoundManager::setMusic(float level){
//     music = level;
//     SetMusicVolume(currentMusic, music*global);
// }

// void SoundManager::setSFX(float level){
//     effects = level;
//     SetSoundVolume(currentSound, effects*global);
// }


void SoundManager::incrementGlobalVolume() {
    global = std::min(global+DELTA_LVL, 1.0f);

    SetMusicVolume(currentMusic, music*global);
    SetSoundVolume(currentSound, effects*global);
}
void SoundManager::incrementMusicVolume() {
    music = std::min(music+DELTA_LVL, 1.0f);

    SetMusicVolume(currentMusic, effects*global);
}
void SoundManager::incrementSfxVolume() {
    effects = std::min(effects+DELTA_LVL, 1.0f);

    SetSoundVolume(currentSound, effects*global);
}

void SoundManager::decrementGlobalVolume() {
    global = std::max(global-DELTA_LVL, 0.0f);

    SetMusicVolume(currentMusic, music*global);
    SetSoundVolume(currentSound, effects*global);
}
void SoundManager::decrementMusicVolume() {
    music = std::max(music-DELTA_LVL, 0.0f);

    SetMusicVolume(currentMusic, music*global);
}
void SoundManager::decrementSfxVolume() {
    effects = std::max(effects-DELTA_LVL, 0.0f);

    SetSoundVolume(currentSound, effects*global);
}

void SoundManager::resetVolume() {
    global= DEF_GLOBAL_LVL;
    effects= DEF_EFFECTS_LVL;
    music= DEF_MUSIC_LVL;

    SetMusicVolume(currentMusic, music*global);
    SetSoundVolume(currentSound, effects*global);
}

float SoundManager::getGlobalLvl() {
    return global;
}

float SoundManager::getMusicLvl() {
    return music;
}

float SoundManager::getSfxLvl() {
    return effects;
}

void SoundManager::playCurrent() {
    PlaySound(currentSound);
}
