#version 410 core
out vec4 fragColor;

in vec3 ourColor;
in vec2 texCoord;

uniform sampler2D texture1; // special uniform
uniform sampler2D texture2;

void main() {
    fragColor = mix(texture(texture1, texCoord), texture(texture2, texCoord), 0.2) * vec4(ourColor, 0.5);
}
