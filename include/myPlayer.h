#ifndef MYPLAYER_H
#define MYPLAYER_H
#include<_common.h>
#include<_quad.h>


class myPlayer:public _quad
{
    public:

        int xFrames,yFrames;
        int actionTrigger;
        int animation;
        int prevAnim;
        int frame;
        float fps;
        float timer;

        float xV,yV;
        float xPos,yPos;
        vector<vector<int>> animations;
        void playerInit(int xF, int yF, char* fileName);
        void movePlay();
        void initAnimations();
        void displayPlayer();
        myPlayer();
        virtual ~myPlayer();

    protected:

    private:
};

#endif // MYPLAYER_H
