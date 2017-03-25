#ifndef QUAD_H
#define QUAD_H

#include "window.h"

class Quad
{
    public:
        Quad(int _x, int _y);
        virtual ~Quad();

        void Render();
        void Translate(int _x,int _y);
        void SetPosition(int _x,int _y);
        int GetXPos();
        int GetYPos();

        void SetColor(glm::vec3 _color);

    private:
        void CheckShader(GLuint _shader);
        void CheckProgramShader(GLuint _progShader);

    private:
        GLuint mVBO = NULL;
        GLuint mVAO = NULL;
        GLuint mEBO = NULL;
        GLuint mVertexShader = NULL;
        GLuint mFragmentShader = NULL;
        GLuint mShaderProgram = NULL;

        int mX,mY;

};

#endif // QUAD_H
