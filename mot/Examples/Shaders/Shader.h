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
		// Read vertex shader code from file
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
		const GLchar* vShaderCode = vertexCode.c_str();

		// Read fragment shader code from file
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
		const GLchar* fShaderCode = fragmentCode.c_str();

		// Compile vertex shader
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

		// Compile fragment shader
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fShaderCode, nullptr);
		glCompileShader(fragmentShader);
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragmentShader, sizeof(infoLog), nullptr, infoLog);
			std::cerr << "Error compiling shader type " << GL_FRAGMENT_SHADER << ": " << infoLog << std::endl;
		}

		// Create Shader program
		ShaderProgram = glCreateProgram();
		// Attach compiled shader object to the program object.
		// This is very similar to specifying the list of objects for linking in a makefile.
		// Since we don't have a makefile here we emulate this behavior programatically.
		// Only the attached objects take part of the linking process.
		glAttachShader(ShaderProgram, vertexShader);
		glAttachShader(ShaderProgram, fragmentShader);
		glLinkProgram(ShaderProgram);
		glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(ShaderProgram, sizeof(infoLog), nullptr, infoLog);
			std::cerr << "Error linking shader program: " << infoLog << std::endl;
		}
		// You may ask yourself why do we need to validate a program after it has been successfully linked.
		// The difference is that linking checks for errors based on the combination of shaders while
		// the call above check whether the program can execute given the current pipeline state.
		// In a complex application with multiple shaders and lots of state changes it is better to validate before every draw call.
		// In our simple app we check it just once.
		// Also, you may want to do this check only during development and avoid this overhead in the final product.
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


