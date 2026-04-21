#include "_gameManager.h"

_gameManager::_gameManager()
{
    currentState = MAIN_MENU;
    currentScreen = MENUPAGE;
}

_gameManager::~_gameManager()
{
    //dtor
}

void _gameManager::initialize()
{
    currentState = MAIN_MENU;
    menuScreen->initPrlx("images/FinalMenuScreen.png");
    helpScreen->initPrlx("images/FinalHelpScreen.png");
    pauseScreen->initPrlx("images/FinalPausedScreen.png");

    startButton = makeHitbox(-1.0, -1.0, -1.0, -1.0); // Placeholder Values
    helpButton = makeHitbox(-1.0, -1.0, -1.0, -1.0);
    exitButton = makeHitbox(-1.0, -1.0, -1.0, -1.0);
    goBackButton = makeHitbox(-1.0, -1.0, -1.0, -1.0);
}

_gameManager::buttonHitbox _gameManager::makeHitbox(float x, float y, float h, float w)
{
    _gameManager::buttonHitbox b;

    b.height = h;
    b.width = w;
    b.xPos = x;
    b.yPos = y;

    return b;
}

void _gameManager::update()
{
    switch (currentState) {

    case MAIN_MENU:
        menuScreen->drawBackground(worldScale.x,worldScale.y);
        break;

    case MAIN_GAME:
        // TO DO
        break;

    case LEVEL_SELECT:
        // TO DO
        break;

    case PLAYER_SELECT:
        // TO DO
        break;

    case END_SCREEN:
        // TO DO
        break;

    case HELP_SCREEN:
        // TO DO
        break;

    case PAUSED:
        // TO DO
        break;

    default:
        break;
    }
}

void _gameManager::drawWorld(float, float)
{
    glDisable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);

    switch (currentScreen) {

    case MENUPAGE:
        // TO DO
        break;

    case GAMEBG:
        // TO DO
        break;

    case LEVELSELECTPAGE:
        // TO DO
        break;

    case PLAYERSELECTPAGE:
        // TO DO
        break;

    case ENDPAGE:
        // TO DO
        break;

    case HELPPAGE:
        // TO DO
        break;

    case PAUSEPAGE:
        // TO DO
        break;

    default:
        break;
    }

    glDisable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
}

