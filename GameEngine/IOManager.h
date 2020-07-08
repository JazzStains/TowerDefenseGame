#pragma once
#include <vector>
#include <string>
namespace GameEngine {
	class IOManager  //gives basic file operations
	{
	public:
		static bool readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer);
	};

}