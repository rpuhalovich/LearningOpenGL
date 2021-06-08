#version 410 core
out vec4 fragColor;

in vec3 ourColor;
in vec2 texCoord;

uniform sampler2D texture1; // special uniform
// uniform sampler2D texture2;

void main() {
    fragColor = texture(texture1, texCoord) * vec4(ourColor, 0.5);
}
