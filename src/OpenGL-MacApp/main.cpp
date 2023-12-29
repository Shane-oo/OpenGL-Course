
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
#include "Light.h"

// important glm::mat4 model is now glm::mat4 model(1.0f);
// or model = glm::mat(1.0f);

GLWindow main_window;
Camera camera;
std::vector<Mesh *> mesh_list;
std::vector<Shader *> shader_list;

Texture brick_texture;
Texture dirt_texture;

Light ambient_light;

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
    mesh_list.push_back(obj1);

    Mesh *obj2 = new Mesh();
    obj2->CreateMesh(vertices, indices, 20, 12);
    mesh_list.push_back(obj2);
}

void CreateShaders() {
    auto *shader1 = new Shader();
    shader1->CreateFromFiles(vShader, fShader);
    shader_list.push_back(shader1);
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
    brick_texture = Texture("Resources/Images/brick.png");
    brick_texture.LoadTexture();

    dirt_texture = Texture("Resources/Images/dirt.png");
    dirt_texture.LoadTexture();
}

void CreateLights() {
    GLfloat red = 1.0f;
    GLfloat green = 1.0f;
    GLfloat blue = 1.0f;
    GLfloat intensity = 0.2f;
    ambient_light = Light(red, green, blue, intensity);
}


int main() {

    main_window = GLWindow(800, 600);
    main_window.Initialise();

    CreateObjects();
    CreateShaders();
    CreateCamera();
    CreateTextures();
    CreateLights();


    glm::mat4 projection = glm::perspective(toRadians(45.0f),
                                            main_window.GetBufferWidth() / main_window.GetBufferHeight(),
                                            0.1f,
                                            100.0f);

    int uniform_projection = 0, uniform_model = 0, uniform_view = 0, uniform_ambient_intensity = 0, uniform_ambient_colour = 0;

    // Loop until window closed
    while (!main_window.GetShouldClose()) {
        CalculateDeltaTime();

        // Get and Handle user input events
        glfwPollEvents();

        camera.KeyControl(main_window.GetKeys(), delta_time);
        camera.MouseControl(main_window.GetMouseXChange(), main_window.GetMouseYChange());

        // Clear window
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        // clear both the colour and depth buffer bit
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader_list[0]->UseShader();
        uniform_model = shader_list[0]->GetUniformModel();
        uniform_projection = shader_list[0]->GetUniformProjection();
        uniform_view = shader_list[0]->GetUniformView();

        uniform_ambient_colour = shader_list[0]->GetUniformAmbientColour();
        uniform_ambient_intensity = shader_list[0]->GetUniformAmbientIntensity();
        ambient_light.UseLight(uniform_ambient_intensity, uniform_ambient_colour);

        // attach the projection Matrix
        glUniformMatrix4fv(uniform_projection, 1, GL_FALSE, glm::value_ptr(projection));
        // attach the view
        glUniformMatrix4fv(uniform_view, 1, GL_FALSE, glm::value_ptr(camera.CalculateViewMatrix()));

        glm::mat4 model(1.0f);
        // translate on x-axis by triOffset
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
        // scale
        model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
        glUniformMatrix4fv(uniform_model, 1, GL_FALSE, glm::value_ptr(model));

        brick_texture.UseTexture();
        mesh_list[0]->RenderMesh();

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.5f, -2.0f));
        model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
        glUniformMatrix4fv(uniform_model, 1, GL_FALSE, glm::value_ptr(model));

        dirt_texture.UseTexture();
        mesh_list[1]->RenderMesh();

        glUseProgram(0);

        main_window.SwapBuffers();
    }
    return 0;
}