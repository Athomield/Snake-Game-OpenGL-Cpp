#include "headers/game.h"

Game::Game()
{
    mWindow->CreateWindow();
    mInput->CreateInstance();
    mSnake = new Snake();
    mCoin = new Coin(5,5);
    mSnake->SetCoin(mCoin);
    Update();
}

void Game::Render()
{
    glClearColor( 0.1f, 0.4f, 0.4f, 1.f );
    //Clear color buffer
	glClear( GL_COLOR_BUFFER_BIT );

	mSnake->Render();

	if(mCoin->IsDetectable())
        mCoin->Render();

    glfwSwapBuffers(Window::GetWindow()->GetGLFWWindow());
//	SDL_GL_SwapBuffers();
}

void Game::Update()
{
    while(!glfwWindowShouldClose(Window::GetWindow()->GetGLFWWindow()))
    {
        double lCurrentFrame = glfwGetTime();
        mDeltaTime = lCurrentFrame - mLastFrame;
        mLastFrame = lCurrentFrame;

        HandleInput();

        mSnake->Update(mDeltaTime);
        mCoin->Update(mDeltaTime);
        Render();
        //std::cout << 1/mDeltaTime << std::endl;
    }

    glfwTerminate();
}

void Game::HandleInput()
{
    glfwPollEvents();
}

Game::~Game()
{
    delete mSnake;
    delete mCoin;
}
