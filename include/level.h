#ifndef LEVEL_H
#define LEVEL_H
#include<_common.h>
#include<_quad.h>
#include<glorp.h>
#include<gleep.h>
#include<_parallax.h>
#include<_sounds.h>

struct block {
    float x;
    float y;
    float scaleX;
    float scaleY;
    int sprite;
    bool visible;
};

class level
{
    public:
        level();
        virtual ~level();

        vec2 worldScale;
        vec2 levelScale;
        vec2 mousePos;
        float dt;

        vector<block> blocks;
        vector<_quad> sprites;

        gleep *glp = new gleep();
        glorp *glrp = new glorp();

        int winner = -1;


        _parallax *background = new _parallax();

        _sounds *soundEngine = new _sounds();

        void loadSprites();
        void loadLevel(int);
        void updateLevel();
        void drawLevel();

        void addBlock(float,float,float,float,int,bool);

        bool gleepCollide();
        bool glorpCollide();

        bool playersCollide();

        bool checkWinner();
        int gleepStepTimer = 0;
        int glorpStepTimer = 0;

    protected:

    private:
};

#endif // LEVEL_H
