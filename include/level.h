#ifndef LEVEL_H
#define LEVEL_H
#include<_common.h>
#include<_quad.h>
#include<glorp.h>
#include<gleep.h>
#include<_parallax.h>
#include<_sounds.h>
#include<particles.h>
#include<random>

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
        int currentLevelID =  -1;
        bool loaded = false;

        vector<block> blocks;
        vector<_quad> sprites;

        gleep *glp = new gleep();
        glorp *glrp = new glorp();

        float gleepSmoke = 0;
        float glorpDash = 0;
        float glorpSmoke = 0;


        std::random_device rd;
        std::mt19937 gen{rd()};
        std::uniform_real_distribution<float> dis{0.0f, 1.0f};
        int winner = -1;

        particles *particleSystem = new particles();

        _parallax *background = new _parallax();

        _sounds *soundEngine = new _sounds();

        void loadSprites();
        void loadLevel(int);
        void updateLevel();
        void drawLevel();
        void reloadGLResources();

        void addBlock(float,float,float,float,int,bool);

        bool gleepCollide();
        bool glorpCollide();

        bool playersCollide();

        bool checkWinner();
        int gleepStepTimer = 0;
        int glorpStepTimer = 0;

        float ran();

    protected:

    private:
};

#endif // LEVEL_H
