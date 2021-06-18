#version 410 core
out vec4 fragColor;

in vec2 texCoord;

uniform sampler2D texture1; // special uniform

void main() {
    fragColor = texture(texture1, texCoord);
}
