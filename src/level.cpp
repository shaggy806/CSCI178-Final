#include "level.h"

level::level()
{
    //ctor
}

level::~level()
{
    //dtor
}



void level::loadSprites()
{
    sprites.resize(1);
    sprites[0].initQuad("images/BlockPlatformUltraWide.png");
}

void level::loadLevel(int levelID)
{
    currentLevelID = levelID;
    loaded = true;
    blocks.clear();
    glp->init();
    glp->yPos = 0.3;
    glp->xPos = 0.3;
    glp->xV=0;
    glp->yV=0;

    glrp->init();
    glrp->yPos = 0.3;
    glrp->xPos = -0.3;
    glrp->xV=0;
    glrp->yV=0;

    loadSprites();
    switch (levelID)
    {
    case 0:
        background->initPrlx("images/MoonBG.png");
        addBlock(0,-0.5,0.5,0.1,0, false);
        break;
    case 1:
        background->initPrlx("images/MarsBg.png");
        addBlock(0,-0.5,0.5,0.1,0,false);
        addBlock(-0.25,-0.15,0.13,0.03,0,true);
        addBlock(0.25,-0.15,0.13,0.03,0,true);
        addBlock(0,0.1,0.13,0.03,0,true);
        break;
    case 2:
        background->initPrlx("images/MarmiteBg.png");
        addBlock(0,-0.5,0.5,0.1,0,false);
        addBlock(0,-0.12,0.3,0.02,0,true);
        break;
    default:
        background->initPrlx("images/MoonBG.png");
        addBlock(0,-0.5,0.5,0.1,0,false);
        addBlock(0,-0.5,0.5,0.1,0,true);
        addBlock(0,-0.5,0.5,0.1,0,true);
        break;
    }
    particleSystem->load();
}
void level::updateLevel()
{
    if (glorpStepTimer >= 1) glorpStepTimer += 1;
    if (glorpStepTimer >= 101) glorpStepTimer = 0;
    if (gleepStepTimer >= 1) gleepStepTimer += 1;
    if (gleepStepTimer >= 201) gleepStepTimer = 0;


    bool isWPressed = GetAsyncKeyState('W') & 0x8000;
    bool isAPressed = GetAsyncKeyState('A') & 0x8000;
    bool isSPressed = GetAsyncKeyState('S') & 0x8000;
    bool isDPressed = GetAsyncKeyState('D') & 0x8000;

    bool isUpPressed = GetAsyncKeyState(VK_UP) & 0x8000;
    bool isDownPressed = GetAsyncKeyState(VK_DOWN) & 0x8000;
    bool isLeftPressed = GetAsyncKeyState(VK_LEFT) & 0x8000;
    bool isRightPressed = GetAsyncKeyState(VK_RIGHT) & 0x8000;

    float maxSpeed = 0.5f;

    glp->xPos+=glp->xV*dt;
    if (gleepCollide())
    {
        glp->xPos-=glp->xV*dt;
        glp->xV =0;
    }
    float accel = 5.0f;
    float decel = 8.0f;

    if (isLeftPressed)
    {
        if (glp->xV >= -maxSpeed) glp->xV -= accel * dt;
        if (gleepStepTimer == 0 && glp->animation < 2)
        {
            soundEngine->playSounds("sounds/gleepWalk.wav");
            gleepStepTimer = 1;
        }
    }
    else if (isRightPressed)
    {
        if (glp->xV <= maxSpeed) glp->xV += accel * dt;
        if (gleepStepTimer == 0 && glp->animation < 2)
        {
            soundEngine->playSounds("sounds/gleepWalk.wav");
            gleepStepTimer = 1;
        }
    }
    else
    {
        if (glp->xV > 0)
        {
            glp->xV -= decel * dt;
            if (glp->xV < 0) glp->xV = 0;
        }
        else if (glp->xV < 0)
        {
            glp->xV += decel * dt;
            if (glp->xV > 0) glp->xV = 0;
        }
    }

    glp->yPos+=glp->yV*dt;

    if (gleepCollide() && glp->yV <0 && isUpPressed)
    {
        soundEngine->playSounds("sounds/gleepJump.wav");
        glp->yPos-=glp->yV*dt;
        glp->yV = 1;

    }
    else if (gleepCollide())
    {
        glp->yPos-=glp->yV*dt;
        glp->yV =0;
    }
    glp->yV-=1.5*dt;

    // Glorp Movement:

    glrp->xPos += glrp->xV * dt;
    if (glorpCollide())
    {
        glrp->xPos -= glrp->xV * dt;
        glrp->xV = 0;
    }

    if (isAPressed)
    {
        if (glrp->xV >= -maxSpeed) glrp->xV -= accel * dt;
        if (glorpStepTimer == 0 && glrp->animation < 2)
        {
            soundEngine->playSounds("sounds/glorpWalk.wav");
            glorpStepTimer = 1;
        }
    }
    else if (isDPressed)
    {
        if (glrp->xV <= maxSpeed) glrp->xV += accel * dt;
        if (glorpStepTimer == 0 && glrp->animation < 2)
        {
            soundEngine->playSounds("sounds/glorpWalk.wav");
            glorpStepTimer = 1;
        }
    }
    else
    {
        if (glrp->xV > 0)
        {
            glrp->xV -= decel * dt;
            if (glrp->xV < 0) glrp->xV = 0;
        }
        else if (glrp->xV < 0)
        {
            glrp->xV += decel * dt;
            if (glrp->xV > 0) glrp->xV = 0;
        }
    }

    glrp->yPos += glrp->yV * dt;
    if (glorpCollide() && glrp->yV < 0 && isWPressed)
    {
        glrp->yPos -= glrp->yV * dt;
        glrp->yV = 1;
        soundEngine->playSounds("sounds/glorpJump.wav");
    }
    else if (glorpCollide())
    {
        glrp->yPos -= glrp->yV * dt;
        glrp->yV = 0;
    }
    glrp->yV -= 1.5 * dt;

    glp->attackCooldown+=dt;
    if (glp->attackCooldown > 0.25) glp->isKicking = false;

    glrp->attackCooldown+=dt;

    if (isSPressed && glrp->attackCooldown>1 && glrp->xV != 0)
    {
        glrp->xV *= 2;
        soundEngine->playSounds("sounds/glorpDash.wav");
        if (playersCollide())
        {
            glp->xV = glrp->xV*3;
            glp->yV *= -0.25;
        }
        glrp->attackCooldown = 0;
    }
    if (isDownPressed && glp->attackCooldown>1)
    {
        soundEngine->playSounds("sounds/gleepKick.wav");

        glp->isKicking = true;

        if (playersCollide())
        {
            glrp->yV = 1;
            if (glp->xV > 0) {
                    glrp->xV = 2;
            } else if (glp->xV < 0) {
                    glrp->xV = -2;
            } else {
                glrp->yV = 1.5;
            }
        }
        glp->attackCooldown = 0;
    }
    particleSystem->addParticle(glp->xPos,glp->yPos-0.049,0.3,0.3,0,0.002,1,1,1,1);

    particleSystem->updateParticles(dt);
}


void level::addBlock(float x, float y, float w, float h, int sprite, bool visible)
{
    block newBlock;
    newBlock.x = x;
    newBlock.y = y;
    newBlock.scaleX = w;
    newBlock.scaleY = h;
    newBlock.sprite = sprite;
    newBlock.visible = visible;
    blocks.push_back(newBlock);

}

void level::reloadGLResources()
{
    if (!loaded) return;

    loadSprites();
    particleSystem->reload();

    glp->sprite->initQuad("images/GleepNew.png");
    glrp->sprite->initQuad("images/cleanGlorp.png");

    switch (currentLevelID)
    {
    case 0:
        background->initPrlx("images/MoonBG.png");
        break;
    case 1:
        background->initPrlx("images/MarsBg.png");
        break;
    case 2:
        background->initPrlx("images/MarmiteBg.png");
        break;
    default:
        background->initPrlx("images/MoonBG.png");
        break;
    }
}

void level::drawLevel()
{
    background->drawBackground(worldScale.x,worldScale.y);


    for (int i = 0; i < blocks.size(); i++)
    {
        if (blocks[i].visible)
        {
            sprites[blocks[i].sprite].pos.z = -8;
            sprites[blocks[i].sprite].pos.x = blocks[i].x * levelScale.x;
            sprites[blocks[i].sprite].pos.y = blocks[i].y * levelScale.y;

            sprites[blocks[i].sprite].scale.x = blocks[i].scaleX * levelScale.x;
            sprites[blocks[i].sprite].scale.y = blocks[i].scaleY * levelScale.y;


            sprites[blocks[i].sprite].drawQuad();
        }
    }

    glp->sprite->scale.x = glp->width*levelScale.x;
    glp->sprite->scale.y = glp->height*levelScale.y;
    glp->sprite->pos.x = glp->xPos*levelScale.x;
    glp->sprite->pos.y = glp->yPos*levelScale.y;

    glp->updatePlayer(dt);
    glp->displayPlayer();

    glrp->sprite->scale.x = glrp->width*levelScale.x;
    glrp->sprite->scale.y = glrp->height*levelScale.y;
    glrp->sprite->pos.x = glrp->xPos*levelScale.x;
    glrp->sprite->pos.y = glrp->yPos*levelScale.y;

    glrp->updatePlayer(dt);
    glrp->displayPlayer();


    particleSystem->drawParticles();
}

bool level::gleepCollide()
{
    float glpLeft   = glp->xPos - glp->width  / 1.2f;
    float glpRight  = glp->xPos + glp->width  / 1.2f;
    float glpBottom = glp->yPos - glp->height / 1.25f;
    float glpTop    = glp->yPos + glp->height / 1.25f;

    for (int i = 0; i < blocks.size(); i++)
    {
        float blockLeft   = blocks[i].x - blocks[i].scaleX / 1.0f;
        float blockRight  = blocks[i].x + blocks[i].scaleX / 1.0f;
        float blockBottom = blocks[i].y - blocks[i].scaleY / 1.0f;
        float blockTop    = blocks[i].y + blocks[i].scaleY / 1.0f;

        if (glpRight > blockLeft &&
                glpLeft < blockRight &&
                glpTop > blockBottom &&
                glpBottom < blockTop)
        {
            return true;
        }
    }

    return false;
}
bool level::glorpCollide()
{
    float glrpLeft   = glrp->xPos - glrp->width  / 1.2f;
    float glrpRight  = glrp->xPos + glrp->width  / 1.2f;
    float glrpBottom = glrp->yPos - glrp->height / 1.0f;
    float glrpTop    = glrp->yPos + glrp->height / 1.0f;

    for (int i = 0; i < blocks.size(); i++)
    {
        float blockLeft   = blocks[i].x - blocks[i].scaleX / 1.0f;
        float blockRight  = blocks[i].x + blocks[i].scaleX / 1.0f;
        float blockBottom = blocks[i].y - blocks[i].scaleY / 1.0f;
        float blockTop    = blocks[i].y + blocks[i].scaleY / 1.0f;

        if (glrpRight > blockLeft &&
                glrpLeft < blockRight &&
                glrpTop > blockBottom &&
                glrpBottom < blockTop)
        {
            return true;
        }
    }
    return false;
}


bool level::playersCollide()
{
    float glpLeft   = glp->xPos - glp->width  / 1.2f;
    float glpRight  = glp->xPos + glp->width  / 1.2f;
    float glpBottom = glp->yPos - glp->height / 1.25f;
    float glpTop    = glp->yPos + glp->height / 1.25f;

    float glrpLeft   = glrp->xPos - glrp->width  / 1.2f;
    float glrpRight  = glrp->xPos + glrp->width  / 1.2f;
    float glrpBottom = glrp->yPos - glrp->height / 1.0f;
    float glrpTop    = glrp->yPos + glrp->height / 1.0f;

    return (glpRight > glrpLeft &&
            glpLeft < glrpRight &&
            glpTop > glrpBottom &&
            glpBottom < glrpTop);
}
bool level::checkWinner()
{

    if (glp->yPos < -1)
    {
        winner = 0;
        return true;
    }
    if (glrp->yPos < -1)
    {
        winner = 1;
        return true;
    }
    return false;
}

