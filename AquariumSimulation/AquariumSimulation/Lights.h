#ifndef LIGHTS_H
#define LIGHTS_H
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include "Shader.h"

class DirLight
{
	public:
	glm::vec3 direction;

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

public:
	DirLight();
	~DirLight();
	void apply(Shader* sp);
};

class SpotLight
{
	public:
	glm::vec3 position;
	glm::vec3 direction;

	float cutOff;
	float outerCutOff;

	float constant;
	float linear;
	float quadratic;

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

public:
	SpotLight();
	~SpotLight();
	void apply(Shader* sp);
};


#endif