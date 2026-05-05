#include "gleep.h"

gleep::gleep()
{
    xPos = yPos = xV = yV = 0;
    width = 0.03;
    height = 0.05;
    xFrames = 12;
    yFrames = 3;
    animation = 0;
    prevAnim = frame = 0;
    fps = 30;
}

gleep::~gleep()
{
    //dtor
}


void gleep::init()
{
    sprite->initQuad("images/GleepNew.png");

    initAnimations();

}
void gleep::initAnimations()
{
    animations.clear();
    animations.push_back({0,1,2,3,4,5,6,7,8,9,10,11});
    animations.push_back({12,13,14,15,16,17,18,19,20,21,22,23});
    animations.push_back({3});
    animations.push_back({20});
    animations.push_back({0});
    animations.push_back({23});
    animations.push_back({25});
    animations.push_back({24});
}

void gleep::updatePlayer(float dt)
{
    timer += dt;

    prevAnim = animation;

    if (isKicking)
    {
        if (animation % 2 == 1 || animation == 7) animation = 7;
        else if (animation % 2 == 0 || animation == 6) animation = 6;
    }

    bool onGround = fabs(yV) < 0.1f;
    bool movingX = fabs(xV) > 0.02f;

    if (onGround)
    {
        if (movingX)
        {
            if (xV > 0)
                animation = 0;
            else
                animation = 1;
        }
        else
        {
            if (animation == 0 || animation == 2) animation = 4;
            else if (animation == 1 || animation == 3) animation = 5;
        }
    }
    else
    {
        if (movingX)
        {
            if (xV > 0)
                animation = 2;
            else
                animation = 3;
        }
        else
        {
            if (animation == 0 || animation == 4) animation = 2;
            else if (animation == 1 || animation == 5) animation = 3;
        }
    }

    if (animation != prevAnim)
    {
        frame = 0;
        timer = 0;
    }
}

void gleep::displayPlayer()
{
    if (timer >= (1.0/fps))
    {
        timer = 0;
        frame++;
    }
    frame = frame % (animations[animation].size());
    int x = animations[animation][frame] % xFrames;
    int y = animations[animation][frame] / xFrames;
    float frameWidth = 1.0/xFrames;
    float frameHeight = 1.0/yFrames;

    sprite->xMin = frameWidth*x;
    sprite->xMax = frameWidth*(x+1);
    sprite->yMin = frameHeight*y;
    sprite->yMax = frameHeight*(y+1);
    sprite->updateQuad();
    sprite->drawQuad();
}
