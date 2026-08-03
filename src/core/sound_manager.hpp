#ifndef SOUND_MANAGER_HPP
#define SOUND_MANAGER_HPP

#include <raylib.h>

class SoundManager {
    private:
        static SoundManager* instance;
        float global= 75.0f;
        float effects= 70.0f;
        float music= 50.0f;
        Music currentMusic, lobbyMusic, survivalMusic, duelMusic;
        Sound currentSound, slash;

        SoundManager();
    public:
        ~SoundManager();
        SoundManager(const SoundManager&) = delete;
        SoundManager& operator=(const SoundManager&) = delete;
        static SoundManager* getInstance();

        void setGlobal(float);
        void setSFX(float);
        void setMusic(float);

        void incrementGlobalVolume();
        void incrementMusicVolume();
        void incrementSfxVolume();

        void decrementGlobalVolume();
        void decrementMusicVolume();
        void decrementSfxVolume();

        void resetVolume();

        float getGlobalLvl();
        float getMusicLvl();
        float getSfxLvl();

        void playCurrent();

        void updateAudio();
};

#endif
