#version 330 core
layout (location = 0) in vec3 in_position;
layout (location = 3) in vec3 in_normal;//se agrego esta linea

out vec3 our_normal;//se agrego esta linea
out vec3 fragPos;//se agrego esta linea

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main(){

	gl_Position = projection * view * model * vec4(in_position, 1.0);
	our_normal = mat3(transpose(inverse(model))) * in_normal;//se agrego esta linea
	fragPos = vec3(model * vec4(in_position, 1.0));//se agrego esta linea

}

