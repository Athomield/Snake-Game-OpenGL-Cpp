#ifndef COIN_H
#define COIN_H

#include "window.h"

class Coin
{
public:
        Coin(int _x, int _y);
        virtual ~Coin();

        void Render();
        void SetPosition(int _x,int _y);
        int GetXPos();
        int GetYPos();
        void Update(double _deltaTime);
        void Hide();
        void Show();
        bool IsDetectable();

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
        bool mDetectable = true;
        double mShowTimer = 0;
};

#endif // COIN_H
