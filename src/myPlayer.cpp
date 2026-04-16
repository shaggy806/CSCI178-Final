#include "myPlayer.h"

myPlayer::myPlayer()
{
    //ctor
    xPos = 0.0;
    yPos = 0.0;
    fps = 18.0;
    timer = 0;
}

myPlayer::~myPlayer()
{
    //dtor
}

void myPlayer::playerInit(int xF, int yF, char* fileName)
{
    initQuad(fileName);
    initAnimations();
    animation = 0;
    prevAnim = 0;
    frame = 0;
    xFrames = xF;
    yFrames = yF;

    xMin = 0;
    xMax = 1.0/xF;
    yMin = 0;
    yMax = 1.0/yF;
}


void myPlayer::movePlay()
{
    yPos+=yV;
    xPos+=xV;
    if (yPos <= -1.5){
        yPos = -1.5;
        yV=0.0;
    }
    if (yV != 0.0){
        if (xV>= 0.0){
            animation = 2;
        } else{
        animation = 3;
        }
    } else{
        if (xV>= 0.003){
            animation = 0;
        }
        else if (xV <=-0.003){
        animation = 1;
        }
        else if (xV >0.001){
            animation=4;
        }
        else if (xV <-0.001){
            animation=5;
        }
    }
    if (yPos == -1.5 && animation == 2){
        animation = 4;
    }
    if (yPos == -1.5 && animation == 3){
        animation = 5;
    }
    if (animation != prevAnim) frame = 0;
    prevAnim = animation;
    pos.x=xPos;
    pos.y=yPos;
    pos.z= -7;
}
void myPlayer::displayPlayer()
{
    if (timer >= (1.0/fps)){
        timer = 0;
        frame++;
    }
    frame = frame % (animations[animation].size());
    int x = animations[animation][frame] % xFrames;
    int y = animations[animation][frame] / xFrames;
    float frameWidth = 1.0/xFrames;
    float frameHeight = 1.0/yFrames;

    xMin = frameWidth*x;
    xMax = frameWidth*(x+1);
    yMin = frameHeight*y;
    yMax = frameHeight*(y+1);
    updateQuad();
    drawQuad();
}
void myPlayer::initAnimations()
{

    animations.push_back({0,1,2,3,4,5});
    animations.push_back({8,9,10,11,12,13});
    animations.push_back({6});
    animations.push_back({7});
    animations.push_back({5});
    animations.push_back({8});
}

