
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Mesh.h"
#include "Shader.h"
#include "GLWindow.h"
#include "Camera.h"
#include "Texture.h"

// important glm::mat4 model is now glm::mat4 model(1.0f);
// or model = glm::mat(1.0f);

GLWindow mainWindow;
Camera camera;
std::vector<Mesh *> meshList;
std::vector<Shader *> shaderList;

Texture brickTexture;
Texture dirtTexture;

double delta_time = 0.0f;
double last_time = 0.0f;

// Vertex Shader codes
static const char *vShader = "shader.vert.glsl";

// Fragment Shader
static const char *fShader = "shader.frag.glsl";

float toRadians(float degrees) {
    return degrees * (3.14159265f / 180.0f);
}

void CalculateDeltaTime() {
    double now = glfwGetTime();
    delta_time = now - last_time;
    last_time = now;
}

void CreateObjects() {

    unsigned int indices[] = {
            0, 3, 1,
            1, 3, 2,
            2, 3, 0,
            0, 1, 2
    };

    GLfloat vertices[] = {
            // x        y           z           u       v
            -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, -1.0f, 1.0f, 0.5f, 0.0f,
            1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.5f, 1.0f
    };

    Mesh *obj1 = new Mesh();
    obj1->CreateMesh(vertices, indices, 20, 12);
    meshList.push_back(obj1);

    Mesh *obj2 = new Mesh();
    obj2->CreateMesh(vertices, indices, 20, 12);
    meshList.push_back(obj2);
}

void CreateShaders() {
    auto *shader1 = new Shader();
    shader1->CreateFromFiles(vShader, fShader);
    shaderList.push_back(shader1);
}

void CreateCamera() {
    glm::vec3 start_position = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 start_up = glm::vec3(0.0f, 1.0f, 0.0f);
    GLfloat start_yaw = -90.0f;
    GLfloat start_pitch = 0.0f;
    GLfloat start_movement_speed = 5.0f;
    GLfloat start_turn_speed = 0.5f;

    camera = Camera(start_position, start_up, start_yaw, start_pitch, start_movement_speed, start_turn_speed);
}

void CreateTextures() {
    brickTexture = Texture("Resources/Images/brick.png");
    brickTexture.LoadTexture();

    dirtTexture = Texture("Resources/Images/dirt.png");
    dirtTexture.LoadTexture();
}


int main() {

    mainWindow = GLWindow(800, 600);
    mainWindow.Initialise();

    CreateObjects();
    CreateShaders();
    CreateCamera();
    CreateTextures();


    glm::mat4 projection = glm::perspective(toRadians(45.0f),
                                            mainWindow.GetBufferWidth() / mainWindow.GetBufferHeight(),
                                            0.1f,
                                            100.0f);

    int uniformProjection = 0, uniformModel = 0, uniformView = 0;

    // Loop until window closed
    while (!mainWindow.GetShouldClose()) {
        CalculateDeltaTime();

        // Get and Handle user input events
        glfwPollEvents();

        camera.KeyControl(mainWindow.GetKeys(), delta_time);
        camera.MouseControl(mainWindow.GetMouseXChange(), mainWindow.GetMouseYChange());

        // Clear window
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        // clear both the colour and depth buffer bit
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shaderList[0]->UseShader();
        uniformModel = shaderList[0]->GetUniformModel();
        uniformProjection = shaderList[0]->GetUniformProjection();
        uniformView = shaderList[0]->GetUniformView();

        // attach the projection Matrix
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        // attach the view
        glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.CalculateViewMatrix()));

        glm::mat4 model(1.0f);
        // translate on x-axis by triOffset
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
        // scale
        model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

        brickTexture.UseTexture();
        meshList[0]->RenderMesh();

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.5f, -2.0f));
        model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

        dirtTexture.UseTexture();
        meshList[1]->RenderMesh();

        glUseProgram(0);

        mainWindow.SwapBuffers();
    }
    return 0;
}