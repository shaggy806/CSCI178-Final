#ifndef _SCENE_H
#define _SCENE_H

#include<_common.h>
#include<_lightSettings.h>
#include<_parallax.h>
#include<_quad.h>
#include<_sounds.h>
#include<myPlayer.h>
#include<firstShader.h>
#include<_gameManager.h>

class _scene
{
    public:


        _scene();
        virtual ~_scene();

        GLint initGL(); // Initialize the openGL contents
        void reSize(GLint, GLint); // To handle resize window
        void drawScene(); // Render the final scene
        bool mouseToWorldOnPlane(int,int,float,float&,float&,float&);
        void setWorldEdges(_gameManager*);
        vec2 getScale(float zPlane);

        int winMsg(HWND	hWnd,			// Handle For This Window
                   UINT	uMsg,			// Message For This Window
                   WPARAM wParam,		// Additional Message Information
                   LPARAM lParam);		// Additional Message Information;

        static float deltaTime;

        _sounds *sound = new _sounds();
        _lightSettings *myLight = new _lightSettings();
        _parallax *myParallax = new _parallax();
        myPlayer *myPlay = new myPlayer();
        _gameManager *manager = new _gameManager();
        vec2 dim;
        int mouseX;
        int mouseY;

        _quad *square = new _quad();

        firstShader *sh = new firstShader();
    protected:

    private:
};

#endif // _SCENE_H
