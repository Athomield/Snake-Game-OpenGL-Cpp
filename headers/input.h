#ifndef INPUT_H
#define INPUT_H

#include "window.h"

class Input
{
public:
    Input();
    ~Input();
    static bool IsKeyPressed(int _key);
    static bool IsKeyPressedOnce(int _key);
    void CreateInstance();

private:
    //static Input* mInstance = nullptr;


private:
    //static int mLastKey;
    static bool mKeys[1024];
    static bool mKeysOnce[1024];
    static void Key_Callback(GLFWwindow* _window, int _key, int _scancode, int _action, int _mods);
};

#endif // INPUT_H
