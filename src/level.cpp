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
    sprites[0].initQuad("images/download.jpg");
}

void level::loadLevel(int levelID)
{
    glp->init();
    glp->yPos = 0.3;
    glp->xPos = 0.3;
    glrp->init();
    glrp->yPos = 0.3;
    glrp->xPos = -0.3;
    loadSprites();
    switch (levelID)
    {
    case 0:
        background->initPrlx("images/MoonBG.png");
        addBlock(0,-0.5,0.5,0.1,0, false);
        break;
    case 1:
        background->initPrlx("images/MoonBG.png");
        addBlock(0,-0.5,0.5,0.1,0,false);
        addBlock(-0.25,-0.15,0.13,0.03,0,true);
        addBlock(0.25,-0.15,0.13,0.03,0,true);
        addBlock(0,0.1,0.13,0.03,0,true);

        break;
    default:
        background->initPrlx("images/MoonBG.png");
        addBlock(0,-0.5,0.5,0.1,0,false);
        addBlock(0,-0.5,0.5,0.1,0,true);
        addBlock(0,-0.5,0.5,0.1,0,true);
        break;
    }

}
void level::updateLevel()
{
    bool isWPressed = GetAsyncKeyState('W') & 0x8000;
    bool isAPressed = GetAsyncKeyState('A') & 0x8000;
    bool isSPressed = GetAsyncKeyState('S') & 0x8000;
    bool isDPressed = GetAsyncKeyState('D') & 0x8000;

    bool isUpPressed = GetAsyncKeyState(VK_UP) & 0x8000;
    bool isDownPressed = GetAsyncKeyState(VK_DOWN) & 0x8000;
    bool isLeftPressed = GetAsyncKeyState(VK_LEFT) & 0x8000;
    bool isRightPressed = GetAsyncKeyState(VK_RIGHT) & 0x8000;

    glp->xPos+=glp->xV*dt;
    if (gleepCollide())
    {
        glp->xPos-=glp->xV*dt;
        glp->xV =0;
    }
    float accel = 1.3f;
    float decel = 1.8f;

    if (isLeftPressed)
    {
        glp->xV -= accel * dt;
    }
    else if (isRightPressed)
    {
        glp->xV += accel * dt;
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

    float maxSpeed = 1.0f;

    if (glp->xV > maxSpeed) glp->xV = maxSpeed;
    if (glp->xV < -maxSpeed) glp->xV = -maxSpeed;


    glp->yPos+=glp->yV*dt;
    if (gleepCollide() && glp->yV <0 && isUpPressed)
    {
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
        glrp->xV -= accel * dt;
    }
    else if (isDPressed)
    {
        glrp->xV += accel * dt;
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


    if (glrp->xV > maxSpeed) glrp->xV = maxSpeed;
    if (glrp->xV < -maxSpeed) glrp->xV = -maxSpeed;

    glrp->yPos += glrp->yV * dt;
    if (glorpCollide() && glrp->yV < 0 && isWPressed)
    {
        glrp->yPos -= glrp->yV * dt;
        glrp->yV = 1;
    }
    else if (glorpCollide())
    {
        glrp->yPos -= glrp->yV * dt;
        glrp->yV = 0;
    }
    glrp->yV -= 1.5 * dt;

    glp->attackCooldown+=dt;
    glrp->attackCooldown+=dt;

    if (playersCollide()){
        if (isSPressed && glrp->attackCooldown>1){
            glp->xV = glrp->xV*20;
            glp->yV = 0.6;
            glrp->attackCooldown = 0;
        }
        if (isDownPressed && glp->attackCooldown>1){
            glrp->xV = glp->xV*20;
            glrp->yV = 0.6;
            glp->attackCooldown = 0;
        }
    }

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


void level::drawLevel()
{
    background->drawBackground(worldScale.x,worldScale.y);


    for (int i = 0; i < blocks.size(); i++)
    {
        if (blocks[i].visible){
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

