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
    delete myKbMs;
    delete myModel;
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
    myModel->initModel("images/download.jpg");
    tea1->initModel("images/download.jpg");
    tea2->initModel("images/image.jpg");
    tea1->pos.x -=2;
    tea2->pos.x +=2;

    //myModelVBO->modelInit("images/huh.png");

    myQuad->initQuad("images/huh.png");
    player->playerInit(12,4,"images/glimp.png");
    myParallax->initPrlx("images/huh2.png");
    sound->playSounds("sounds/FIREBIRD.mp3");
    myPlay->playerInit(7,2,"images/glorp.png");
    sh->initShader("shaders/v.vs","shaders/f.fs");
    return true;
}

void _scene::reSize(GLint width, GLint height)
{
    GLfloat aspectRatio = (GLfloat)width/(GLfloat)height;
    glViewport(0,0,width,height);                           // Setting the viewport

    glMatrixMode(GL_PROJECTION);                            // Initiate the proction
    glLoadIdentity();                                       // Initialize the matrix with identity matrix
    gluPerspective(45.0,aspectRatio,0.1,100.0);             // Setup perspective projection

    glMatrixMode(GL_MODELVIEW);                             // Initiate model & view matrix
    glLoadIdentity();

    dim.x = GetSystemMetrics(SM_CXSCREEN);
    dim.y = GetSystemMetrics(SM_CYSCREEN);
}

float _scene::deltaTime=0;

void _scene::drawScene()
{

    auto currentTime = chrono::steady_clock::now();
    chrono::duration<float> elapsed = currentTime - lastTime;
    deltaTime = elapsed.count();
    lastTime = currentTime;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear buffers

    glLoadIdentity();
    glColor3f(0.0,1.0,1.0); // Set color for my model

    myParallax->drawBackground(dim.x,dim.y);
    myParallax->scroll(true,myParallax->LEFT,0.05*deltaTime);

    //tea1->drawModel();
    //tea2->drawModel();
    bool isWPressed = GetAsyncKeyState('W') & 0x8000;
    bool isAPressed = GetAsyncKeyState('A') & 0x8000;
    bool isSPressed = GetAsyncKeyState('S') & 0x8000;
    bool isDPressed = GetAsyncKeyState('D') & 0x8000;

    bool isUpPressed = GetAsyncKeyState(VK_UP) & 0x8000;
    bool isDownPressed = GetAsyncKeyState(VK_DOWN) & 0x8000;
    bool isLeftPressed = GetAsyncKeyState(VK_LEFT) & 0x8000;
    bool isRightPressed = GetAsyncKeyState(VK_RIGHT) & 0x8000;

    if (isWPressed){
        tea1->rotation.x-=0.05;
    }
    if (isSPressed){
        tea1->rotation.x+=0.05;
    }
    if (isAPressed){
        tea1->rotation.y-=0.05;
    }
    if (isDPressed){
        tea1->rotation.y+=0.05;
    }

    if (isUpPressed){
        if (myPlay->yPos <-1.4){
            myPlay->yV = 0.03;
        }
    }
    if (isDownPressed){
        tea2->rotation.x+=0.05;
    }
    if (isLeftPressed){
        myPlay->xV-=0.07*deltaTime;
    }
    if (isRightPressed){
        myPlay->xV+=0.07*deltaTime;
        player->frame=(player->frame + 1) % player->animations[player->animation].size();
    }
    myPlay->timer += deltaTime;
    myPlay->yV-=0.1*deltaTime;
    myPlay->xV*=(0.99);
    myPlay->movePlay();
    myPlay->displayPlayer();

    //player->updatePlayer();
    //player->updateQuad();
    //player->drawQuad();

    //myModelVBO->drawmodel();
}

int _scene::winMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg) {
    case WM_KEYDOWN:
        myKbMs->wParam = wParam;
        myKbMs->keyPressed(myModel);
        break;
    case WM_KEYUP:
        break;

    case WM_LBUTTONDOWN:
    case WM_RBUTTONDOWN:
    case WM_MBUTTONDOWN:
        myKbMs->wParam = wParam;
        myKbMs->mouseEventDown(myModel,LOWORD(lParam),HIWORD(lParam));
        myKbMs->mouseEventDown(myModelVBO,LOWORD(lParam),HIWORD(lParam));
        break;
    case WM_LBUTTONUP:
    case WM_RBUTTONUP:
    case WM_MBUTTONUP:
        myKbMs->wParam = wParam;
        myKbMs->mouseEventUp(myModel);
        myKbMs->mouseEventUp(myModelVBO);
        break;

    case WM_MOUSEMOVE:
        myKbMs->wParam = wParam;
        myKbMs->mouseMove(myModel,LOWORD(lParam),HIWORD(lParam));
        myKbMs->mouseMove(myModelVBO,LOWORD(lParam),HIWORD(lParam));

        break;
    case WM_MOUSEWHEEL:
        myKbMs->wParam = wParam;
        myKbMs->mouseWheel(myModel,(double)GET_WHEEL_DELTA_WPARAM(wParam));
        myKbMs->mouseWheel(myModelVBO,(double)GET_WHEEL_DELTA_WPARAM(wParam));

        break;
    }
}
