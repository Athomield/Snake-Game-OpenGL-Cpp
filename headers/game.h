#ifndef GAME_H
#define GAME_H
#include "window.h"
#include "input.h"
#include "snake.h"
#include "coin.h"

// member class must start with "m"

class Game
{

private:
    Window* mWindow = nullptr;
    Input* mInput = nullptr;
    Snake* mSnake = nullptr;
    Coin* mCoin = nullptr;

    double mDeltaTime = 0;
    double mLastFrame = 0;

public:
	Game();
	~Game();
private:
	void Update();
	void Render();
	void HandleInput();
};

#endif
