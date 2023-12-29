#version 330
struct DirectionalLight {
    vec3 colour;
    float ambient_intensity;
};

in vec4 vCol;
in vec2 TexCoord;

uniform sampler2D Texture;// don't need to setup uniform binding since its just one but if there was more would need to
uniform DirectionalLight directional_light;


out vec4 colour;


void main(){
    vec4 ambient_colour = vec4(directional_light.colour, 1.0f) * directional_light.ambient_intensity;

    colour = texture(Texture, TexCoord) * ambient_colour;
}