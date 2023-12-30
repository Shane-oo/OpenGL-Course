#version 330
struct DirectionalLight {
    vec3 colour;
    float ambient_intensity;
    vec3 direction;
    float diffuse_intensity;
};

struct Material {
    float specular_intensity;
    float shininess;
};

in vec4 vCol;
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPosition;

uniform sampler2D Texture;// don't need to setup uniform binding since its just one but if there was more would need to
uniform DirectionalLight directional_light;
uniform Material material;

uniform vec3 eye_position;

out vec4 colour;

void main(){
    vec4 ambient_colour = vec4(directional_light.colour, 1.0f) * directional_light.ambient_intensity;

    //cos(angle) = A.B
    float diffuse_factor = max(dot(normalize(Normal), normalize(directional_light.direction)), 0.0f);
    vec4 diffuse_colour = vec4(directional_light.colour, 1.0f) * directional_light.diffuse_intensity * diffuse_factor;

    vec4 specular_colour = vec4(0, 0, 0, 0);

    if (diffuse_factor > 0.0f){
        vec3 frag_to_eye = normalize(eye_position - FragPosition);//which direction the fragment is to the eye position
        vec3 reflected_vertex = normalize(reflect(normalize(directional_light.direction), normalize(Normal)));// does directional_light.direction need to be normalized?

        float specular_factor = dot(frag_to_eye, reflected_vertex);
        if (specular_factor > 0.0f){
            specular_factor = pow(specular_factor, material.shininess);
            specular_colour = vec4(directional_light.colour * material.specular_intensity * specular_factor, 1.0f);
        }
    }

    colour = texture(Texture, TexCoord) * (ambient_colour + diffuse_colour + specular_colour);
}