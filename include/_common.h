#ifndef _COMMON_H
#define _COMMON_H

#include<GL/glew.h>
#include<windows.h>
#include <stdlib.h>
#include<iostream>
#include<GL/gl.h>
#include<GL/glut.h>
#include<time.h>
#include<cmath>
#include<chrono>
#include<vector>
#include<fstream>

#define PI 3.14159
#define GLEW_STATIC

using namespace std;

typedef struct{
    float x;
    float y;
    float z;
}vec3;

typedef struct{
    float x;
    float y;
}vec2;



#endif // _COMMON_H
