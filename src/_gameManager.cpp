#include "_gameManager.h"

_gameManager::_gameManager()
{
    currentState = LANDING;
    currentScreen = LANDINGPAGE;
}

_gameManager::~_gameManager()
{
    //dtor
}

void _gameManager::reloadGLResources()
{
    loadSprites();

    if (gameLevel)
    {
        gameLevel->reloadGLResources();
    }
}
void _gameManager::initialize()
{
    loadSprites();
}
void _gameManager::loadSprites()
{
    landingScreen->initPrlx("images/FinalLandingScreen.png");
    menuScreen->initPrlx("images/FinalMenuScreen.png");
    helpScreen->initPrlx("images/FinalHelpScreen.png");
    pausePopup->initQuad("images/FinalPausePopup.png");
    gleepWin->initPrlx("images/GleepWinsGlorpLoses.png");
    glorpWin->initPrlx("images/GlorpWinsGleepLoses.png");

    buttons.resize(9);

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

    buttons[3].sprite.initQuad("images/ButtonLV1.png");
    buttons[3].xPos = -0.25;
    buttons[3].yPos = 0;
    buttons[3].width = 0.1;
    buttons[3].height = 0.1;
    buttons[3].screen = LEVEL_SELECT;

    buttons[4].sprite.initQuad("images/ButtonLV2.png");
    buttons[4].xPos = 0;
    buttons[4].yPos = 0;
    buttons[4].width = 0.1;
    buttons[4].height = 0.1;
    buttons[4].screen = LEVEL_SELECT;

    buttons[5].sprite.initQuad("images/ButtonLV3.png");
    buttons[5].xPos = 0.25;
    buttons[5].yPos = 0;
    buttons[5].width = 0.1;
    buttons[5].height = 0.1;
    buttons[5].screen = LEVEL_SELECT;

    buttons[6].sprite.initQuad("images/ButtonCreditsFromPause.png");
    buttons[6].xPos = 0.15;
    buttons[6].yPos = -0.05;
    buttons[6].width = 0.06;
    buttons[6].height = 0.06;
    buttons[6].screen = PAUSED;

    buttons[7].sprite.initQuad("images/ButtonMenuFromPause.png");
    buttons[7].xPos = 0;
    buttons[7].yPos = -0.1;
    buttons[7].width = 0.06;
    buttons[7].height = 0.06;
    buttons[7].screen = PAUSED;

    buttons[8].sprite.initQuad("images/ButtonHelp.png");
    buttons[8].xPos = -0.15;
    buttons[8].yPos = -0.05;
    buttons[8].width = 0.06;
    buttons[8].height = 0.06;
    buttons[8].screen = PAUSED;

    //buttons[3].sprite.initQuad("images/ButtonGoBack.png");

}


void _gameManager::update()
{
    for (int i = 0; i < buttons.size(); i++)
    {
        if (buttons[i].screen == currentState)
            buttonColliding(i);   // updates brightness every frame
        else
            buttons[i].sprite.brightness = 1.0f;
    }

    for (int i = 0; i < buttons.size();i++) {
        if (mouseClicked && buttonColliding(i)) soundEngine->playSounds("sounds/menuSelect.wav");
    }

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
            soundEngine->pauseMusic("sounds/level1.mp3");
            soundEngine->pauseMusic("sounds/level2.mp3");
            soundEngine->pauseMusic("sounds/level3.mp3");
            currentState = END_SCREEN;
            currentScreen = ENDPAGE;
            soundEngine->playSounds("sounds/winScreen.wav");
        } else if (GetAsyncKeyState('P') & 0x8000)
        {
            currentState = PAUSED;
            currentScreen = PAUSEPAGE;
        }

        break;

    case LEVEL_SELECT:
        if (mouseClicked && buttonColliding(3))
        {
            soundEngine->pauseMusic("sounds/main_menu.mp3");
            gameLevel->loadLevel(0);
            currentState = MAIN_GAME;
            currentScreen = GAMEBG;
            soundEngine->playMusic("sounds/level1.mp3");
        }
        else if (mouseClicked && buttonColliding(4)){
            soundEngine->pauseMusic("sounds/main_menu.mp3");
            gameLevel->loadLevel(1);
            currentState = MAIN_GAME;
            currentScreen = GAMEBG;
            soundEngine->playMusic("sounds/level2.mp3");
        }
        else if (mouseClicked && buttonColliding(5)){
            soundEngine->pauseMusic("sounds/main_menu.mp3");
            gameLevel->loadLevel(2);
            currentState = MAIN_GAME;
            currentScreen = GAMEBG;
            soundEngine->playMusic("sounds/level3.mp3");
        }
        mouseClicked = false;
        break;

    case PLAYER_SELECT:
        // TO DO
        break;

    case END_SCREEN:
        if (mouseClicked)
        {
            soundEngine->playMusic("sounds/main_menu.mp3");
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

    case LANDING:
        if (mouseClicked)
        {
            mouseClicked = false;
            currentState = MAIN_MENU;
            currentScreen = MENUPAGE;
            soundEngine->playMusic("sounds/main_menu.mp3");
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
        gameLevel->drawLevel();
        pausePopup->drawQuad();
        drawButtons();
        break;

    case LANDINGPAGE:
        landingScreen->drawBackground(worldScale.x,worldScale.y);
        break;

    default:
        break;
    }


}
void _gameManager::drawButtons()
{
    glDisable(GL_LIGHTING);
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
    bool thing = (mouseDist <= buttons[index].width * buttonScale.x);
    if (thing){
        buttons[index].sprite.brightness = 0.8;
    } else{
        buttons[index].sprite.brightness = 1.0;
    }
    return (thing && buttons[index].screen == currentState);

}


