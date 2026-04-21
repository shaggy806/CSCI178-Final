#include "glorp.h"

glorp::glorp()
{

    xPos = yPos =xV=yV=0;
    width=0.03;
    height=0.05;
    xFrames=7;
    yFrames=2;
    animation=0;
    prevAnim=frame=0;
    fps=30;
}

glorp::~glorp()
{
    //dtor
}
void glorp::init()
{

    sprite->initQuad("images/cleanGlorp.png");

    initAnimations();
}
void glorp::initAnimations()
{
    animations.push_back({0,1,2,3,4,5});
    animations.push_back({8,9,10,11,12,13});
    animations.push_back({6});
    animations.push_back({7});
    animations.push_back({5});
    animations.push_back({8});
}

void glorp::updatePlayer(float dt)
{
    timer += dt;

    prevAnim = animation;

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
        }else
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
void glorp::displayPlayer()
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
