#pragma once

#ifndef BUFFERS_H
#define BUFFERS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void create_vao(GLuint& thisVAO);
void delete_vao(GLuint& thisVAO);
void vao_attrib(GLuint index, GLint size, size_t offset);
void vao_bind();
void delete_vbo(GLuint& buffer);

template<typename T, size_t S>
void create_vbo(GLuint& buffer, T(&_indices)[S], GLenum target) {
    glGenBuffers(1, &buffer);
    glBindBuffer(target, buffer);
    glBufferData(target, sizeof(_indices), _indices, GL_STATIC_DRAW);
}

#endif
