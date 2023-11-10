#version 410
in vec2 vTexCoord;

out vec4 fragColor;

uniform sampler2D textureSlot;

void main() {
    fragColor = texture(textureSlot, vTexCoord);
}