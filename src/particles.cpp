#include "particles.h"

particles::particles()
{
    //ctor
}

particles::~particles()
{
    //dtor
}
void particles::load()
{
    image->initQuad("images/particle.png");
    parts.clear();
}

void particles::reload()
{
    image->initQuad("images/particle.png");
}

void particles::updateParticles(float dt)
{
    for (int i = 0; i < parts.size(); i++){
        parts[i].x += parts[i].xV*dt;
        parts[i].y += parts[i].yV*dt;
        parts[i].yV -= 1*dt;
        parts[i].livedTime += dt;
        if (parts[i].livedTime > parts[i].lifetime){
            parts.erase(parts.begin()+i);
            i--;
        }
    }
}

void particles::drawParticles()
{
    for (int i = 0; i < parts.size(); i++){
        image->pos.z = -9;
        image->pos.x =  parts[i].x * scale.x;
        image->pos.y =  parts[i].y * scale.y;

        image->scale.x = parts[i].scale * scale.x;
        image->scale.y = parts[i].scale * scale.x;
        image->rot.z = parts[i].rotation;

        image->drawQuad(parts[i].r,parts[i].g,parts[i].b,(parts[i].lifetime-parts[i].livedTime)/parts[i].lifetime);
    }
}

void particles::addParticle(float x, float y, float xV, float yV, float rot, float scl, float lifetime, float r, float g, float b)
{
    particle newPart;
    newPart.x = x;
    newPart.y = y;
    newPart.xV = xV;
    newPart.yV = yV;
    newPart.rotation = rot;
    newPart.scale = scl;
    newPart.lifetime = lifetime;
    newPart.livedTime = 0;
    newPart.r = r;
    newPart.g = g;
    newPart.b = b;
    parts.push_back(newPart);
}

