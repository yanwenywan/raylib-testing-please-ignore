#version 330 

in vec2 fragTexCoord;
in vec4 fragColor;

uniform sampler2D texture0;
uniform vec4 colDiffuse;

uniform vec2 mousePos;
uniform vec2 resolution;

out vec4 finalColor;

const float maxLightRadius = 0.5;
const vec4 black = vec4(0.0, 0.0, 0.0, 1.0);

// gl_FragCoord is the PIXEL coordinates on the SCREEN (not normalised) with (0,0) at the bottom left
void main() {
    // this keeps the light radius round rather than the aspect ratio of the window
    float scalingFactor = min(resolution.x, resolution.y);
    vec2 normalisedRes = gl_FragCoord.xy / scalingFactor;
    vec2 normalisedMouse = mousePos / scalingFactor;
    float distanceToMouse = distance(normalisedRes, normalisedMouse);
    vec4 textureCol = texture(texture0, fragTexCoord);

    float lightStrength = distanceToMouse / maxLightRadius;
    lightStrength = clamp(lightStrength, 0.0, 1.0);
    
    finalColor = mix(textureCol, vec4(0.0, 0.0, 0.0, 1.0), lightStrength);
}
