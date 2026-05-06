#ifndef PARTICLES_H
#define PARTICLES_H
#include<_common.h>
#include<_quad.h>


struct particle{
    float x;
    float y;
    float xV;
    float yV;
    float rotation;
    float scale;
    float livedTime;
    float lifetime;
    float r,g,b;
};

class particles
{
    public:
        particles();
        virtual ~particles();

        _quad *image = new _quad();

        vec2 scale;

        vector<particle> parts;

        void load();
        void reload();
        void updateParticles(float dt);
        void drawParticles();

        void addParticle(float x, float y, float xV, float yV, float rot, float scl, float lifetime, float r, float g, float b);


    protected:

    private:
};

#endif // PARTICLES_H
