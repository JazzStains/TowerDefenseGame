#pragma once
#include <string>
#include <GL/glew.h>
namespace GameEngine {
	class GLSLProgram
	{
	public:
		GLSLProgram();
		~GLSLProgram();

		void compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath); //read shaders from file and compile

		void linkShaders();

		void addAttribute(const std::string& attributeName);

		void use();

		void unuse();

		GLint getUniformLocation(const std::string& uniformName);

	private:

		int _numAttributes;

		void compileShader(const std::string& filePath, GLuint id);

		GLuint _programID; //id that refers to the program
		GLuint _vertexShaderID;
		GLuint _fragmentShaderID;

	};
}

