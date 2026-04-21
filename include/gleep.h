#ifndef GLEEP_H
#define GLEEP_H
#include<_common.h>
#include<_quad.h>

class gleep
{
    public:
        gleep();
        virtual ~gleep();
        float xPos;
        float yPos;
        float width;
        float height;
        float xV;
        float yV;
        int xFrames,yFrames;
        int animation;
        int prevAnim;
        int frame;
        float fps;
        float timer;
        float attackCooldown;
        vector<vector<int>> animations;


        _quad *sprite = new _quad();

        void init();
        void initAnimations();
        void updatePlayer(float dt);
        void displayPlayer();

    protected:

    private:
};

#endif // GLEEP_H
