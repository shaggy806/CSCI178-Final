#ifndef _GAMEMANAGER_H
#define _GAMEMANAGER_H
#include<_common.h>

class _gameManager
{
    public:
        _gameManager();
        virtual ~_gameManager();
        bool paused;
        enum{MAIN_MENU,LEVEL_SELECT,PLAYER_SELECT,MAIN_GAME,END_SCREEN};
        int state;
    protected:

    private:
};

#endif // _GAMEMANAGER_H
