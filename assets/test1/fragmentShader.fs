#version 330 core

in vec2 texCoord;
in vec4 fragPos;

out vec4 FragColor;

uniform sampler2D spriteSheet;

void main() {
  vec2 texcoord = vec2(texCoord.x, texCoord.y);
 	FragColor = texture(spriteSheet, texcoord);
}
