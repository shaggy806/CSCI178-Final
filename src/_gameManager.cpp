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
    loadSprites();
}
void _gameManager::loadSprites()
{
    menuScreen->initPrlx("images/FinalMenuScreen.png");
    helpScreen->initPrlx("images/FinalHelpScreen.png");
    pauseScreen->initPrlx("images/FinalPausedScreen.png");
    gleepWin->initPrlx("images/GleepWinsGlorpLoses.png");
    glorpWin->initPrlx("images/GlorpWinsGleepLoses.png");

    buttons.resize(6);

    buttons[0].sprite.initQuad("images/ButtonExit.png");
    buttons[0].xPos = -0.35;
    buttons[0].yPos = -0.25;
    buttons[0].width = 0.1;
    buttons[0].height = 0.1;
    buttons[0].screen = MAIN_MENU;


    buttons[1].sprite.initQuad("images/ButtonHelp.png");
    buttons[1].xPos = 0.35;
    buttons[1].yPos = -0.25;
    buttons[1].width = 0.1;
    buttons[1].height = 0.1;
    buttons[1].screen = MAIN_MENU;


    buttons[2].sprite.initQuad("images/ButtonStart.png");
    buttons[2].xPos = 0;
    buttons[2].yPos = -0.3;
    buttons[2].width = 0.1;
    buttons[2].height = 0.1;
    buttons[2].screen = MAIN_MENU;

    buttons[3].sprite.initQuad("images/ButtonStart.png");
    buttons[3].xPos = -0.25;
    buttons[3].yPos = 0;
    buttons[3].width = 0.1;
    buttons[3].height = 0.1;
    buttons[3].screen = LEVEL_SELECT;

    buttons[4].sprite.initQuad("images/ButtonStart.png");
    buttons[4].xPos = 0;
    buttons[4].yPos = 0;
    buttons[4].width = 0.1;
    buttons[4].height = 0.1;
    buttons[4].screen = LEVEL_SELECT;

    buttons[5].sprite.initQuad("images/ButtonStart.png");
    buttons[5].xPos = 0.25;
    buttons[5].yPos = 0;
    buttons[5].width = 0.1;
    buttons[5].height = 0.1;
    buttons[5].screen = LEVEL_SELECT;


    //buttons[3].sprite.initQuad("images/ButtonGoBack.png");

}


void _gameManager::update()
{
    switch (currentState) {

    case MAIN_MENU:
        if (mouseClicked && buttonColliding(1))
        {
            currentState = HELP_SCREEN;
            currentScreen = HELPPAGE;
        }
        else if (mouseClicked && buttonColliding(0)){
            exit(0);
        }
        else if (mouseClicked && buttonColliding(2)){
            currentState = LEVEL_SELECT;
            currentScreen = LEVELSELECTPAGE;
        }
        mouseClicked = false;
        break;

    case MAIN_GAME:
        gameLevel->updateLevel();
        if (gameLevel->checkWinner()){
            currentState = END_SCREEN;
            currentScreen = ENDPAGE;
        } else if (GetAsyncKeyState('P') & 0x8000)
        {
            currentState = PAUSED;
            currentScreen = PAUSEPAGE;
        }

        break;

    case LEVEL_SELECT:
        if (mouseClicked && buttonColliding(3))
        {
            gameLevel->loadLevel(0);
            currentState = MAIN_GAME;
            currentScreen = GAMEBG;
        }
        else if (mouseClicked && buttonColliding(4)){
            gameLevel->loadLevel(1);
            currentState = MAIN_GAME;
            currentScreen = GAMEBG;
        }
        else if (mouseClicked && buttonColliding(5)){
            gameLevel->loadLevel(2);
            currentState = MAIN_GAME;
            currentScreen = GAMEBG;
        }
        mouseClicked = false;
        break;

    case PLAYER_SELECT:
        // TO DO
        break;

    case END_SCREEN:
        if (mouseClicked)
        {
            mouseClicked = false;
            currentState = MAIN_MENU;
            currentScreen = MENUPAGE;
        }
        break;

    case HELP_SCREEN:
        if (mouseClicked)
        {
            mouseClicked = false;
            currentState = MAIN_MENU;
            currentScreen = MENUPAGE;
        }
        break;

    case PAUSED:
        if (mouseClicked)
        {
            mouseClicked = false;
            currentState = MAIN_GAME;
            currentScreen = GAMEBG;
        }
        break;

    default:
        break;
    }
}

void _gameManager::drawWorld(float, float)
{
    glDisable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);

    switch (currentScreen)
    {

    case MENUPAGE:
        menuScreen->drawBackground(worldScale.x,worldScale.y);
        drawButtons();
        break;

    case GAMEBG:
        gameLevel->drawLevel();
        break;

    case LEVELSELECTPAGE:
        drawButtons();
        break;

    case PLAYERSELECTPAGE:
        // TO DO
        break;

    case ENDPAGE:
        if (gameLevel->winner == 0){
            glorpWin->drawBackground(worldScale.x,worldScale.y);
        } else{
            gleepWin->drawBackground(worldScale.x,worldScale.y);
        }
        break;

    case HELPPAGE:
        helpScreen->drawBackground(worldScale.x,worldScale.y);
        break;

    case PAUSEPAGE:
        pauseScreen->drawBackground(worldScale.x,worldScale.y);
        break;

    default:
        break;
    }


}
void _gameManager::drawButtons()
{
    for (int i = 0; i < buttons.size();i++)
    {
        if (buttons[i].screen == currentState){
        buttons[i].sprite.pos.z = -5;
        buttons[i].sprite.pos.x = buttons[i].xPos * buttonScale.x;
        buttons[i].sprite.pos.y = buttons[i].yPos * buttonScale.y;
        buttons[i].sprite.scale.x = buttons[i].width * buttonScale.x;
        buttons[i].sprite.scale.y = buttons[i].height * buttonScale.x;

        buttons[i].sprite.drawQuad();
        }
    }
}

bool _gameManager::buttonColliding(int index)
{
    float mouseDist = sqrt( (mousePos.x - buttons[index].xPos * buttonScale.x) * (mousePos.x - buttons[index].xPos * buttonScale.x) + (mousePos.y - buttons[index].yPos * buttonScale.y) * (mousePos.y - buttons[index].yPos * buttonScale.y) );
    return (mouseDist <= buttons[index].width * buttonScale.x);
}


