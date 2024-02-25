
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
#include "Material.h"
#include "Lights/DirectionalLight.h"

// important glm::mat4 model is now glm::mat4 model(1.0f);
// or model = glm::mat(1.0f);

GLWindow main_window;
Camera camera;
std::vector<Mesh *> mesh_list;
std::vector<Shader *> shader_list;

Texture brick_texture;
Texture dirt_texture;
Texture plain_texture;

Material shiny_material;
Material dull_material;

DirectionalLight main_light;
PointLight point_lights[MAX_POINT_LIGHTS];
SpotLight spotLights[MAX_SPOT_LIGHTS];

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

void CalcAverageNormals(const unsigned int *indices, unsigned int indicesCount, float *vertices,
                        unsigned int verticesCount, unsigned int vertexLength, unsigned int normalOffset) {
    for (size_t i = 0; i < indicesCount; i += 3) {
        unsigned int in0 = indices[i] * vertexLength;
        unsigned int in1 = indices[i + 1] * vertexLength;
        unsigned int in2 = indices[i + 2] * vertexLength;

        glm::vec3 v1(vertices[in1] - vertices[in0],
                     vertices[in1 + 1] - vertices[in0 + 1],
                     vertices[in1 + 2] - vertices[in0 + 2]);
        glm::vec3 v2(vertices[in2] - vertices[in0],
                     vertices[in2 + 1] - vertices[in0 + 1],
                     vertices[in2 + 2] - vertices[in0 + 2]);

        glm::vec3 normal = glm::cross(v1, v2);
        normal = glm::normalize(normal);

        in0 += normalOffset;
        in1 += normalOffset;
        in2 += normalOffset;

        vertices[in0] += normal.x;
        vertices[in0 + 1] += normal.y;
        vertices[in0 + 2] += normal.z;

        vertices[in1] += normal.x;
        vertices[in1 + 1] += normal.y;
        vertices[in1 + 2] += normal.z;

        vertices[in2] += normal.x;
        vertices[in2 + 1] += normal.y;
        vertices[in2 + 2] += normal.z;
    }

    // normalize normals
    for (size_t i = 0; i < verticesCount / vertexLength; i++) {
        unsigned int nOffset = i * vertexLength + normalOffset;
        glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
        vec = glm::normalize(vec);
        vertices[nOffset] = vec.x;
        vertices[nOffset + 1] = vec.y;
        vertices[nOffset + 2] = vec.z;
    }
}

void CreateObjects() {

    unsigned int indices[] = {
            0, 3, 1,
            1, 3, 2,
            2, 3, 0,
            0, 1, 2
    };

    GLfloat vertices[] = {
            // x        y           z           u       v       normals(x,y,z)
            -1.0f, -1.0f, -0.6f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, -1.0f, 1.0f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f,
            1.0f, -1.0f, -0.6f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f
    };

    unsigned int floor_indices[] = {
            0, 2, 1,
            1, 2, 3
    };

    GLfloat floor_vertices[] = {
            -10.0f, 0.0f, -10.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
            10.0f, 0.0f, -10.0f, 10.0f, 0.0f, 0.0f, -1.0f, 0.0f,
            -10.0f, 0.0f, 10.0f, 0.0f, 10.0f, 0.0f, -1.0f, 0.0f,
            10.0f, 0.0f, 10.0f, 10.0f, 10.0f, 0.0f, -1.0f, 0.0f
    };

    CalcAverageNormals(indices, 12, vertices, 32, 8, 5);

    Mesh *obj1 = new Mesh();
    obj1->CreateMesh(vertices, indices, 32, 12);
    mesh_list.push_back(obj1);

    Mesh *obj2 = new Mesh();
    obj2->CreateMesh(vertices, indices, 32, 12);
    mesh_list.push_back(obj2);

    Mesh *obj3 = new Mesh();
    obj3->CreateMesh(floor_vertices, floor_indices, 32, 6);
    mesh_list.push_back(obj3);
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
    brick_texture.LoadTextureWithAlpha();

    dirt_texture = Texture("Resources/Images/dirt.png");
    dirt_texture.LoadTextureWithAlpha();

    plain_texture = Texture("Resources/Images/plain.png");
    plain_texture.LoadTextureWithAlpha();
}

void CreateMaterials() {
    shiny_material = Material(4.0f, 256);
    dull_material = Material(0.3f, 4);
}

void CreateLights(GLint &point_light_count, GLint &spotLightCount) {
    GLfloat red = 1.0f;
    GLfloat green = 1.0f;
    GLfloat blue = 1.0f;
    GLfloat ambient_intensity = 0.1f;
    GLfloat diffuse_intensity = 0.4f;

    GLfloat x_direction = 2.0f;
    GLfloat y_direction = -1.0f;
    GLfloat z_direction = -2.0f;


    main_light = DirectionalLight(red, green, blue, ambient_intensity, diffuse_intensity,
                                  x_direction, y_direction, z_direction);

    GLfloat point_light1_red = 0.0f;
    GLfloat point_light1_green = 0.0f;
    GLfloat point_light1_blue = 1.0f;
    GLfloat point_light1_ambient_intensity = 0.1f;
    GLfloat point_light1_diffuse_intensity = 0.5f;

    GLfloat point_light1_x_position = 4.0f;
    GLfloat point_light1_y_position = 0.0f;
    GLfloat point_light1_z_position = 0.0f;

    // 100 Range
    GLfloat point_light1_exponent = 0.0075f;
    GLfloat point_light1_linear = 0.045f;
    GLfloat point_light1_constant = 1.0f;


    point_lights[0] = PointLight(point_light1_red, point_light1_green, point_light1_blue,
                                 point_light1_ambient_intensity, point_light1_diffuse_intensity,
                                 point_light1_x_position, point_light1_y_position, point_light1_z_position,
                                 point_light1_constant, point_light1_linear, point_light1_exponent);
    point_light_count += 1;

    GLfloat point_light2_red = 0.0f;
    GLfloat point_light2_green = 1.0f;
    GLfloat point_light2_blue = 0.0f;
    GLfloat point_light2_ambient_intensity = 0.1f;
    GLfloat point_light2_diffuse_intensity = 0.1f;

    GLfloat point_light2_x_position = -4.0f;
    GLfloat point_light2_y_position = 2.0f;
    GLfloat point_light2_z_position = 0.0f;

    // 50 Range
    GLfloat point_light2_exponent = 0.032f;
    GLfloat point_light2_linear = 0.09f;
    GLfloat point_light2_constant = 1.0f;

    point_lights[1] = PointLight(point_light2_red, point_light2_green, point_light2_blue,
                                 point_light2_ambient_intensity, point_light2_diffuse_intensity,
                                 point_light2_x_position, point_light2_y_position, point_light2_z_position,
                                 point_light2_constant, point_light2_linear, point_light2_exponent);
    point_light_count += 1;


    GLfloat spotLight1_red = 1.0f;
    GLfloat spotLight1_green = 1.0f;
    GLfloat spotLight1_blue = 1.0f;
    GLfloat spotLight1_ambient_intensity = 0.0f;
    GLfloat spotLight1_diffuse_intensity = 2.0f;

    GLfloat spotLight1_x_position = 4.0f;
    GLfloat spotLight1_y_position = 0.0f;
    GLfloat spotLight1_z_position = 0.0f;


    GLfloat spotLight1_exponent = 0.1;
    GLfloat spotLight1_linear = 0.2f;
    GLfloat spotLight1_constant = 0.3f;

    GLfloat spotLight1XDirection = 0.0f;
    GLfloat spotLight1YDirection = -1.0f;
    GLfloat spotLight1ZDirection = 0.0f;

    GLfloat spotLight1Edge = 20.0f; // 20 degrees

    spotLights[0] = SpotLight(spotLight1_red, spotLight1_green, spotLight1_blue, spotLight1_ambient_intensity,
                              spotLight1_diffuse_intensity,
                              spotLight1_x_position, spotLight1_y_position, spotLight1_z_position,
                              spotLight1XDirection, spotLight1YDirection, spotLight1ZDirection,
                              spotLight1_constant, spotLight1_linear, spotLight1_exponent,
                              spotLight1Edge);
    spotLightCount++;
}


int main() {

    main_window = GLWindow(1366, 768);
    main_window.Initialise();

    CreateObjects();
    CreateShaders();
    CreateCamera();
    CreateTextures();
    CreateMaterials();
    GLint point_light_count = 0;
    GLint spotLightCount = 0;
    CreateLights(point_light_count, spotLightCount);


    glm::mat4 projection = glm::perspective(toRadians(45.0f),
                                            main_window.GetBufferWidth() / main_window.GetBufferHeight(),
                                            0.1f,
                                            100.0f);

    GLint uniform_projection = 0, uniform_model = 0, uniform_view = 0, uniform_eye_position = 0,
            uniform_specular_intensity = 0, uniform_shininess = 0;

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
        uniform_eye_position = shader_list[0]->GetUniformEyePosition();

        uniform_specular_intensity = shader_list[0]->GetUniformSpecularIntensity();
        uniform_shininess = shader_list[0]->GetUniformShininess();

        spotLights[0].SetAsFlashLight(camera.getPosition(), camera.GetDirection());

        shader_list[0]->SetDirectionalLight(&main_light);
        shader_list[0]->SetPointLights(point_lights, point_light_count);
        shader_list[0]->SetSpotLights(spotLights, spotLightCount);


        // attach the projection Matrix
        glUniformMatrix4fv(uniform_projection, 1, GL_FALSE, glm::value_ptr(projection));
        // attach the view
        glUniformMatrix4fv(uniform_view, 1, GL_FALSE, glm::value_ptr(camera.CalculateViewMatrix()));
        // attach the eye_position
        glm::vec3 camera_position = camera.getPosition();
        glUniform3f(uniform_eye_position, camera_position.x, camera_position.y, camera_position.z);

        glm::mat4 model(1.0f);
        // translate on x-axis by triOffset
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
        // scale
        //model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
        glUniformMatrix4fv(uniform_model, 1, GL_FALSE, glm::value_ptr(model));

        brick_texture.UseTexture();
        shiny_material.UseMaterial(uniform_specular_intensity, uniform_shininess);
        mesh_list[0]->RenderMesh();

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 3.0f, -2.5f));
        //model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
        glUniformMatrix4fv(uniform_model, 1, GL_FALSE, glm::value_ptr(model));

        dirt_texture.UseTexture();
        dull_material.UseMaterial(uniform_specular_intensity, uniform_shininess);
        mesh_list[1]->RenderMesh();


        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -2.0f, 0.0f));
        //model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
        glUniformMatrix4fv(uniform_model, 1, GL_FALSE, glm::value_ptr(model));

        dirt_texture.UseTexture();
        shiny_material.UseMaterial(uniform_specular_intensity, uniform_shininess);
        mesh_list[2]->RenderMesh();

        glUseProgram(0);

        main_window.SwapBuffers();
    }
    return 0;
}