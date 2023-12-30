#version 330
struct DirectionalLight {
    vec3 colour;
    float ambient_intensity;
    vec3 direction;
    float diffuse_intensity;
};

in vec4 vCol;
in vec2 TexCoord;
in vec3 Normal;

uniform sampler2D Texture;// don't need to setup uniform binding since its just one but if there was more would need to
uniform DirectionalLight directional_light;

out vec4 colour;

void main(){
    vec4 ambient_colour = vec4(directional_light.colour, 1.0f) * directional_light.ambient_intensity;

    //cos(angle) = A.B
    float diffuse_factor = max(dot(normalize(Normal), normalize(directional_light.direction)), 0.0f);
    vec4 diffuse_colour = vec4(directional_light.colour, 1.0f) * directional_light.diffuse_intensity * diffuse_factor;

    colour = texture(Texture, TexCoord) * (ambient_colour + diffuse_colour);
}