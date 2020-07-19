#pragma once
#include <GL/glew.h>
#include "Vertex.h"
#include <glm/glm.hpp>
#include <vector>

namespace GameEngine {
	
	enum class GlyphSortType {
		NONE,
		FRONT_TO_BACK,
		BACK_TO_FRONT,
		TEXTURE
	};

	struct Glyph {

		GLuint texture;
		float depth;

		Vertex topLeft;
		Vertex bottomLeft;
		Vertex topRight;
		Vertex bottomRight;
	};

	class RenderBatch { 
	public:
		RenderBatch(GLuint Offset, GLuint NumVertices, GLuint Texture) {
			offset = Offset;
			numVertices = NumVertices;
			texture = Texture;
		}
		GLuint offset;
		GLuint numVertices;
		GLuint texture;
	};
	class SpriteBatch
	{
	public: 
		SpriteBatch();
		~SpriteBatch();

		void init();
		void begin(GlyphSortType sortType = GlyphSortType::TEXTURE);
		void end();
		bool update();

		void draw(const glm::vec4& destRect,const  glm::vec4& uvRect, GLuint texture,float depth, const ColorRGBA8& color);
		void renderBatch();

	private:
		void createRenderBatches();
		void createVertexArray();
		void sortGlyphs();

		//vertex buffer object
		GLuint _vbo;

		GLuint _vao;
		std::vector<Glyph*> _glyphs;
		std::vector<RenderBatch> _renderBatches;
		int _lifeTime;
		
		int _delay;

		GlyphSortType _sortType;

		static bool compareFrontToBack(Glyph* a, Glyph* b);
		static bool compareBackToFront(Glyph* a, Glyph* b);
		static bool compareTexture(Glyph* a, Glyph* b);

	};

}
