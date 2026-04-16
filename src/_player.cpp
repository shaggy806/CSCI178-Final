#include "_player.h"

_player::_player()
{
    //ctor



}

_player::~_player()
{
    //dtor
}

void _player::playerInit(int xF, int yF, char* fileName)
{
    initQuad(fileName);
    initAnimations();
    animation = 0;
    frame = 0;
    xFrames = xF;
    yFrames = yF;
    xMin = 0;
    xMax = 1.0/xFrames;
    yMin = 0;
    yMax = 1.0/yFrames;
}

void _player::playerActions()
{

}

void _player::updatePlayer()
{

    int x = animations[animation][frame] % xFrames;
    int y = animations[animation][frame] / xFrames;
    float frameWidth = 1.0/xFrames;
    float frameHeight = 1.0/yFrames;

    xMin = frameWidth*x;
    xMax = frameWidth*(x+1);
    yMin = frameHeight*y;
    yMax = frameHeight*(y+1);


}


void _player::initAnimations()
{
    animations.push_back({0,3,4,5,6,7,8,9,10,11});
}

