#ifndef _SOUNDS_H
#define _SOUNDS_H

#include <_common.h>
#include <SNDS/irrKlang.h>

using namespace irrklang;

class _sounds
{
    public:
        _sounds();
        virtual ~_sounds();

        void playMusic(char*);
        void playSounds(char*);
        void pauseMusic(bool); // Changed to take a boolean for pause/unpause
        void initSounds();

        ISoundEngine *sndEng = createIrrKlangDevice();

    protected:

    private:
        ISound* currentMusic = nullptr; // Add this pointer to track the music
};

#endif // _SOUNDS_H
