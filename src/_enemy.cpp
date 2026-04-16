#include "_enemy.h"

_enemy::_enemy()
{
    //ctor
}

_enemy::~_enemy()
{
    //dtor
}
void _enemy::enemyInit(int xF, int yF, char* fileName)
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

void _enemy::initAnimations()
{
    animations.push_back({0,1,2,3,4,5});
}

void _enemy::enemyActions()
{

}

void _enemy::updateEnemy()
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

void _enemy::placeEnemy(vec3)
{

}
