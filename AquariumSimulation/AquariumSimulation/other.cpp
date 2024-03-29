#include "Renderable.h"




#include "stb_image.h"




Other::Other(std::string element_s, glm::vec3 initialPosition)

{

	Model = glm::mat4(1.0f);




	//steps = 0;




	std::vector< glm::vec3 > vertices;

	std::vector< glm::vec2 > uvs;

	std::vector< glm::vec3 > normals; // Won't be used at the moment.

	std::string path_obj = "Models/" + element_s +".obj";

	bool res = loadOBJ(path_obj.c_str(), vertices, uvs, normals);

	sx = 0.2f; sy = 0.2f; sz = 0.2f;


	VerticesNumber = vertices.size() * 3;




	glGenVertexArrays(1, &VAO);

	glGenBuffers(3, VBO);




	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);

	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);




	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(0);




	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);

	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);




	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(2);




	glGenTextures(1, &Texture);

	glBindTexture(GL_TEXTURE_2D, Texture);

	// set the texture wrapping parameters

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// set texture filtering parameters

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	std::string path_tex = "Models/" + element_s + ".jpg";

	TextureData = stbi_load(path_tex.c_str(), &TextureWidth, &TextureHeight, &nrChannels, 0);

	if (TextureData)

	{

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TextureWidth, TextureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureData);

		glGenerateMipmap(GL_TEXTURE_2D);

	}

	else

	{

		std::cout << "Failed to load texture" << std::endl;

	}

	stbi_image_free(TextureData);

}




void Other::draw(Shader* sp)

{

	sp->use();

	this->Model = glm::mat4(1.0f);

	this->Model = glm::translate(this->Model, glm::vec3(x, y, z));

	this->Model = glm::scale(this->Model, glm::vec3(sx, sy, sz));

	sp->setMat4("model", this->Model);

	glActiveTexture(GL_TEXTURE0);

	glBindTexture(GL_TEXTURE_2D, Texture);

	glBindVertexArray(VAO);

	glDrawArrays(GL_TRIANGLES, 0, VerticesNumber);

}




void Other::behave()

{




}