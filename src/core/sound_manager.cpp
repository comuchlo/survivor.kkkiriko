#include "sound_manager.hpp"
#include <raylib.h>

SoundManager* SoundManager::instance = nullptr;

SoundManager::SoundManager(){
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

    SetSoundVolume(currentSound, (effects / 100.0f) * (global / 100.0f));
    SetMusicVolume(currentMusic, (music / 100.0f) * (global / 100.0f));
    PlayMusicStream(currentMusic);
}

SoundManager::~SoundManager(){
    UnloadSound(slash);

    UnloadMusicStream(lobbyMusic);
    UnloadMusicStream(duelMusic);
    UnloadMusicStream(survivalMusic);

    CloseAudioDevice();
}

SoundManager* SoundManager::getInstance(){
    if (instance == nullptr){
        instance = new SoundManager();
    }
    return instance;
}

void SoundManager::updateAudio() {
    UpdateMusicStream(currentMusic);
}

void SoundManager::setGlobal(float level){
    global = level;
    SetMusicVolume(currentMusic, ( music / 100.0f) * ( global / 100.0f));
    SetSoundVolume(currentSound, ( effects / 100.0f) * ( global / 100.0f));
}

void SoundManager::setMusic(float level){
    music = level;
    SetMusicVolume(currentMusic, ( music / 100.0f) * ( global / 100.0f));
}

void SoundManager::setSFX(float level){
    effects = level;
    SetSoundVolume(currentSound, ( effects / 100.0f) * ( global / 100.0f));
}


void SoundManager::incrementGlobalVolume(){
    global = (global+5.0f>=100.0f) ? 100.0f : global+5.0f;

    SetMusicVolume(currentMusic, ( music / 100.0f) * ( global / 100.0f));
    SetSoundVolume(currentSound, ( effects / 100.0f) * ( global / 100.0f));
}
void SoundManager::incrementMusicVolume(){
    music = (music+5.0f>=100.0f) ? 100.0f : music+5.0f;
    SetMusicVolume(currentMusic, ( music / 100.0f) * ( global / 100.0f));
}
void SoundManager::incrementSfxVolume(){
    effects = (effects+5.0f>=100.0f) ? 100.0f : effects+5.0f;
    SetSoundVolume(currentSound, ( effects / 100.0f) * ( global / 100.0f));
}

void SoundManager::decrementGlobalVolume(){
    global = (global-5.0f <= 0.0f) ? 0.0f : global-5.0f;

    SetMusicVolume(currentMusic, ( music / 100.0f) * ( global / 100.0f));
    SetSoundVolume(currentSound, ( effects / 100.0f) * ( global / 100.0f));
}
void SoundManager::decrementMusicVolume(){
    music = (music-5.0f <= 0.0f) ? 0.0f : music-5.0f;
    SetMusicVolume(currentMusic, ( music / 100.0f) * ( global / 100.0f));
}
void SoundManager::decrementSfxVolume(){
    effects = (effects-5.0f <= 0.0f) ? 0.0f : effects-5.0f;
    SetSoundVolume(currentSound, ( effects / 100.0f) * ( global / 100.0f));
}

void SoundManager::resetVolume(){
    global= 50.0f;
    effects= 70.0f;
    music= 50.0f;

    SetMusicVolume(currentMusic, ( music / 100.0f) * ( global / 100.0f));
    SetSoundVolume(currentSound, ( effects / 100.0f) * ( global / 100.0f));
}

float SoundManager::getGlobalLvl(){
    return global;
}
float SoundManager::getMusicLvl(){
    return music;
}
float SoundManager::getSfxLvl(){
    return effects;
}

void SoundManager::playCurrent(){
    PlaySound(currentSound);
}
