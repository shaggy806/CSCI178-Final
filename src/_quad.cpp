#include "_quad.h"

_quad::_quad()
{
    rot.x = rot.y = rot.z = 0;
    pos.x = pos.y = 0;
    pos.z = -8;
    scale.x = scale.y = scale.z = 1.0;
    brightness = 1;
}

_quad::_quad(int rx, int ry, int rz, int px, int py, int pz, float sx, float sy, float sz, int b)
{
    rot.x = rx;
    rot.y = ry;
    rot.z = rz;
    pos.x = px;
    pos.y = py;
    pos.z = pz;
    scale.x = sx;
    scale.y = sy;
    scale.z = sz;
    brightness = b;
}

_quad::~_quad()
{
    //dtor
}
void _quad::initQuad(char* fileName)
{
    glGenBuffers(1,&vboPos);
    glBindBuffer(GL_ARRAY_BUFFER,vboPos);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_DYNAMIC_DRAW);

    glGenBuffers(1,&vboTex);
    glBindBuffer(GL_ARRAY_BUFFER,vboTex);
    glBufferData(GL_ARRAY_BUFFER,sizeof(texCoord),texCoord,GL_DYNAMIC_DRAW);

    myTex->loadTexture(fileName);
}

void _quad::drawQuad()
{
    glPushMatrix();
    myTex->bindTexture();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glColor3f(brightness,brightness,brightness);             // Set base color


    glTranslatef(pos.x,pos.y,pos.z);    // Places the object

    glRotatef(rot.x, 1,0,0);       // Set the rotation on the X axis
    glRotatef(rot.y, 0,1,0);       // Set the rotation on the Y axis
    glRotatef(rot.z, 0,0,1);       // Set the rotation on the Z axis

    glScalef(scale.x,scale.y,scale.z);  // Set the scale


    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER,vboTex);
    glTexCoordPointer(2,GL_FLOAT,0,(void*)0);


    glBindBuffer(GL_ARRAY_BUFFER,vboPos);
    glVertexPointer(3,GL_FLOAT,0,(void*)0);


    glDrawArrays(GL_QUADS,0,4);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glPopMatrix();

}

void _quad::updateQuad()
{
    float texCoord[8]= {
            xMax,yMin,
            xMax,yMax,
            xMin,yMax,
            xMin,yMin
        };
    glBindBuffer(GL_ARRAY_BUFFER,vboTex);
    glBufferSubData(GL_ARRAY_BUFFER,0,sizeof(texCoord),texCoord);
}
