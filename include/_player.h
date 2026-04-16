#ifndef _PLAYER_H
#define _PLAYER_H
#include<_common.h>
#include<_quad.h>


class _player:public _quad
{
    public:
        _player();
        virtual ~_player();

        int xFrames,yFrames;
        int actionTrigger;
        int animation;
        int frame;
        vector<vector<int>> animations;
        enum{STAND,LEFT_WALK,RIGHT_WALK,RUN,ATTACK,JUMP};
        void playerInit(int, int,char*);
        void initAnimations();
        void playerActions();
        void updatePlayer();
    protected:

    private:
};

#endif // _PLAYER_H
