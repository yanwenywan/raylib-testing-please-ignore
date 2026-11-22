#version 330

// from raylib default assingment
in vec2 fragTexCoord;
in vec4 fragColor;

uniform sampler2D texture0;
uniform vec4 colDiffuse;

// output
out vec4 finalColor;


const float renderWidth = 1600;
const float renderHeight = 1000;

const float pixelWidth = 5.0;
const float pixelHeight = 5.0;

void main() {
    float dx = pixelWidth * (1.0/renderWidth);
    float dy = pixelHeight * (1.0/renderHeight);

    vec2 coord = vec2(dx * floor(fragTexCoord.x/dx), dy * floor(fragTexCoord.y/dy));

    vec3 rgb = texture(texture0, coord).rgb;

    finalColor = vec4(rgb, 1.0f);
}
