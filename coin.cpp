#include "headers/coin.h"

Coin::Coin(int _x, int _y)
{
    mX = _x;
    mY = _y;

    GLfloat vertices[] =
    {
    0.5f, 0.5f,0.0f, //TOP RIGHT
    0.5f, -0.5f, 0.0f, // BOTTOM RIGHT
    -0.5f, -0.5f,0.0f, // BOTTOM LEFT
    -0.5f, 0.5f, 0.0f //TOP LEFT
    };

    GLuint indices[] =
    {
      0,1,3,
      1,2,3
    };

    // Shaders
    GLchar* vertexShaderSource =
    "#version 330 core\n"
    "layout (location = 0) in vec3 position;\n"
    "uniform mat4 projectionMat;\n"
    "uniform mat4 modelMat;\n"
    "uniform mat4 viewMat;\n"
    "void main()\n"
    "{\n"
    "gl_Position = projectionMat * viewMat* modelMat * vec4(position, 1.0);\n"
    "}\0";
    GLchar* fragmentShaderSource = "#version 330 core\n"
    "out vec4 color;\n"
    "void main()\n"
    "{\n"
    "color = vec4(0.8f, 0.9f, 0.2f, 1.0f);\n"
    "}\n\0";

    mVertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(mVertexShader , 1, &vertexShaderSource, NULL);
    glCompileShader(mVertexShader);
    CheckShader(mVertexShader);

    mFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(mFragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(mFragmentShader);
    CheckShader(mFragmentShader);

    mShaderProgram = glCreateProgram();

    glAttachShader(mShaderProgram, mVertexShader );
    glAttachShader(mShaderProgram, mFragmentShader);
    glLinkProgram(mShaderProgram);

    CheckProgramShader(mShaderProgram);



    glGenVertexArrays(1, &mVAO);
    glGenBuffers(1, &mVBO);
    glGenBuffers(1, &mEBO);

    glBindVertexArray(mVAO);

    // 0. Copy our vertices array in a buffer for OpenGL to use
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
    GL_STATIC_DRAW);

    // 1. Then set the vertex attributes pointers

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    //4. Unbind the VAO
    glBindVertexArray(0);


}

void Coin::Update(double _deltaTime)
{
    if(!mDetectable)
    {
        mShowTimer += _deltaTime;
        //std::cout << "Doing stuff" << std::endl;
        if(mShowTimer >= 3)
        {
            Show();
            mShowTimer = 0;
        }
    }
}

void Coin::Show()
{
    srand(time(NULL));
    mX = rand() % 20 - 10;
    mY = rand() % 12 - 6;
    mDetectable = true;
}

void Coin::Hide()
{
    mDetectable = false;
}

void Coin::CheckShader(GLuint _shader)
{
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(_shader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(_shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::LOLZ::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}

int Coin::GetXPos()
{
    return mX;
}

int Coin::GetYPos()
{
    return mY;
}

void Coin::SetPosition(int _x, int _y)
{
    mX = _x;
    mY = _y;
}

void Coin::CheckProgramShader(GLuint _progShader)
{
    GLint success;
    GLchar infoLog[512];
    glGetProgramiv(_progShader, GL_LINK_STATUS, &success);

    if(!success)
    {
        glGetProgramInfoLog(_progShader, 512, NULL, infoLog);
    }
}

bool Coin::IsDetectable()
{
    return mDetectable;
}

void Coin::Render()
{
    glUseProgram(mShaderProgram);

    glm::mat4x4 projectionMat = glm::perspective(45.0f,800.0f/600.0f,0.1f,100.0f);
    GLuint projectionMatLoc = glGetUniformLocation(mShaderProgram, "projectionMat");
    glUniformMatrix4fv(projectionMatLoc, 1, GL_FALSE,
                       glm::value_ptr(projectionMat));

    GLuint modelMatLoc = glGetUniformLocation(mShaderProgram, "modelMat");
    glm::mat4x4 modelMat = glm::mat4x4();
    modelMat = glm::translate(modelMat,glm::vec3(mX,mY,0));
    modelMat = glm::scale(modelMat,glm::vec3(0.9f,0.9f,0));
    glUniformMatrix4fv(modelMatLoc , 1, GL_FALSE, glm::value_ptr(modelMat));

    GLuint viewMatLoc = glGetUniformLocation(mShaderProgram, "viewMat");
    glm::mat4x4 viewMat = glm::mat4x4();
    viewMat = glm::lookAt(glm::vec3(0,0,15),glm::vec3(),glm::vec3(0.0, 1.0f, 0.0f));
    glUniformMatrix4fv(viewMatLoc, 1, GL_FALSE, glm::value_ptr(viewMat));

    /* glm::mat4x4 trans;
    trans = glm::translate(trans,glm::vec3(0,0,5));
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE,
                       glm::value_ptr(glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 100.0f)));*/
    //glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr());

    glBindVertexArray(mVAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

Coin::~Coin()
{
    //dtor
    glDeleteShader(mVertexShader);
    glDeleteShader(mFragmentShader);
}
