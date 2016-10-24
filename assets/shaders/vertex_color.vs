#version 330

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec4 aColor;

out vec4 vColor;

uniform mat4 MVP;

void main() {
  gl_Position = MVP * vec4(aPosition, 1.0);
  vColor = aColor;
}
