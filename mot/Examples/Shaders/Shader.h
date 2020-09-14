#pragma once
#include <iostream>
#include <fstream>
#include <string>

#include <GL/glew.h>

struct Shader
{
	GLuint ShaderProgram;
	Shader(const std::string& vsPath, const std::string& fsPath)
	{
		std::ifstream vShaderFile(vsPath);
		if(!vShaderFile.is_open())
		{
			std::cerr << "Failed to load vertex shader" << std::endl;
			terminate();
		}
		vShaderFile.seekg(0, std::ios::end);
		std::string vertexCode;
		vertexCode.resize(vShaderFile.tellg());
		vShaderFile.seekg(0);
		vShaderFile.read(vertexCode.data(), vertexCode.size());

		std::ifstream fShaderFile(fsPath);
		if (!fShaderFile.is_open())
		{
			std::cerr << "Failed to load fragment shader" << std::endl;
			terminate();
		}
		fShaderFile.seekg(0, std::ios::end);
		std::string fragmentCode;
		fragmentCode.resize(fShaderFile.tellg());
		fShaderFile.seekg(0);
		fShaderFile.read(fragmentCode.data(), fragmentCode.size());

		const GLchar* vShaderCode = vertexCode.c_str();
		const GLchar* fShaderCode = fragmentCode.c_str();

		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vShaderCode, nullptr);
		glCompileShader(vertexShader);

		GLint success;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		GLchar infoLog[1024];
		if (!success)
		{
			glGetShaderInfoLog(vertexShader, sizeof(infoLog), nullptr, infoLog);
			std::cerr << "Error compiling shader type " << GL_VERTEX_SHADER << ": " << infoLog << std::endl;
		}

		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fShaderCode, nullptr);
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragmentShader, sizeof(infoLog), nullptr, infoLog);
			std::cerr << "Error compiling shader type " << GL_FRAGMENT_SHADER << ": " << infoLog << std::endl;
		}

		ShaderProgram = glCreateProgram();
		glAttachShader(ShaderProgram, vertexShader);
		glAttachShader(ShaderProgram, fragmentShader);
		glLinkProgram(ShaderProgram);
		glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(ShaderProgram, sizeof(infoLog), nullptr, infoLog);
			std::cerr << "Error linking shader program: " << infoLog << std::endl;
		}
		glValidateProgram(ShaderProgram);

		// Delete the shaders as they're linked into our program now and no longer necessery
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

	void Use() const
	{
		glUseProgram(ShaderProgram);
	}
};


