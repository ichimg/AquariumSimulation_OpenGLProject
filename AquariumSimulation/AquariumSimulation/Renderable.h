#ifndef RENDERABLE_H
#define RENDERABLE_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include <random>

#include "Shader.h"

extern std::mt19937 gen;

const float MAX_X = 16.0f;
const float MAX_Y = 7.5f;
const float MAX_Z = 16.0f;
const float MIN_Y = 2.5f;


class Renderable
{
protected:
	glm::mat4 Model;
	float x, y, z;	
	float rx, ry, rz;	
	float sx, sy, sz;	

	unsigned char* TextureData;
	int TextureWidth, TextureHeight, nrChannels;
	unsigned int Texture;

	int VerticesNumber;

	template<class T>
	T random(T min, T max);	

public:
	Renderable();
	virtual ~Renderable() = 0;
	virtual void draw(Shader* sp) = 0;
	virtual void behave() = 0;
	virtual bool loadOBJ(const char* path,
		std::vector < glm::vec3 >& out_vertices,
		std::vector < glm::vec2 >& out_uvs,
		std::vector < glm::vec3 >& out_normals);


};

template<class T>
T Renderable::random(T min, T max)
{
	using dist = std::conditional_t<
		std::is_integral<T>::value,
		std::uniform_int_distribution<T>,
		std::uniform_real_distribution<T>
	>;
	return dist{ min, max }(gen);
}


class Fish : public Renderable
{
private:
	float Velocity;
	float RotateVelocity;
	unsigned int VAO, VBO[3];

	glm::vec3 wantToGo; 
	int rsteps;
	int steps;

	glm::vec2 AnglesBeetwen(glm::vec3 v1, glm::vec3 v2);

public:
	Fish(std::string _s = "norandom", glm::vec3 initialPosition = glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3 initialRotation = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 initialScaling = glm::vec3(1.0f, 1.0f, 1.0f));
	~Fish();
	void draw(Shader* sp);
	void behave();
	void move(glm::vec3 coordinates);
};

class Plant : public Renderable
{
private:
	float location[3];

};

class Other : public Renderable
{
	unsigned int VAO, VBO[3];
	float location[3];

public:
	Other(std::string element_s, glm::vec3 initialPosition);
	void draw(Shader* sp);
	void behave();

};

class Rock : public Renderable
{
private:
	unsigned int VAO, VBO[3];
public:
	Rock();
	~Rock();
	void draw(Shader* sp);
	void behave();
};

#endif