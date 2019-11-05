#version 330 core

in vec2 our_uv;
out vec4 color;
uniform sampler2D texture1;

void main(){
	color = texture(texture1, our_uv);
	if(color.a < 0.8)
		discard;
}
