#include "_model.h"

_model::_model()
{
    //ctor
}

_model::~_model()
{
    //dtor
}

void _model::initModel(char *fileName)
{
    rotation.x = rotation.y = rotation.z = 0;
    pos.x = pos.y = 0;
    pos.z = -8;
    scale.x = scale.y = scale.z = 1;
    myTex->loadTexture(fileName);

}

void _model::drawModel()
{
    glPushMatrix();

    myTex->bindTexture();
    glColor3f(1.0,0.0,0.0);             // Set base color
    glTranslatef(pos.x,pos.y,pos.z);    // Places the object

    glRotatef(rotation.x, 1,0,0);       // Set the rotation on the X axis
    glRotatef(rotation.y, 0,1,0);       // Set the rotation on the Y axis
    glRotatef(rotation.z, 0,0,1);       // Set the rotation on the Z axis

    glScalef(scale.x,scale.y,scale.z);  // Set the scale

    glutSolidTeapot(1.5);

    glPopMatrix();


}
