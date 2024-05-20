#version 330 core

out vec4 FragColor;

in vec3 Position;
in vec3 Normal;
in vec2 UV;

uniform sampler2D Diffuse0;
uniform sampler2D Specular0;
uniform vec4 LightColor;
uniform vec3 LightPosition;
uniform vec3 CameraPosition;


vec4 pointLight()
{	
	vec3 lightVec = LightPosition - Position;

	float dist = length(lightVec);
	float a = 3.0;
	float b = 0.7;
	float inten = 1.0f / (a * dist * dist + b * dist + 1.0f);

	float ambient = 0.20f;

	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightVec);
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	float specularLight = 0.50f;
	vec3 viewDirection = normalize(CameraPosition - Position);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
	float specular = specAmount * specularLight;

	return (texture(Diffuse0, UV) * (diffuse * inten + ambient) + texture(Specular0, UV).r * specular * inten) * LightColor;
}

vec4 direcLight()
{
	float ambient = 0.20f;

	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(vec3(1.0f, 1.0f, 0.0f));
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	float specularLight = 0.50f;
	vec3 viewDirection = normalize(CameraPosition - Position);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
	float specular = specAmount * specularLight;

	return (texture(Diffuse0, UV) * (diffuse + ambient) + texture(Specular0, UV).r * specular) * LightColor;
}

vec4 spotLight()
{
	float outerCone = 0.90f;
	float innerCone = 0.95f;

	float ambient = 0.20f;

	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(LightPosition - Position);
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	float specularLight = 0.50f;
	vec3 viewDirection = normalize(CameraPosition - Position);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
	float specular = specAmount * specularLight;

	float angle = dot(vec3(0.0f, -1.0f, 0.0f), -lightDirection);
	float inten = clamp((angle - outerCone) / (innerCone - outerCone), 0.0f, 1.0f);

	return (texture(Diffuse0, UV) * (diffuse * inten + ambient) + texture(Specular0, UV).r * specular * inten) * LightColor;
}


void main()
{
	FragColor = spotLight();
}