#pragma once
#ifndef TEXTURES_H
#define TEXTURES_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

using namespace std;

void load_tex(const char* texturePath, GLuint& texture);
void bind_tex(GLuint& texture);

#endif