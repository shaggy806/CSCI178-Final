#ifndef FIRSTSHADER_H
#define FIRSTSHADER_H
#include<_common.h>


class firstShader
{
    public:
        firstShader();
        virtual ~firstShader();

        void loadFile(char*, string&);
        unsigned int loadShader(string&, unsigned int);
        void initShader(char*, char*);
        void cleanUp(); //clean shaders

        unsigned vs,fs,program; //handlers

    protected:

    private:
};

#endif // FIRSTSHADER_H
