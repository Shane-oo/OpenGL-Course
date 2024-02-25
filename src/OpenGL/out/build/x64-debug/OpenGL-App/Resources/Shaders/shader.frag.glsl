#version 330
const int MAX_POINT_LIGHTS = 3;
const int MAX_SPOT_LIGHTS = 3;

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

struct SpotLight {
    PointLight pointLight;
    vec3 direction;
    float edge;
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
uniform int spotLightCount;

uniform DirectionalLight directional_light;
uniform PointLight point_lights[MAX_POINT_LIGHTS];
uniform SpotLight spotLights[MAX_SPOT_LIGHTS];


uniform sampler2D Texture;// don't need to setup uniform binding since its just one but if there was more would need to
uniform Material material;

uniform vec3 eye_position;

out vec4 colour;

vec4 CalcLightByDirection(Light light, vec3 direction){
    vec4 ambient_colour = vec4(light.colour, 1.0f) * light.ambient_intensity;

    //cos(angle) = A.B
    // -normalize(direction) as its the standard and the instructors does not follow
    float diffuse_factor = max(dot(normalize(Normal), -normalize(direction)), 0.0f);
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

vec4 CalcPointLight(PointLight pointLight){
    vec3 direction = FragPosition - pointLight.position;// direction of fragment to position of point light
    float distance = length(direction);

    vec4 colour = CalcLightByDirection(pointLight.base, direction);
    // quadratic equation
    float attenuation = (pointLight.exponent * distance * distance) + (pointLight.linear * distance) + pointLight.constant;

    return (colour / attenuation);
}

vec4 CalcSpotLight(SpotLight spotLight){
    vec3 rayDirection = normalize(FragPosition - spotLight.pointLight.position);

    float spotLightFactor = dot(rayDirection, spotLight.direction);
    if (spotLightFactor > spotLight.edge){
        vec4 colour = CalcPointLight(spotLight.pointLight);

        // soft edge
        float spotLightFade = 1.0f - ((1.0f - spotLightFactor) / (1.0f - spotLight.edge));

        return colour * spotLightFade;
    }

    return vec4(0, 0, 0, 0);
}

vec4 CalcPointLights(){
    vec4 totalColour = vec4(0.0, 0.0, 0.0, 0);
    for (int i = 0; i < point_light_count; i++){
        totalColour += CalcPointLight(point_lights[i]);
    }

    return totalColour;
}

vec4 CalcSpotLights(){
    vec4 totalColour = vec4(0, 0, 0, 0);
    for (int i = 0; i < spotLightCount; i++){
        totalColour += CalcSpotLight(spotLights[i]);
    }

    return totalColour;
}

void main(){
    vec4 final_colour = CalcDirectionalLight() + CalcPointLights() + CalcSpotLights();

    colour = texture(Texture, TexCoord) * final_colour;
}