#ifndef _SCENE_H
#define _SCENE_H

#include<_common.h>
#include<_lightSettings.h>
#include<_model.h>
#include<_inputs.h>
#include<_modelVBO.h>
#include<_parallax.h>
#include<_quad.h>
#include<_player.h>
#include<_sounds.h>
#include<myPlayer.h>
#include<firstShader.h>

class _scene
{
    public:


        _scene();
        virtual ~_scene();

        GLint initGL(); // Initialize the openGL contents
        void reSize(GLint, GLint); // To handle resize window
        void drawScene(); // Render the final scene

        int winMsg(HWND	hWnd,			// Handle For This Window
                   UINT	uMsg,			// Message For This Window
                   WPARAM wParam,		// Additional Message Information
                   LPARAM lParam);		// Additional Message Information;

        static float deltaTime;

        _sounds *sound = new _sounds();
        _lightSettings *myLight = new _lightSettings();
        _inputs *myKbMs = new _inputs();
        _model *myModel = new _model();
        _model *tea1 = new _model();
        _model *tea2 = new _model();
        _modelVBO *myModelVBO = new _modelVBO();
        _parallax *myParallax = new _parallax();
        _quad *myQuad = new _quad();
        _player *player = new _player();
        myPlayer *myPlay = new myPlayer();
        vec2 dim;

        firstShader *sh = new firstShader();
    protected:

    private:
};

#endif // _SCENE_H
