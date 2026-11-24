// https://www.shadertoy.com/view/WtdXR8
#version 330

in vec2 fragTexCoord;
in vec4 fragColor;

uniform sampler2D texture0;
uniform vec4 colDiffuse;

uniform float time;
uniform vec2 resolution;

out vec4 finalColor;

void main() {
    vec2 uv = (2.0 * gl_FragCoord.xy - resolution.xy) / min(resolution.x, resolution.y);

    for(float i = 1.0; i < 10.0; i++) {
        uv.x += 0.6 / i * cos(i * 2.5* uv.y + time);
        uv.y += 0.6 / i * cos(i * 1.5 * uv.x + time);
    }

    vec4 textureCol = texture(texture0, fragTexCoord);
    float marblingFactor = abs(sin(time - uv.y - uv.x));
    finalColor = vec4(textureCol.xyz / marblingFactor, 1.0);
}

