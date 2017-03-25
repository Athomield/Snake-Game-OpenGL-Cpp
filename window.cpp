#include "headers/window.h"

GLFWwindow* Window::mWindow = NULL;
Window* Window::mInstance = NULL;

Window::Window()
{
    const GLuint WIDTH = 800, HEIGHT = 600;
	  // Init GLFW
    glfwInit( );

    // Set all the required options for GLFW
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
    glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );

    glfwWindowHint( GLFW_RESIZABLE, GL_FALSE );

    // Create a GLFWwindow object that we can use for GLFW's functions
    mWindow = glfwCreateWindow( WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr );

    int screenWidth, screenHeight;
    glfwGetFramebufferSize( mWindow, &screenWidth, &screenHeight );

    if ( nullptr == mWindow )
    {
        std::cout << "Failed to create GLFW mWindow" << std::endl;
        glfwTerminate( );
    }

    glfwMakeContextCurrent( mWindow );

    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;
    // Initialize GLEW to setup the OpenGL Function pointers
    if ( GLEW_OK != glewInit() )
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
    }

    // Define the viewport dimensions
    glViewport(0, 0, screenWidth, screenHeight );
}

GLFWwindow* Window::GetGLFWWindow()
{
    return mWindow;
}

Window::~Window()
{
	delete mWindow;
	//delete mRenderer;
	delete mInstance;
}

void Window::CreateWindow()
{
    if(mInstance == NULL)
        mInstance = new Window();
}

Window* Window::GetWindow()
{
	return mInstance;
}
