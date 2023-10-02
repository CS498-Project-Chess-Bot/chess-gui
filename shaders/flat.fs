#version 410
out vec4 fragColor;

uniform float r;

void main() {
    fragColor = vec4(r, 0.4, 0.0, 1.0);
}