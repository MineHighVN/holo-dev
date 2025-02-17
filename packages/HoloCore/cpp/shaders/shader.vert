#version 450

layout(location = 0) in vec2 inPosition;
layout(location = 1) in vec3 inColor;

layout(location = 0) out vec3 fragColor;

layout(set = 0, binding = 0) uniform UBO { 
    mat4 model;  // rotate and scale
    mat4 proj;   // projection matrix
    // dont care about view matrix
} ubo;

void main() {
    fragColor = inColor;
    gl_Position = ubo.proj * ubo.model * vec4(inPosition, 0.0, 1.0); 
}
