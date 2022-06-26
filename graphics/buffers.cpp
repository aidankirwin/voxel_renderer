#include "buffers.h"
using namespace std;

void create_vao(GLuint& thisVAO) {
    glGenVertexArrays(1, &thisVAO);
    glBindVertexArray(thisVAO);
}

void delete_vao(GLuint& thisVAO) {
    glDeleteVertexArrays(1, &thisVAO);
}

void vao_attrib(GLuint index, GLint size, size_t offset) {
    // Linking vertex attributes
    glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(offset * sizeof(float)));
    glEnableVertexAttribArray(index);
}

void vao_bind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void delete_vbo(GLuint& buffer) {
    glDeleteBuffers(1, &buffer);
}