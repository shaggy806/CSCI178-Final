#ifndef _TEXTURELOADER_H
#define _TEXTURELOADER_H

#include<_common.h>
#include<SOIL.h>

class _textureLoader
{
    public:
        _textureLoader();
        virtual ~_textureLoader();

        int width,height;
        unsigned char *image;
        GLuint tex;

        void loadTexture(char* fileName);
        void bindTexture();

    protected:

    private:
};

#endif // _TEXTURELOADER_H
