#pragma once

#include <glad/glad.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

class Shader
{
   public:
	GLuint ID;

	Shader() = delete;

	Shader(const char* vertexPath, const char* fragmentPath)
	{
		GLuint vertex   = loadShader(vertexPath, GL_VERTEX_SHADER);
		GLuint fragment = loadShader(fragmentPath, GL_FRAGMENT_SHADER);

		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);

		int success;
		glGetProgramiv(ID, GL_LINK_STATUS, &success);
		if (!success)
		{
			char infoLog[512];
			glGetProgramInfoLog(ID, sizeof(infoLog), NULL, infoLog);

			std::stringstream msg;
			msg << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << "\n";

			throw std::runtime_error(msg.str());
		}

		glDeleteShader(vertex);
		glDeleteShader(fragment);
	};

	~Shader() { glDeleteProgram(ID); }

	static GLuint loadShader(const char* path, GLenum shaderType)
	{
		std::ifstream shaderFile;
		shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		shaderFile.open(path);

		std::stringstream shaderStream;
		shaderStream << shaderFile.rdbuf();
		shaderFile.close();

		std::string shaderCode  = shaderStream.str();
		const char* cShaderCode = shaderCode.c_str();

		GLuint id = glCreateShader(shaderType);
		glShaderSource(id, 1, &cShaderCode, NULL);
		glCompileShader(id);

		int success;
		glGetShaderiv(id, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			char infoLog[512];
			glGetShaderInfoLog(id, sizeof(infoLog), NULL, infoLog);

			std::string type;
			switch (shaderType)
			{
				case GL_VERTEX_SHADER:
					type = "FRAGMENT";
					break;
				case GL_FRAGMENT_SHADER:
					type = "VERTEX";
					break;
				case GL_GEOMETRY_SHADER:
					type = "GEOMETRY";
					break;
				case GL_COMPUTE_SHADER:
					type = "COMPUTE";
					break;
				default:
					type = "UNKNOWN";
					break;
			}

			std::stringstream msg;
			msg << "ERROR::SHADER::" << type << "COMPILATION_FAILED\n" << infoLog << "\n";

			throw std::runtime_error(msg.str());
		}

		return id;
	};

	void use() { glUseProgram(ID); };

	void setBool(const std::string& name, bool value) const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
	};

	void setInt(const std::string& name, int value) const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	};

	void setFloat(const std::string& name, float value) const
	{
		glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
	};
};