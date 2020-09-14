#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <GL/glew.h>

struct Shader
{
	GLuint ShaderProgram;
	Shader(const std::string &vsPath, const std::string &fsPath)
	{
		        // 1. Retrieve the vertex/fragment source code from filePath
        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        // ensures ifstream objects can throw exceptions:
        vShaderFile.exceptions ( std::ifstream::badbit );
        fShaderFile.exceptions ( std::ifstream::badbit );
        try
        {
            // Open files
            vShaderFile.open( vsPath );
            fShaderFile.open( fsPath );
            std::stringstream vShaderStream, fShaderStream;
            // Read file's buffer contents into streams
            vShaderStream << vShaderFile.rdbuf( );
            fShaderStream << fShaderFile.rdbuf( );
            // close file handlers
            vShaderFile.close( );
            fShaderFile.close( );
            // Convert stream into string
            vertexCode = vShaderStream.str( );
            fragmentCode = fShaderStream.str( );
        }
        catch (...)
        {
            std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
        }
        const GLchar *vShaderCode = vertexCode.c_str( );
        const GLchar *fShaderCode = fragmentCode.c_str( );
		
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vShaderCode, nullptr);
		glCompileShader(vertexShader);

		GLint success;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		GLchar infoLog[1024];
		if(!success)
		{
			glGetShaderInfoLog(vertexShader, sizeof(infoLog), nullptr, infoLog);
			std::cerr << "Error compiling shader type "<< GL_VERTEX_SHADER << ": " << infoLog << std::endl;
		}

		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fShaderCode, nullptr);
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if(!success)
		{
			glGetShaderInfoLog(fragmentShader, sizeof(infoLog), nullptr, infoLog);
			std::cerr << "Error compiling shader type "<< GL_FRAGMENT_SHADER << ": " << infoLog << std::endl;
		}

		ShaderProgram = glCreateProgram();
		glAttachShader(ShaderProgram, vertexShader);
		glAttachShader(ShaderProgram, fragmentShader);
		glLinkProgram(ShaderProgram);
		glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &success);
		if(!success)
		{
			glGetProgramInfoLog(ShaderProgram, sizeof(infoLog), nullptr, infoLog);
			std::cerr << "Error linking shader program: " << infoLog << std::endl;
		}
		glValidateProgram(ShaderProgram);

		// Delete the shaders as they're linked into our program now and no longer necessery
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

	void Use()
	{
		glUseProgram(ShaderProgram);
	}
};


