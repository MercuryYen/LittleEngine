#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <map>
#include "../DLC/Light.h"
using namespace std;


class Shader
{
public:
	string ShaderName;
	static map<string,GLuint> Programs;
	enum Type {
		NULL_SHADER = (0),
		VERTEX_SHADER = (1 << 0),
		FRAGMENT_SHADER = (1 << 1),
		TESS_CONTROL_SHADER = (1 << 2),
		TESS_EVALUATION_SHADER = (1 << 3),
		GEOMETRY_SHADER = (1 << 4),

	};
	//DEFINE_ENUM_FLAG_OPERATORS(Type);

	Type type = NULL_SHADER;
	// Constructor generates the shader on the fly
	Shader(const string _ShaderName, const GLchar* vert, const GLchar* frag, const GLchar* tesc = nullptr, const GLchar* tese = nullptr, const GLchar* geom = nullptr)
	{
		ShaderName = _ShaderName;
		if (Programs.find(_ShaderName) != Programs.end()) {
			return;
		}
		std::vector<GLuint> shaders;
		if (vert)
		{
			shaders.push_back(this->compileShader(GL_VERTEX_SHADER, this->readCode(vert).c_str()));
			this->type = (Shader::Type)(this->type | Type::VERTEX_SHADER);
		}
		if (tesc)
		{
			shaders.push_back(this->compileShader(GL_TESS_CONTROL_SHADER, this->readCode(tesc).c_str()));
			this->type = (Shader::Type)(this->type | Type::TESS_CONTROL_SHADER);
		}
		if (tese)
		{
			shaders.push_back(this->compileShader(GL_TESS_EVALUATION_SHADER, this->readCode(tese).c_str()));
			this->type = (Shader::Type)(this->type | Type::TESS_EVALUATION_SHADER);
		}
		if (geom)
		{
			shaders.push_back(this->compileShader(GL_GEOMETRY_SHADER, this->readCode(geom).c_str()));
			this->type = (Shader::Type)(this->type | Type::GEOMETRY_SHADER);
		}
		if (frag)
		{
			shaders.push_back(this->compileShader(GL_FRAGMENT_SHADER, this->readCode(frag).c_str()));
			this->type = (Shader::Type)(this->type | Type::FRAGMENT_SHADER);
		}
		// Shader Program
		GLint success;
		GLchar infoLog[512];
		Programs[ShaderName] = glCreateProgram();

		for (GLuint shader : shaders)
			glAttachShader(Programs[ShaderName], shader);

		glLinkProgram(Programs[ShaderName]);
		// Print linking errors if any
		glGetProgramiv(Programs[ShaderName], GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(Programs[ShaderName], 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		}

		for (GLuint shader : shaders)
			glDeleteShader(shader);
	}
	// Uses the current shader
	virtual void Use()
	{
		glUseProgram(Programs[ShaderName]);
	}

	GLuint getProgram() {
		return Programs[ShaderName];
	}

	//###################################################################################### Extra
protected:
	void setBool(const std::string& name, bool value) const
	{
		glUniform1i(glGetUniformLocation(Programs[ShaderName], name.c_str()), (int)value);
	}
	// ------------------------------------------------------------------------
	void setInt(const std::string& name, int value) const
	{
		glUniform1i(glGetUniformLocation(Programs[ShaderName], name.c_str()), value);
	}
	// ------------------------------------------------------------------------
	void setFloat(const std::string& name, float value) const
	{
		glUniform1f(glGetUniformLocation(Programs[ShaderName], name.c_str()), value);
	}
	// ------------------------------------------------------------------------
	void setVec2(const std::string& name, const glm::vec2& value) const
	{
		glUniform2fv(glGetUniformLocation(Programs[ShaderName], name.c_str()), 1, &value[0]);
	}
	void setVec2(const std::string& name, float x, float y) const
	{
		glUniform2f(glGetUniformLocation(Programs[ShaderName], name.c_str()), x, y);
	}
	// ------------------------------------------------------------------------
	void setVec3(const std::string& name, const glm::vec3& value) const
	{
		glUniform3fv(glGetUniformLocation(Programs[ShaderName], name.c_str()), 1, &value[0]);
	}
	void setVec3(const std::string& name, float x, float y, float z) const
	{
		glUniform3f(glGetUniformLocation(Programs[ShaderName], name.c_str()), x, y, z);
	}
	// ------------------------------------------------------------------------
	void setVec4(const std::string& name, const glm::vec4& value) const
	{
		glUniform4fv(glGetUniformLocation(Programs[ShaderName], name.c_str()), 1, &value[0]);
	}
	void setVec4(const std::string& name, float x, float y, float z, float w)
	{
		glUniform4f(glGetUniformLocation(Programs[ShaderName], name.c_str()), x, y, z, w);
	}
	// ------------------------------------------------------------------------
	void setMat2(const std::string& name, const glm::mat2& mat) const
	{
		glUniformMatrix2fv(glGetUniformLocation(Programs[ShaderName], name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}
	// ------------------------------------------------------------------------
	void setMat3(const std::string& name, const glm::mat3& mat) const
	{
		glUniformMatrix3fv(glGetUniformLocation(Programs[ShaderName], name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}
	// ------------------------------------------------------------------------
	void setMat4(const std::string& name, const glm::mat4& mat) const
	{
		glUniformMatrix4fv(glGetUniformLocation(Programs[ShaderName], name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}


	//####################### LIGHT
	void setPointLightNum_(string uniformName, int num) {
		this->setInt(uniformName, num);
	}
	void setSpotLightNum_(string uniformName, int num) {
		this->setInt(uniformName, num);
	}
	void setDirectLight_(string uniformName, DirectLight dirLight) {

		this->setVec3((uniformName + direction).c_str(), dirLight.direction);
		this->setFloat((uniformName + ambient).c_str(), dirLight.ambient);
		this->setFloat((uniformName + diffuse).c_str(), dirLight.diffuse);
		this->setFloat((uniformName + specular).c_str(), dirLight.specular);

	}

	void setPointLight_(string uniformName, PointLight* pointLights, int number) {
		for (int i = 0; i < number; i++) {
			string index;
			index = "[" + to_string(i) + "]";
			setVec3((uniformName + index + position).c_str(), pointLights[i].position);
			setFloat((uniformName + index + ambient).c_str(), pointLights[i].ambient);
			setFloat((uniformName + index + diffuse).c_str(), pointLights[i].diffuse);
			setFloat((uniformName + index + specular).c_str(), pointLights[i].specular);
			setFloat((uniformName + index + constant).c_str(), pointLights[i].constant);
			setFloat((uniformName + index + linear).c_str(), pointLights[i].linear);
			setFloat((uniformName + index + quadratic).c_str(), pointLights[i].quadratic);
		}
	}

	void setSpotLight_(string uniformName, SpotLight* spotLights, int number) {
		for (int i = 0; i < number; i++) {
			string index;
			index = "[" + to_string(i) + "]";
			setVec3((uniformName + index + position).c_str(), spotLights[i].position);
			setVec3((uniformName + index + direction).c_str(), spotLights[i].direction);
			setFloat((uniformName + index + ambient).c_str(), spotLights[i].ambient);
			setFloat((uniformName + index + diffuse).c_str(), spotLights[i].diffuse);
			setFloat((uniformName + index + specular).c_str(), spotLights[i].specular);
			setFloat((uniformName + index + constant).c_str(), spotLights[i].constant);
			setFloat((uniformName + index + linear).c_str(), spotLights[i].linear);
			setFloat((uniformName + index + quadratic).c_str(), spotLights[i].quadratic);
			setFloat((uniformName + index + cutOff).c_str(), spotLights[i].cutOff);
			setFloat((uniformName + index + outerCutOff).c_str(), spotLights[i].outerCutOff);
		}
	}
private:
	std::string readCode(const GLchar* path)
	{
		std::string code;
		std::ifstream shader_file;
		// ensures ifstream objects can throw exceptions:
		shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			// Open files
			shader_file.open(path);
			//if (!vShaderFile)std::cout << vertexPath << " fail to open" << std::endl;
			std::stringstream shader_stream;
			// Read file's buffer contents into streams
			shader_stream << shader_file.rdbuf();
			// close file handlers
			shader_file.close();
			// Convert stream into string
			code = shader_stream.str();
		}
		catch (std::ifstream::failure e)
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
			std::cout << path << std::endl;
		}
		return code;
	}
	GLuint compileShader(GLenum shader_type, const char* code)
	{
		GLuint shader_number;
		GLint success;
		GLchar infoLog[512];
		// Vertex Shader
		shader_number = glCreateShader(shader_type);
		glShaderSource(shader_number, 1, &code, NULL);
		glCompileShader(shader_number);
		// Print compile errors if any
		glGetShaderiv(shader_number, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader_number, 512, NULL, infoLog);
			if (shader_type == GL_VERTEX_SHADER)
				std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
			else if (shader_type == GL_TESS_CONTROL_SHADER)
				std::cout << "ERROR::SHADER::TESS_CONTROL::COMPILATION_FAILED\n" << infoLog << std::endl;
			else if (shader_type == GL_TESS_EVALUATION_SHADER)
				std::cout << "ERROR::SHADER::TESS_EVALUATION::COMPILATION_FAILED\n" << infoLog << std::endl;
			else if (shader_type == GL_GEOMETRY_SHADER)
				std::cout << "ERROR::SHADER::GEOMETRY::COMPILATION_FAILED\n" << infoLog << std::endl;
			else if (shader_type == GL_FRAGMENT_SHADER)
				std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		}
		return shader_number;
	}

	//###### ABOUT LIGHT
	string direction = ".direction";
	string position = ".position";
	string ambient = ".ambient";
	string diffuse = ".diffuse";
	string specular = ".specular";
	string constant = ".constant";
	string linear = ".linear";
	string quadratic = ".quadratic";
	string cutOff = ".cutOff";
	string outerCutOff = ".outerCutOff";
};

#endif