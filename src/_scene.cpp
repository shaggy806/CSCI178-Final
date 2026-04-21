#include "_scene.h"

auto lastTime = chrono::steady_clock::now();
_scene::_scene()
{
    //ctor
}

_scene::~_scene()
{
    //dtor
    delete myLight;
}

GLint _scene::initGL()
{
    glewInit();
    glClearColor(0.0,0.0,0.0,1.0);  // Background color
    glClearDepth(1.0);              // Depth test value
    glEnable(GL_DEPTH_TEST);        // Enable depth test
    glDepthFunc(GL_LEQUAL);         // True for less or equal

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    //glEnable(GL_COLOR_MATERIAL);

    myLight->setLight(GL_LIGHT0);
    myParallax->initPrlx("images/huh2.png");
    //sound->playSounds("sounds/FIREBIRD.mp3");
    myPlay->playerInit(7,2,"images/glorp.png");
    sh->initShader("shaders/v.vs","shaders/f.fs");
    square->initQuad("images/BlockPlatformUltraWide.png");
    glUseProgram(sh->program);
    glUseProgram(0);


    manager->initialize();
    setWorldEdges(manager);
    manager->buttonScale = getScale(-5);
    manager->gameLevel->worldScale = manager->worldScale;
    manager->gameLevel->levelScale = getScale(-8);
    return true;
}


float _scene::deltaTime=0;

void _scene::reSize(GLint width, GLint height)
{
    if (height == 0) height = 1;

    dim.x = width;   // actual window width
    dim.y = height;  // actual window height

    GLfloat aspectRatio = (GLfloat)width / (GLfloat)height;
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, aspectRatio, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    setWorldEdges(manager);
    manager->buttonScale = getScale(-5);

    manager->gameLevel->worldScale = manager->worldScale;
    manager->gameLevel->levelScale = getScale(-8);
}

void _scene::drawScene()
{
    auto currentTime = chrono::steady_clock::now();
    chrono::duration<float> elapsed = currentTime - lastTime;
    deltaTime = elapsed.count();
    lastTime = currentTime;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


    float wx, wy, wz;
    mouseToWorldOnPlane(mouseX, mouseY, -5.0f, wx, wy, wz);



    manager->mousePos.x = wx;
    manager->mousePos.y = wy;

    manager->gameLevel->dt = deltaTime;
    manager->update();
    manager->drawWorld(0,0);
}

bool _scene::mouseToWorldOnPlane(int mx, int my, float planeZ,
                                 float& outX, float& outY, float& outZ)
{
    GLdouble model[16];
    GLdouble proj[16];
    GLint viewport[4];

    GLdouble nearX, nearY, nearZ;
    GLdouble farX,  farY,  farZ;

    glGetDoublev(GL_MODELVIEW_MATRIX, model);
    glGetDoublev(GL_PROJECTION_MATRIX, proj);
    glGetIntegerv(GL_VIEWPORT, viewport);

    const GLdouble winX = (GLdouble)mx;
    const GLdouble winY = (GLdouble)(viewport[3] - my - 1);

    if (gluUnProject(winX, winY, 0.0, model, proj, viewport,
                     &nearX, &nearY, &nearZ) == GL_FALSE)
        return false;

    if (gluUnProject(winX, winY, 1.0, model, proj, viewport,
                     &farX, &farY, &farZ) == GL_FALSE)
        return false;

    const GLdouble denom = farZ - nearZ;
    if (fabs(denom) < 1e-8)
        return false;

    const GLdouble t = (planeZ - nearZ) / denom;

    outX = (float)(nearX + t * (farX - nearX));
    outY = (float)(nearY + t * (farY - nearY));
    outZ = planeZ;
    return true;
}

/*
    bool isWPressed = GetAsyncKeyState('W') & 0x8000;
    bool isAPressed = GetAsyncKeyState('A') & 0x8000;
    bool isSPressed = GetAsyncKeyState('S') & 0x8000;
    bool isDPressed = GetAsyncKeyState('D') & 0x8000;

    bool isUpPressed = GetAsyncKeyState(VK_UP) & 0x8000;
    bool isDownPressed = GetAsyncKeyState(VK_DOWN) & 0x8000;
    bool isLeftPressed = GetAsyncKeyState(VK_LEFT) & 0x8000;
    bool isRightPressed = GetAsyncKeyState(VK_RIGHT) & 0x8000;
    */

int _scene::winMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

}

void _scene::setWorldEdges(_gameManager *managerToUpdate)
{
    float minX,maxX,minY,maxY,Z;
    mouseToWorldOnPlane(0,0,-30,minX,maxY,Z);
    mouseToWorldOnPlane(dim.x,dim.y,-30,maxX,minY,Z);

    managerToUpdate->worldScale.x = maxX-minX;
    managerToUpdate->worldScale.y = maxY-minY;

}
vec2 _scene::getScale(float zPlane)
{
    float minX,maxX,minY,maxY,Z;
    mouseToWorldOnPlane(0,0,zPlane,minX,maxY,Z);
    mouseToWorldOnPlane(dim.x,dim.y,zPlane,maxX,minY,Z);

    vec2 retVal;
    retVal.x = maxX-minX;
    retVal.y = maxY-minY;

    return retVal;
}


/* Movement Code
    if (isWPressed){
        }
    if (isSPressed){
        }
    if (isAPressed){
        }
    if (isDPressed){
        }

    if (isUpPressed){
        if (myPlay->yPos <-1.4){
            myPlay->yV = 0.03;
        }
    }
    if (isDownPressed){
        }
    if (isLeftPressed){
        myPlay->xV-=0.07*deltaTime;
    }
    if (isRightPressed){
        myPlay->xV+=0.07*deltaTime;
    }

    myPlay->timer += deltaTime;
    myPlay->yV-=0.1*deltaTime;
    myPlay->xV*=(0.99);
    myPlay->movePlay();
    myPlay->displayPlayer();
*/
