#include "SpriteBatch.h"
#include <algorithm>

namespace GameEngine {



	SpriteBatch::SpriteBatch()
	{
		_vbo = 0;
		_vao = 0;
		_delay = 5;

	}

	SpriteBatch::~SpriteBatch() {

	}

	void SpriteBatch::init() {
		createVertexArray();

	}
	void SpriteBatch::begin(GlyphSortType sortType) {
		_sortType = sortType;
		_renderBatches.clear();
		_glyphs.clear();
	}
	void SpriteBatch::end() {
		sortGlyphs();
		createRenderBatches();

	}

	void SpriteBatch::draw(const glm::vec4& destRect, const  glm::vec4& uvRect, GLuint texture, float depth, const ColorRGBA8& color) {
		Glyph* newGlyph;
		newGlyph = new Glyph;

		newGlyph->texture = texture;
		newGlyph->depth = depth;

		newGlyph->topLeft.color = color;
		newGlyph->topLeft.setPosition(destRect.x, destRect.y + destRect.w);
		newGlyph->topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);

		newGlyph->bottomLeft.color = color;
		newGlyph->bottomLeft.setPosition(destRect.x, destRect.y);
		newGlyph->bottomLeft.setUV(uvRect.x, uvRect.y);

		newGlyph->bottomRight.color = color;
		newGlyph->bottomRight.setPosition(destRect.x + destRect.z, destRect.y);
		newGlyph->bottomRight.setUV(uvRect.x + uvRect.z, uvRect.y);

		newGlyph->topRight.color = color;
		newGlyph->topRight.setPosition(destRect.x + destRect.z, destRect.y + destRect.w);
		newGlyph->topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);

		_glyphs.push_back(newGlyph);


	}
	void SpriteBatch::renderBatch() {
		glBindVertexArray(_vao);

		for (int i = 0; i < _renderBatches.size(); i++) {
			glBindTexture(GL_TEXTURE_2D, _renderBatches[i].texture);
			glDrawArrays(GL_TRIANGLES, _renderBatches[i].offset, _renderBatches[i].numVertices);
		}
		glBindVertexArray(0);
	}

	void SpriteBatch::createRenderBatches() {

		std::vector <Vertex> vertices;
		//tell vertices vector how big it is going to be
		vertices.resize(_glyphs.size() * 6);

		if (_glyphs.empty()) {
			return;
		}

		int offset = 0;

		int currentVertex = 0;

		//add to render batches
		_renderBatches.emplace_back(offset, 6, _glyphs[0]->texture);
		vertices[currentVertex++] = _glyphs[0]->topLeft;
		vertices[currentVertex++] = _glyphs[0]->bottomLeft;
		vertices[currentVertex++] = _glyphs[0]->bottomRight;
		vertices[currentVertex++] = _glyphs[0]->bottomRight;
		vertices[currentVertex++] = _glyphs[0]->topRight;
		vertices[currentVertex++] = _glyphs[0]->topLeft;
		offset += 6;

		for (int cg = 1; cg < _glyphs.size(); cg++) {
			//increase size of render batch
			if (_glyphs[cg]->texture != _glyphs[cg - 1]->texture)
				_renderBatches.emplace_back(offset, 6, _glyphs[cg]->texture);
			else
				_renderBatches.back().numVertices += 6;

			vertices[currentVertex++] = _glyphs[cg]->topLeft;
			vertices[currentVertex++] = _glyphs[cg]->bottomLeft;
			vertices[currentVertex++] = _glyphs[cg]->bottomRight;
			vertices[currentVertex++] = _glyphs[cg]->bottomRight;
			vertices[currentVertex++] = _glyphs[cg]->topRight;
			vertices[currentVertex++] = _glyphs[cg]->topLeft;
			offset += 6;
		}
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		//orphan the buffer
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
		//upload the data
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());
		//unbind buffer
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void SpriteBatch::createVertexArray() {
		if (_vao == 0)
			glGenVertexArrays(1, &_vao);

		glBindVertexArray(_vao);

		if (_vbo == 0)
			glGenBuffers(1, &_vbo);

		glBindBuffer(GL_ARRAY_BUFFER, _vbo);

		glEnableVertexAttribArray(0);   //sets location
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		//position attribute pointer
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position)); //finds position of vertex data in buffer ID //position attribute pointer
		//color attribute pointer
		glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color)); //color attribute pointer
		//UV attribute pointer
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

		//unbind
		glBindVertexArray(0);

	}

	void SpriteBatch::sortGlyphs() {
		switch (_sortType) {
		case GlyphSortType::BACK_TO_FRONT:
			std::stable_sort(_glyphs.begin(), _glyphs.end(), compareBackToFront);
			break;

		case GlyphSortType::FRONT_TO_BACK:
			std::stable_sort(_glyphs.begin(), _glyphs.end(), compareFrontToBack);
			break;
		case GlyphSortType::TEXTURE:
			std::stable_sort(_glyphs.begin(), _glyphs.end(), compareTexture);
			break;
		}
	}

	bool SpriteBatch::compareFrontToBack(Glyph* a, Glyph* b) {
		return (a->depth < b->depth);
	}
	bool SpriteBatch::compareBackToFront(Glyph* a, Glyph* b) {
		return (a->depth > b->depth);
	}
	bool SpriteBatch::compareTexture(Glyph* a, Glyph* b) {
		return (a->texture < b->texture);
	}

	bool SpriteBatch::update() {
		if (_lifeTime == 0) {
			return true;
		}
		return false;
	}

}
