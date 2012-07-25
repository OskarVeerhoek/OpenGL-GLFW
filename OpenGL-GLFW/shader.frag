#version 150 core

uniform sampler2D texture;

smooth in vec4 fragment_colour;
smooth in vec2 fragment_texture_coordinate;

void main()
{
    gl_FragColor = mix(fragment_colour, texture2D(texture, fragment_texture_coordinate), 0.7);
}