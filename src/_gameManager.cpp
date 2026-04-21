#include "_gameManager.h"

_gameManager::_gameManager()
{
    actionTrigger = MAIN_MENU;
    currentScreen = MENUPAGE;
}

_gameManager::~_gameManager()
{
    //dtor
}

void _gameManager::initialize()
{
    menuScreen->initPrlx("images/menuScreen.png");
    helpScreen->initPrlx("images/HowToPlayScreen.png");
    pauseScreen->initPrlx("images/PausePop_Up.png");

    startButton = makeHitbox(-1.0, -1.0, -1.0, -1.0); // Placeholder Values
    helpButton = makeHitbox(-1.0, -1.0, -1.0, -1.0);
    exitButton = makeHitbox(-1.0, -1.0, -1.0, -1.0);
    goBackButton = makeHitbox(-1.0, -1.0, -1.0, -1.0);
}

_gameManager::buttonHitbox _gameManager::makeHitbox(float, float, float, float)
{
    _gameManager::buttonHitbox b;

    //TO DO

    return b;
}

void _gameManager::update()
{
    switch (actionTrigger) {

    case MAIN_MENU:
        // TO DO
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

