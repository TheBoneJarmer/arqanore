#version 330 core
in vec2 a_position;
in vec2 a_texcoord;

uniform vec2 u_resolution;
uniform vec2 u_rotation;
uniform vec2 u_translation;
uniform vec4 u_color;

out vec4 color;
out vec2 texcoord;

void main() {
    vec2 rotatedPosition = vec2(a_position.x * u_rotation.y + a_position.y * u_rotation.x, a_position.y * u_rotation.y - a_position.x * u_rotation.x);
    vec2 zeroToOne = (rotatedPosition + u_translation) / u_resolution;
    vec2 zeroToTwo = zeroToOne * 2.0;
    vec2 clipSpace = zeroToTwo - 1.0;

    color = u_color;
    texcoord = a_texcoord;
    
    gl_Position = vec4(clipSpace.x, -clipSpace.y, 0, 1);
}
