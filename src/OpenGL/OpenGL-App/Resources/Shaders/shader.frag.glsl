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

struct PointLight {
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
in vec4 DirectionalLightSpacePos;

uniform int point_light_count;
uniform int spotLightCount;

uniform DirectionalLight directional_light;
uniform PointLight point_lights[MAX_POINT_LIGHTS];
uniform SpotLight spotLights[MAX_SPOT_LIGHTS];


uniform sampler2D theTexture;// don't need to setup uniform binding since its just one but if there was more would need to
uniform sampler2D directionalShadowMap;

uniform Material material;

uniform vec3 eye_position;

out vec4 colour;

float CalcDirectionalShadowFactor(DirectionalLight light) {
    // -1 to 1 range
    vec3 projCoords = DirectionalLightSpacePos.xyz / DirectionalLightSpacePos.w;
    // 0 to 1 range
    projCoords = (projCoords * 0.5) + 0.5;

    float closest = texture(directionalShadowMap, projCoords.xy).r;


    float currentDepth = projCoords.z;

    //vec3 normal = normalize(Normal);
    //vec3 lightDirection = normalize(light.direction);

    //float bias = max(0.05 * (1.0 - dot(normal, lightDirection)), 0.0005);

    
    float shadow = currentDepth > closest ? 1.0 : 0.0;

/**
    vec2 texelSize = 1.0 / textureSize(directionalShadowMap, 0);
    for (int x = -1; x <= 1; ++x) {
        for (int y = -1; y <= 1; ++y) {
            
            float pcfDepth = texture(directionalShadowMap, projCoords.xy + vec2(x, y) * texelSize).r;
            
            shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0; // 1 = full shadow, 0 = no shadow
            
            
        }
    }

    shadow /= 9.0; // x = -1,0,1 y = -1,0,1 => 3*3 = 9
*/

  /**  if (projCoords.z > 1.0) {
        shadow = 0.0;
    }*/

    return shadow;
}


vec4 CalcLightByDirection(Light light, vec3 direction, float shadowFactor) {
    vec4 ambient_colour = vec4(light.colour, 1.0f) * light.ambient_intensity;

    //cos(angle) = A.B
    // -normalize(direction) as its the standard and the instructors does not follow
    float diffuse_factor = max(dot(normalize(Normal), -normalize(direction)), 0.0f);
    vec4 diffuse_colour = vec4(light.colour * light.diffuse_intensity * diffuse_factor, 1.0f);

    vec4 specular_colour = vec4(0, 0, 0, 0);

    if (diffuse_factor > 0.0f) {
        vec3 frag_to_eye = normalize(eye_position - FragPosition);//which direction the fragment is to the eye position
        vec3 reflected_vertex = normalize(reflect(normalize(direction), normalize(Normal)));// does direction need to be normalized?

        float specular_factor = dot(frag_to_eye, reflected_vertex);
        if (specular_factor > 0.0f) {
            specular_factor = pow(specular_factor, material.shininess);
            specular_colour = vec4(light.colour * material.specular_intensity * specular_factor, 1.0f);
        }
    }

    // shadow is only applied to diffuse and specular, ambient always is present
    return (ambient_colour + ((1.0 - shadowFactor) * (diffuse_colour + specular_colour)));
}

vec4 CalcDirectionalLight() {
    float shadowFactor = CalcDirectionalShadowFactor(directional_light);
    return CalcLightByDirection(directional_light.base, directional_light.direction, shadowFactor);
}

vec4 CalcPointLight(PointLight pointLight) {
    vec3 direction = FragPosition - pointLight.position;// direction of fragment to position of point light
    float distance = length(direction);

    vec4 colour = CalcLightByDirection(pointLight.base, direction, 0.0f);
    // quadratic equation
    float attenuation = (pointLight.exponent * distance * distance) + (pointLight.linear * distance) + pointLight.constant;

    return (colour / attenuation);
}

vec4 CalcSpotLight(SpotLight spotLight) {
    vec3 rayDirection = normalize(FragPosition - spotLight.pointLight.position);

    float spotLightFactor = dot(rayDirection, spotLight.direction);
    if (spotLightFactor > spotLight.edge) {
        vec4 colour = CalcPointLight(spotLight.pointLight);

        // soft edge
        float spotLightFade = 1.0f - ((1.0f - spotLightFactor) / (1.0f - spotLight.edge));

        return colour * spotLightFade;
    }

    return vec4(0, 0, 0, 0);
}

vec4 CalcPointLights() {
    vec4 totalColour = vec4(0.0, 0.0, 0.0, 0);
    for (int i = 0; i < point_light_count; i++) {
        totalColour += CalcPointLight(point_lights[i]);
    }

    return totalColour;
}

vec4 CalcSpotLights() {
    vec4 totalColour = vec4(0, 0, 0, 0);
    for (int i = 0; i < spotLightCount; i++) {
        totalColour += CalcSpotLight(spotLights[i]);
    }

    return totalColour;
}

void main() {
    vec4 final_colour = CalcDirectionalLight() + CalcPointLights() + CalcSpotLights();

    colour = texture(theTexture, TexCoord) * final_colour;
}