#pragma once

#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

class shader {
private:
	void error(string type);
public:
	shader();
	void create(const char* vertexPath, const char* fragmentPath);
	void destroy();
	void destroy_program();
	void use();
	void set_float(const string& name, float value) const;
	void set_int(const string& name, int value) const;
	void set_bool(const string& name, bool value) const;

	void set_vec2(const std::string& name, const glm::vec2& value) const;
	void _set_vec2(const std::string& name, float x, float y) const;

	void set_vec3(const std::string& name, const glm::vec3& value) const;
	void _set_vec3(const std::string& name, float x, float y, float z) const;

	void set_vec4(const std::string& name, const glm::vec4& value) const;
	void _set_vec4(const std::string& name, float x, float y, float z, float w);

	void set_mat2(const std::string& name, const glm::mat2& mat) const;

	void set_mat3(const std::string& name, const glm::mat3& mat) const;

	void set_mat4(const std::string& name, const glm::mat4& mat) const;
};


#endif