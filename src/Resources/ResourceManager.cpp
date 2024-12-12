#include "ResourceManager.h"
#include "../Renderer/ShaderProgram.h"	

#include <sstream>
#include <fstream>
#include <iostream>

ResourceManager::ResourceManager(const std::string& executablePath)
{
	size_t found = executablePath.find_last_of("/\\");
	m_path = executablePath.substr(0, found);
}

std::string ResourceManager::getFileString(const std::string& relativeFilePath) const
{
	std::fstream file;
	file.open(m_path + "/" + relativeFilePath.c_str(), std::ios::in | std::ios::binary);
	if (!file.is_open())
	{
		std::cerr << "Failed to open file: " << relativeFilePath << std::endl;
		return std::string{};
	}

	std::stringstream buffer;
	buffer << file.rdbuf();
	return buffer.str();
}

std::shared_ptr<Renderer::ShaderProgram> ResourceManager::loadShaders(const std::string& shaderName, const std::string& vertexShaderPath, const std::string fragmentShaderPath)
{
	std::string vertexString = getFileString(vertexShaderPath);
	if (vertexString.empty())
	{
		std::cerr << "Vertex Shader is empty!" << std::endl;
		return nullptr;
	}

	std::string fragmentString = getFileString(fragmentShaderPath);
	if (fragmentString.empty())
	{
		std::cerr << "Fragment Shader is empty" << std::endl;
		return nullptr;
	}

	std::shared_ptr<Renderer::ShaderProgram>& newShader = m_shaderPrograms.emplace(shaderName, std::make_shared<Renderer::ShaderProgram>(vertexString, fragmentString)).first->second;
	if (newShader->isCompiled())
	{
		return newShader;
	}

	std::cerr << "Can't load shader program: \n"
		<< "Vertex: " << vertexShaderPath << "\n"
		<< "Fragment: " << fragmentShaderPath << std::endl;

	return nullptr;
}

std::shared_ptr<Renderer::ShaderProgram> ResourceManager::getShaderProgram(std::string& shaderName)
{
	ShaderProgramsMap::const_iterator it = m_shaderPrograms.find(shaderName);
	if (it != m_shaderPrograms.end())
	{
		return it->second;
	}

	std::cerr << "Can't find shader program: " << shaderName << std::endl;
	return nullptr;
}