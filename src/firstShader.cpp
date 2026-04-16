#include "firstShader.h"

firstShader::firstShader()
{
    //ctor
}

firstShader::~firstShader()
{
    cleanUp();
}
void firstShader::loadFile(char* fileName, string& str)
{
    char tmp[1024];
    ifstream in(fileName);

    if (!in.is_open()){
        cout << "Error file cannot be opened" << endl;
        return;

    }

    while (in.getline(tmp,1024)){
        str += tmp;
        str += '\n';
    }
    str += '\n';
    cout << str << endl; // DEBUG ONLY
    in.close();
}

unsigned int firstShader::loadShader(string& src, unsigned int mode)
{
    unsigned int id; // id for shader program

    const char* cSource; // to convert string to char array
    char error[1024];

    id = glCreateShader(mode);
    cSource = src.c_str();

    glShaderSource(id,1,&cSource,NULL);
    glCompileShader(id);

    glGetShaderInfoLog(id,1024,NULL,error); // output for shader errors

    cout << "Compile Status:" << error<< endl;

    return id;

}

void firstShader::initShader(char* vFileName, char* fFileName)
{
    string source;

    loadFile(vFileName,source);

    vs = loadShader(source,GL_VERTEX_SHADER);

    source = "";

    loadFile(fFileName,source);
    fs = loadShader(source,GL_FRAGMENT_SHADER);

    source = "";

    program = glCreateProgram();
    glAttachShader(program,vs);
    glAttachShader(program,fs);

    glLinkProgram(program);
}

void firstShader::cleanUp()
{
    glDetachShader(program,vs);
    glDetachShader(program,fs);
    glDeleteShader(vs);
    glDeleteShader(fs);
    glDeleteProgram(program);
}

