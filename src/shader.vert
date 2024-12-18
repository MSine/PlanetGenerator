#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNor;
layout (location = 2) in vec3 aCol;

out vec3 normal;
out vec3 pos;
out vec3 color;

uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * vec4(aPos, 1.0f);
	normal = aNor;
	pos = aPos;
	color = aCol;
}