#include "_inputs.h"

_inputs::_inputs()
{
    //ctor
    isRotate = false;
    isTranslate = false;
}

_inputs::~_inputs()
{
    //dtor
}
void _inputs::keyPressed(_model *mdl)
{
    switch(wParam)
    {
        case VK_LEFT:
            mdl->rotation.y += 1.0;
            break;
        case VK_RIGHT:
            mdl->rotation.y -= 1.0;
            break;
        case VK_UP:
            mdl->rotation.x += 1.0;
            break;
        case VK_DOWN:
            mdl->rotation.x -= 1.0;
            break;
    }
}

void _inputs::keyUp()
{
    switch(wParam)
    {

        default: break;
    }
}

void _inputs::mouseEventDown(_model *mdl, double x, double y)
{
    prevMx = x;
    prevMy = y;

    switch(wParam)
    {
        case MK_LBUTTON:
            isRotate = true;
            break;
        case MK_RBUTTON:
            isTranslate = true;
            break;
        case MK_MBUTTON: break;
        default: break;
    }
}

void _inputs::mouseEventUp(_model *mdl)
{
    isRotate = false;
    isTranslate = false;
}

void _inputs::mouseMove(_model *mdl, double x, double y)
{
    if(isRotate)
    {
        mdl->rotation.y += (x-prevMx)/3.0;
        mdl->rotation.x += (y-prevMy)/3.0;
    }

    if(isTranslate)
    {
        mdl->pos.x += (x-prevMx)/100.0;
        mdl->pos.y -= (y-prevMy)/100.0;
    }


}

void _inputs::mouseWheel(_model *mdl, double delta)
{
    mdl->pos.z += delta/100;
}


void _inputs::keyPressed(_modelVBO* mdlv)
{

    switch(wParam)

    {
        case 65:
            mdlv->rot.y -= 1.0;
            break;
        case 68:
            mdlv->rot.y += 1.0;
            break;
        case 87:
            mdlv->rot.x -= 1.0;
            break;
        case 83:
            mdlv->rot.x += 1.0;
            break;
    }
}
void _inputs::keyPressed(_player* player)
{
    switch(wParam)
    {
        case VK_LEFT:
            break;
        case VK_RIGHT:
            player->frame=(player->frame + 1) % player->animations[player->animation].size();
            break;
        case VK_UP:
            break;
        case VK_DOWN:
            break;
    }
}

void _inputs::mouseEventDown(_modelVBO* mdlv, double x, double y)
{
    prevMx = x;
    prevMy = y;

    switch(wParam)
    {
        case MK_LBUTTON:
            isRotate = true;
            break;
        case MK_RBUTTON:
            isTranslate = true;
            break;
        case MK_MBUTTON: break;
        default: break;
    }
}

void _inputs::mouseEventUp(_modelVBO* mdlv)
{
 isRotate = false;
    isTranslate = false;
}

void _inputs::mouseMove(_modelVBO* mdlv, double x, double y)
{
if(isRotate)
    {
        mdlv->rot.y += (x-prevMx)/3.0;
        mdlv->rot.x += (y-prevMy)/3.0;
    }

    if(isTranslate)
    {
        mdlv->pos.x += (x-prevMx)/100.0;
        mdlv->pos.y -= (y-prevMy)/100.0;
    }

    prevMx = x;
    prevMy = y;
}

void _inputs::mouseWheel(_modelVBO* mdlv, double delta)
{
     mdlv->pos.z += delta/100;
}
