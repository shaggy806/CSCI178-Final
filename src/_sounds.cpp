#include "_sounds.h"
#include <iostream>

_sounds::_sounds()
{
    //ctor
}

_sounds::~_sounds()
{
    //dtor
    if(currentMusic) {
        currentMusic->drop(); // Clean up the tracked sound
    }
    sndEng->drop();
}

void _sounds::playMusic(char* fileName)
{
    // If music is already playing, drop it before starting a new one
    if (currentMusic) {
        currentMusic->stop();
        currentMusic->drop();
    }

    // The 4th parameter 'true' tells irrKlang to track the sound and return a pointer
    currentMusic = sndEng->play2D(fileName, true, false, true);
}

void _sounds::playSounds(char* fileName)
{
    sndEng->play2D(fileName, false, false);
}

void _sounds::pauseMusic(bool isPaused)
{
    // Check if the music pointer exists, then pause or unpause it
    if(currentMusic) {
        currentMusic->setIsPaused(isPaused);
    }
}

void _sounds::initSounds()
{
    if(!sndEng) std::cout << "ERROR** Sound Engine did not start!" << std::endl;
    return;
}
