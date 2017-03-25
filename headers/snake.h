#ifndef SNAKE_H
#define SNAKE_H

#include "window.h"
#include "quad.h"
#include "input.h"
#include "coin.h"
#include <vector>

class Snake
{

private:
    std::vector<Quad*> mQuads;
    std::vector<int> mLastXPos;
    std::vector<int> mLastYPos;

    Coin* mCoin = nullptr;
    double mTimer = 0;
    enum mMoveDirection {MOVE_UP,MOVE_DOWN,MOVE_RIGHT,MOVE_LEFT};
    int mDir = MOVE_RIGHT;
    bool mDead = false;

public:
    Snake();
    ~Snake();

    void Render();
    void Update(double _deltaTime);

    void Translate(int _x, int _y);
    void SetCoin(Coin* _coin);

};


#endif // SNAKE_H
