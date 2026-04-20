#ifndef _GAMEMANAGER_H
#define _GAMEMANAGER_H
#include<_common.h>
#include<_quad.h>
#include<level.h>
#include<glorp.h>
#include<gleep.h>
#include <_parallax.h>

class _gameManager
{
    public:
        _gameManager();
        virtual ~_gameManager();
        bool paused;
        enum state {MAIN_MENU, LEVEL_SELECT, PLAYER_SELECT, MAIN_GAME, END_SCREEN, HELP_SCREEN, PAUSED};
        enum screen {MENUPAGE, LEVELSELECTPAGE, PLAYERSELECTPAGE, GAMEBG, ENDPAGE, HELPPAGE, PAUSEPAGE};

        state actionTrigger;
        screen currentScreen;

//        level *gameLevel = new level();

        void initialize();
        void update();
        void drawWorld(float, float);

        _parallax *menuScreen = new _parallax();
        _parallax *helpScreen = new _parallax();
        _parallax *pauseScreen = new _parallax();

        struct buttonHitbox
        {
            float xPos;
            float yPos;
            float width;
            float height;
        };

        buttonHitbox startButton;
        buttonHitbox helpButton;
        buttonHitbox exitButton;
        buttonHitbox goBackButton;

        buttonHitbox makeHitbox(float, float, float, float);

    protected:

    private:
};

#endif // _GAMEMANAGER_H
