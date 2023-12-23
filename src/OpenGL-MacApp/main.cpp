#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Mesh.h"

// important glm::mat4 model is now glm::mat4 model(1.0f);
// or model = glm::mat(1.0f);


// Window dimensions
const GLint WIDTH = 800;
const GLint HEIGHT = 600;

std::vector<Mesh *> meshList;

GLuint shader;
int uniformModel;
int uniformProjection;

bool direction = true;
float triOffset = 0.0f;
float triMaxOffset = 0.7f;
float triIncrement = 0.005f;

float currentAngle = 0.0f;

bool sizeDirection = true;
float currentSize = 0.4f;
float maxSize = 0.8f;
float minSize = 0.1f;

// Vertex Shader code
static const char *vShader = "#version 330 \n layout (location = 0) in vec3 pos; \n out vec4 vCol; \n uniform mat4 model; \n uniform mat4 projection; \n void main(){ \n gl_Position = projection * model * vec4(pos, 1.0); \n vCol = vec4(clamp(pos, 0.0f, 1.0f), 1.0); \n }";

// Fragment Shader
static const char *fShader = "#version 330 \n in vec4 vCol; \n out vec4 colour; \n void main(){ colour = vCol; }";

float toRadians(float degrees) {
    return degrees * (3.14159265f / 180.0f);
}

void createTriangle() {

    unsigned int indices[] = {
            0, 3, 1,
            1, 3, 2,
            2, 3, 0,
            0, 1, 2
    };

    GLfloat vertices[] = {
            -1.0f, -1.0f, 0.0f,
            0.0f, -1.0f, 1.0f,
            1.0f, -1.0f, 0.0f,
            0.0f, 1.0f, 0.0f
    };

    Mesh *obj1 = new Mesh();
    obj1->CreateMesh(vertices, indices, 12, 12);
    meshList.push_back(obj1);

    Mesh *obj2 = new Mesh();
    obj2->CreateMesh(vertices, indices, 12, 12);
    meshList.push_back(obj2);
}

void addShader(GLuint program, const char *shaderCode, GLenum shaderType) {
    GLuint theShader = glCreateShader(shaderType);

    const GLchar *code[1];
    code[0] = shaderCode;

    GLint codeLength[1];
    codeLength[0] = strlen(shaderCode);

    glShaderSource(theShader, 1, code, codeLength);
    glCompileShader(theShader);

    GLint result = 0;
    GLchar eLog[1024] = {0};


    glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
    if (!result) {
        glGetShaderInfoLog(theShader, sizeof(eLog), nullptr, eLog);
        printf("Error compiling the %d shader: '%s' \n", shaderType, eLog);
        return;
    }

    glAttachShader(program, theShader);
}

void compileShaders() {
    shader = glCreateProgram();

    if (!shader) {
        printf("Error creating shader program! \n");
        return;
    }

    addShader(shader, vShader, GL_VERTEX_SHADER);
    addShader(shader, fShader, GL_FRAGMENT_SHADER);

    GLint result = 0;
    GLchar eLog[1024] = {0};

    glLinkProgram(shader);
    glGetProgramiv(shader, GL_LINK_STATUS, &result);
    if (!result) {
        glGetProgramInfoLog(shader, sizeof(eLog), nullptr, eLog);
        printf("Error linking program: '%s' \n", eLog);
        return;
    }

    glValidateProgram(shader);
    glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);
    if (!result) {
        glGetProgramInfoLog(shader, sizeof(eLog), nullptr, eLog);
        printf("Error Validating program: '%s' \n", eLog);
        return;
    }

    printf("Compiled Successfully\n");

    uniformModel = glGetUniformLocation(shader, "model");
    uniformProjection = glGetUniformLocation(shader, "projection");
}

int main() {

    // Initialise GLFW
    if (glfwInit() == GLFW_FALSE) {
        printf("GLFW initialisation failed!");
        glfwTerminate();
        return 1;
    }

    // Setup GLFW window properties
    // OpenGL version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // don't use deprecated features, no backwards compatibility
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // Allow forward compatibility
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow *mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "Test Window", nullptr, nullptr);
    if (!mainWindow) {
        printf("GLFW window creation failed");
        glfwTerminate();
        return 1;
    }

    // Get Buffer size information
    int bufferWidth;
    int bufferHeight;
    glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

    // Set context for GLEW to use
    glfwMakeContextCurrent(mainWindow);

    // Initialise GLEW
    // Allow modern extension features
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        printf("GLEW initialisation failed");
        glfwDestroyWindow(mainWindow);
        glfwTerminate();
        return 1;
    }

    // tell OpenGL to draw triangles over others
    glEnable(GL_DEPTH_TEST);

    // Create Viewport
    glViewport(0, 0, bufferWidth, bufferHeight);


    createTriangle();
    compileShaders();

    glm::mat4 projection = glm::perspective(toRadians(45.0f), (GLfloat) bufferWidth / (GLfloat) bufferHeight, 0.1f,
                                            100.0f);


// Loop until window closed
    while (!glfwWindowShouldClose(mainWindow)) {
        // Get and Handle user input events
        glfwPollEvents();

        if (direction) {
            triOffset += triIncrement;
        } else {
            triOffset -= triIncrement;
        }

        if (abs(triOffset) >= triMaxOffset) {
            direction = !direction;
        }

        currentAngle += 1.0f;
        if (currentAngle >= 360) {
            currentAngle -= 360;
        }

        if (sizeDirection) {
            currentSize += 0.01f;
        } else {
            currentSize -= 0.01f;
        }

        if (currentSize >= maxSize || currentSize <= minSize) {
            sizeDirection = !sizeDirection;
        }

        // Clear window
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        // clear both the colour and depth buffer bit
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shader);
        // attach the projection Matrix
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));

        glm::mat4 model(1.0f);
        // translate on x-axis by triOffset
        model = glm::translate(model, glm::vec3(triOffset, 0.0f, -2.5f));
        // scale
        model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        meshList[0]->RenderMesh();

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-triOffset, 0.5f, -2.0f));
        model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        meshList[1]->RenderMesh();

        glUseProgram(0);
        glfwSwapBuffers(mainWindow);
    }
    return 0;
}