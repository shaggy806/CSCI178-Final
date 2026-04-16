#ifndef _ENEMY_H
#define _ENEMY_H
#include<_common.h>
#include<_quad.h>

class _enemy : public _quad
{
    public:
        _enemy();
        virtual ~_enemy();

        int xFrames,yFrames;
        int actionTrigger;
        int animation;
        int frame;
        vector<vector<int>> animations;
        enum{STAND,LEFT_WALK,RIGHT_WALK,RUN,ATTACK,JUMP};
        void enemyInit(int, int,char*);
        void initAnimations();
        void enemyActions();
        void updateEnemy();
        void placeEnemy(vec3);
        void drawEnemy();

        bool isAlive = true;

    protected:

    private:
};

#endif // _ENEMY_H
