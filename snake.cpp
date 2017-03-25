#include "headers/snake.h"

void Key_Callback(GLFWwindow* _window, int _key, int _scancode, int _action, int _mods);

Snake::Snake()
{
    for(int i = 0; i < 5; i++)
    {
        mQuads.push_back(new Quad(-i,0));
        mLastXPos.push_back(-i);
        mLastYPos.push_back(0);
    }
}

Snake::~Snake()
{
    for(int i = 0; i < mQuads.size(); i++)
    {
        delete mQuads[i];
    }
}

void Snake::Render()
{
    for(int i = 0; i<mQuads.size(); i++)
    {
        mQuads[i]->Render();
         if(!mDead)
        {
            mQuads[i]->SetColor(glm::vec3(1.0f,0.6f,0.3f));
        }
        else mQuads[i]->SetColor(glm::vec3(0.9f,0.1f,0.1f));
    }
}

void Snake::Translate(int _x, int _y)
{
    mQuads[0]->Translate(_x,_y);
    for(int i = 1; i<mQuads.size(); i++)
    {
        mQuads[i]->SetPosition(mLastXPos[i-1],mLastYPos[i-1]);
    }
    for(int i = 0; i<mQuads.size(); i++)
    {
        mLastXPos[i] = mQuads[i]->GetXPos();
        mLastYPos[i] = mQuads[i]->GetYPos();
    }
}

void Snake::Update(double _deltaTime)
{
    //std::cout << "Snake size : " << mQuads.size() << std::endl;
    mTimer += _deltaTime;

    if(mTimer >= 0.2 && !mDead)
    {
        switch(mDir)
        {
        case MOVE_RIGHT:
                Translate(1,0);
            break;
        case MOVE_LEFT:
                Translate(-1,0);
            break;
        case MOVE_UP:
                Translate(0,1);
            break;
        case MOVE_DOWN:
                Translate(0,-1);
            break;
        }

        mTimer = 0;
    }

    if(Input::IsKeyPressedOnce(GLFW_KEY_UP) && mDir != MOVE_DOWN)
    {
        std::cout << "Up key pressed !" << std::endl;
        mDir = MOVE_UP;
    }
    if(Input::IsKeyPressedOnce(GLFW_KEY_DOWN) && mDir != MOVE_UP)
    {
        std::cout << "Down key pressed !" << std::endl;
        mDir = MOVE_DOWN;
    }
    if(Input::IsKeyPressedOnce(GLFW_KEY_RIGHT) && mDir != MOVE_LEFT)
    {
        std::cout << "Right key pressed !" << std::endl;
        mDir = MOVE_RIGHT;
    }
    if(Input::IsKeyPressedOnce(GLFW_KEY_LEFT) && mDir != MOVE_RIGHT)
    {
        std::cout << "Left key pressed !" << std::endl;
        mDir = MOVE_LEFT;
    }


    for(int i = 0; i<mQuads.size(); i++)
    {
        /*bool collisionX = mCoin->GetXPos() - 0.5f >= mQuads[i]->GetXPos() - 0.5f &&
        mQuads[i]->GetXPos() - 0.5f >= mCoin->GetXPos() + 0.5f;

        bool collisionY = mCoin->GetYPos() - 0.5f >= mQuads[i]->GetYPos() + 0.5f &&
        mQuads[i]->GetYPos() - 0.5f >= mCoin->GetYPos() + 0.5f;
*/      if(mCoin->IsDetectable())
        {
            bool collisionX = mQuads[i]->GetXPos() - 0.5f >= mCoin->GetXPos() - 0.5f &&
            mQuads[i] ->GetXPos() + 0.5f <= mCoin->GetXPos() + 0.5f;

            bool collisionY = mQuads[i]->GetYPos() + 0.5f <= mCoin->GetYPos() + 0.5f &&
            mQuads[i]->GetYPos() - 0.5f >= mCoin->GetYPos() - 0.5f;

            if(collisionX && collisionY)
            {
                //std::cout << "Collision Happening" << std::endl;

                mCoin->Hide();
                mQuads.push_back(new Quad(mQuads[mQuads.size()-1]->GetXPos(),mQuads[mQuads.size()-1]->GetYPos()));
                mLastXPos.push_back(mQuads[mQuads.size()-1]->GetXPos());
                mLastYPos.push_back(mQuads[mQuads.size()-1]->GetYPos());
            }
        }
    }

    for(int j = 1; j<mQuads.size(); j++)
    {
        bool collisionX = mQuads[0]->GetXPos() - 0.5f >= mQuads[j]->GetXPos() - 0.5f &&
        mQuads[0] ->GetXPos() + 0.5f <= mQuads[j]->GetXPos() + 0.5f;

        bool collisionY = mQuads[0]->GetYPos() + 0.5f <= mQuads[j]->GetYPos() + 0.5f &&
        mQuads[0]->GetYPos() - 0.5f >= mQuads[j]->GetYPos() - 0.5f;

        if(collisionX && collisionY)
        {
            std::cout << "Damage was done" << std::endl;
            mDead = true;
        }
    }
}

void Snake::SetCoin(Coin* _coin)
{
    mCoin = _coin;
}
