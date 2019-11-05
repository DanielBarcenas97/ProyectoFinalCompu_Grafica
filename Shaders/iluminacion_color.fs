#version 330 core

in vec3 our_normal;//se agrego esta linea
in vec3 fragPos;//se agrego esta linea

//uniform vec4 ourColor; 
out vec4 color;

struct LightPosition{
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform vec4 ourColor;
uniform LightPosition light;
uniform vec3 viewPos;

void main()
{
    vec3 ambient = light.ambient * vec3(ourColor);
	vec3 Normal = normalize(our_normal);//se agrego esta linea
	vec3 lightDirection = normalize(light.position- fragPos);//se agrego esta linea
	float diff = max(dot(Normal, lightDirection), 0.0);//se agrego esta linea
	vec3 diffuse = diff * light.diffuse * vec3(ourColor);//se agrego esta linea

	vec3 r = reflect(- lightDirection, Normal);
	vec3 viewPos = normalize(viewPos - fragPos);
	float spec = pow(max(dot(r, viewPos), 0.0), 32.0);// se agregaron estas lineas
	vec3 specular = spec * light.specular * vec3(ourColor);
	
	color = vec4(ambient + diffuse + specular,1.0);
}
