#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;
layout (location = 2) in vec2 aTex;

out vec3 fragNormal;
out vec2 texCoord;

uniform mat4 model; // model xform stuff
uniform mat4 view; // move stuff into camera view
uniform mat4 projection; // project are crap into homo coord space

void main() {
  gl_Position = projection*view*model*vec4(aPos, 1.0f);
  fragNormal = aNorm;
  texCoord = aTex;
}
