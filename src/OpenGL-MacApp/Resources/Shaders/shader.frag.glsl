#version 330
const int MAX_POINT_LIGHTS = 3;

struct Light {
    vec3 colour;
    float ambient_intensity;
    float diffuse_intensity;
};

struct DirectionalLight {
    Light base;
    vec3 direction;
};

struct PointLight{
    Light base;
    vec3 position;
    float constant;
    float linear;
    float exponent;
};


struct Material {
    float specular_intensity;
    float shininess;
};

in vec4 vCol;
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPosition;

uniform int point_light_count;

uniform DirectionalLight directional_light;
uniform PointLight point_lights[MAX_POINT_LIGHTS];


uniform sampler2D Texture;// don't need to setup uniform binding since its just one but if there was more would need to
uniform Material material;

uniform vec3 eye_position;

out vec4 colour;

vec4 CalcLightByDirection(Light light, vec3 direction){
    vec4 ambient_colour = vec4(light.colour, 1.0f) * light.ambient_intensity;

    //cos(angle) = A.B
    float diffuse_factor = max(dot(normalize(Normal), normalize(direction)), 0.0f);
    vec4 diffuse_colour = vec4(light.colour * light.diffuse_intensity * diffuse_factor, 1.0f);

    vec4 specular_colour = vec4(0, 0, 0, 0);

    if (diffuse_factor > 0.0f){
        vec3 frag_to_eye = normalize(eye_position - FragPosition);//which direction the fragment is to the eye position
        vec3 reflected_vertex = normalize(reflect(normalize(direction), normalize(Normal)));// does direction need to be normalized?

        float specular_factor = dot(frag_to_eye, reflected_vertex);
        if (specular_factor > 0.0f){
            specular_factor = pow(specular_factor, material.shininess);
            specular_colour = vec4(light.colour * material.specular_intensity * specular_factor, 1.0f);
        }
    }

    return (ambient_colour + diffuse_colour + specular_colour);
}

vec4 CalcDirectionalLight(){
    return CalcLightByDirection(directional_light.base, directional_light.direction);
}

vec4 CalcPointLights(){
    vec4 totalColour = vec4(0.0, 0.0, 0.0, 0);
    for (int i = 0; i < point_light_count; i++){
        vec3 direction = FragPosition - point_lights[i].position;// direction of fragment to position of point light
        float distance = length(direction);

        vec4 colour = CalcLightByDirection(point_lights[i].base, direction);
        // quadratic equation
        float attenuation = (point_lights[i].exponent * distance * distance) + (point_lights[i].linear * distance) + point_lights[i].constant;

        totalColour += (colour / attenuation);
    }

    return totalColour;
}

void main(){
    vec4 final_colour = CalcDirectionalLight() + CalcPointLights();

    colour = texture(Texture, TexCoord) * final_colour;
}