#ifndef FLOOR_H
#define FLOOR_H

#include "Shader.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>




const int LENGTH = 10;	//Length of floor object
const int WIDTH = 10;	//Width of floor object
const unsigned int VERTEXCOUNT = 4;	//Number of Vertices
const unsigned int INDEXCOUNT = 6;	//Number of Indices

class Floor
{
private:
	glm::mat4 Model;
	int Length; //X Coordinate
	int Width;	//Z Coordinate
	static int VertexCount;
	static int IndexCount;
	static float Vertices[];
	static float Colors[];
	static float TextureVertices[];
	static unsigned int Indexes[];
	unsigned int VAO, VBO[3], EBO;

	unsigned char* data;
	int TextureWidth, TextureHeight, nrChannels;
	unsigned int Texture;
	enum Texture_Number
	{
		sand,
		sand2
	};

public:
	Floor();	//default constructor
	~Floor();	//default destructor
	void draw(Shader* sp);	//draw Floor in loop function
};

#endif