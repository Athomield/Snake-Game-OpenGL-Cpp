#include "headers/input.h"

bool Input::mKeys[1024];
bool Input::mKeysOnce[1024];
//Input* Input::mInstance;

Input::Input()
{

}

Input::~Input()
{
    //delete mInstance;
}

void Input::CreateInstance()
{
    //mInstance = new Input();
    glfwSetKeyCallback(Window::GetWindow()->GetGLFWWindow(), Key_Callback);
}

bool Input::IsKeyPressedOnce(int _key)
{
    if(mKeysOnce[_key])
    {
        bool retVal = mKeysOnce[_key];
        mKeysOnce[_key] = false;
        return retVal;
    }
    else return false;
}

bool Input::IsKeyPressed(int _key)
{
    return mKeys[_key];
}

void Input::Key_Callback(GLFWwindow* _window, int _key, int _scancode, int _action, int _mods)
{
    if(_action == GLFW_PRESS)
    {
        mKeys[_key] = true;
        mKeysOnce[_key] = true;
    }
    else if(_action == GLFW_RELEASE)
    {
        mKeys[_key] = false;
    }
}
