#ifndef LEVEL_H
#define LEVEL_H
#include<_common.h>
#include<_quad.h>

struct block {
    float x;
    float y;
    float scaleX;
    float scaleY;
    int sprite;
};

class level
{
    public:
        level();
        virtual ~level();

        vector<block> blocks;
        vector<_quad> sprites;

        void loadSprites();
        void loadLevel(int);
        void drawLevel();

    protected:

    private:
};

#endif // LEVEL_H
