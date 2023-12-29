#version 330
in vec4 vCol;
in vec2 TexCoord;

uniform sampler2D Texture;// don't need to setup uniform binding since its just one but if there was more would need to

out vec4 colour;


void main(){
    colour = texture(Texture, TexCoord);
}