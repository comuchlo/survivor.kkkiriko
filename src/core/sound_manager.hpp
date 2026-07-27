#include <raylib.h>
#ifndef SOUND_MANAGER_HPP
#define SOUND_MANAGER_HPP

class SoundManager{
    private:
        static SoundManager* instance;
        float global= 75.0;
        float effects= 70.0;
        float music= 50.0;
        Music currentMusic, lobbyMusic, survivalMusic, duelMusic;
        Sound currentSound, slash;
        SoundManager();
    public:
        SoundManager(const SoundManager&) = delete;
        SoundManager& operator=(const SoundManager&) = delete;

        static SoundManager* getInstance();
        ~SoundManager();
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
};

#endif
