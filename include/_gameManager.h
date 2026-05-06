#ifndef _GAMEMANAGER_H
#define _GAMEMANAGER_H
#include<_common.h>
#include<_quad.h>
#include<level.h>
#include<glorp.h>
#include<gleep.h>
#include <_parallax.h>
#include <_sounds.h>

class _gameManager
{
    public:
        _gameManager();
        virtual ~_gameManager();
        bool paused;
        enum {MAIN_MENU, LEVEL_SELECT, PLAYER_SELECT, MAIN_GAME, END_SCREEN, HELP_SCREEN, PAUSED, LANDING, CREDITS_PAUSE, HELP_SCREEN_PAUSED, CREDITS_MAIN_MENU};
        enum {MENUPAGE, LEVELSELECTPAGE, PLAYERSELECTPAGE, GAMEBG, ENDPAGE, HELPPAGE, PAUSEPAGE, LANDINGPAGE, CREDITSPAGE};

        vec2 worldScale;
        vec2 buttonScale;
        vec2 mousePos;

        bool mouseClicked = false;

        int currentState;
        int currentScreen;

        level *gameLevel = new level();

        void initialize();
        void loadSprites();
        void update();
        void drawWorld(float, float);
        void drawButtons();

        _parallax *landingScreen = new _parallax();
        _parallax *menuScreen = new _parallax();
        _parallax *helpScreen = new _parallax();
        _quad *pausePopup = new _quad(0, 0, 0, 0, 0, -8, 3.0, 2.0, 1.0, 1);
        _parallax *gleepWin = new _parallax();
        _parallax *glorpWin = new _parallax();
        _parallax *creditsScreen = new _parallax();

        struct button
        {
            float xPos;
            float yPos;
            float width;
            float height;
            _quad sprite;
            int screen;
        };

        vector<button> buttons;

        bool buttonColliding(int index);
        void reloadGLResources();

        _sounds *soundEngine = new _sounds();

    protected:

    private:
};

#endif // _GAMEMANAGER_H
