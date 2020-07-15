#include "Sprite.h"
#include <iostream>
#include "Vertex.h"
#include <cstddef>
#include "ResourceManager.h"
namespace GameEngine {
	Sprite::Sprite() {
		_vboiID = 0;
	}

	Sprite::~Sprite() {
		if (_vboiID == 0)
			glDeleteBuffers(1, &_vboiID);
	}

	void Sprite::init(float x, float y, float width, float height, std::string texturePath) {
		_x = x;
		_y = y;
		_width = width;
		_height = height;

		_texture = ResourceManager::getTexture(texturePath);

		if (_vboiID == 0)
			glGenBuffers(1, &_vboiID);				//create vertex ID buffer

		Vertex vertexData[6];


		vertexData[0].setPosition(x + width, y + height);
		vertexData[0].setUV(1.0f, 1.0f);

		vertexData[1].setPosition(x, y + height);
		vertexData[1].setUV(0.0f, 1.0f);

		vertexData[2].setPosition(x, y);
		vertexData[2].setUV(0.0f, 0.0f);

		vertexData[3].setPosition(x, y);
		vertexData[3].setUV(0.0f, 0.0f);

		vertexData[4].setPosition(x + width, y);
		vertexData[4].setUV(1.0f, 0.0f);

		vertexData[5].setPosition(x + width, y + height);
		vertexData[5].setUV(1.0f, 1.0f);


		for (int i = 0; i < 6; i++) {
			vertexData[4].setColor(255, 0, 255, 255);

		}
		vertexData[4].setColor(0, 0, 255, 255);
		vertexData[4].setColor(0, 255, 0, 255);



		glBindBuffer(GL_ARRAY_BUFFER, _vboiID); //sets buffer active and binds
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, 0); //unbind buffer
	}


	void Sprite::draw() {

		glBindTexture(GL_TEXTURE_2D, _texture.id);


		glBindBuffer(GL_ARRAY_BUFFER, _vboiID);

		glEnableVertexAttribArray(0);   //sets location
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		//position attribute pointer
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position)); //finds position of vertex data in buffer ID //position attribute pointer
		//color attribute pointer
		glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color)); //color attribute pointer
		//UV attribute pointer
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
		glDrawArrays(GL_TRIANGLES, 0, 6); //draws arrays

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Sprite::changeTexture(std::string texturePath) {
		_texture = ResourceManager::getTexture(texturePath);
	}
}