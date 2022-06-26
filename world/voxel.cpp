#include "voxel.h"

using namespace std;

GLuint VAO, VBO, EBO;
GLuint* textures = new GLuint[5];
shader* vshader = new shader();

GLfloat vertices[] = {
    // Position         // Texture Coordinates
    
    // Front
    0.0f, 0.0f, 0.0f,   0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,   1.0f, 0.0f,
    1.0f, 1.0f, 0.0f,   1.0f, 1.0f,
    0.0f, 1.0f, 0.0f,   0.0f, 1.0f,

    // Back
    0.0f, 0.0f, 1.0f,   1.0f, 0.0f,
    1.0f, 0.0f, 1.0f,   0.0f, 0.0f,
    1.0f, 1.0f, 1.0f,   0.0f, 1.0f,
    0.0f, 1.0f, 1.0f,   1.0f, 1.0f,

    // Top
    0.0f, 1.0f, 0.0f,   0.0f, 0.0f,
    0.0f, 1.0f, 1.0f,   0.0f, 1.0f,
    1.0f, 1.0f, 0.0f,   1.0f, 0.0f,
    1.0f, 1.0f, 1.0f,   1.0f, 1.0f,

    // Bottom
    1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
    1.0f, 0.0f, 1.0f,   0.0f, 1.0f,
    0.0f, 0.0f, 0.0f,   1.0f, 0.0f,
    0.0f, 0.0f, 1.0f,   1.0f, 1.0f,

    // Left
    0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
    0.0f, 1.0f, 1.0f,   0.0f, 1.0f,
    0.0f, 0.0f, 0.0f,   1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,   1.0f, 1.0f,

    // Right
    1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
    1.0f, 1.0f, 0.0f,   0.0f, 1.0f,
    1.0f, 0.0f, 1.0f,   1.0f, 0.0f,
    1.0f, 1.0f, 1.0f,   1.0f, 1.0f
};

GLuint indices[] = {
     0,  3,  1,  3,  1,  2, // Front face
     5,  6,  4,  6,  4,  7, // Back face
     8,  9, 10,  9, 10, 11, // Top face
    12, 13, 14, 13, 14, 15, // Bottom face
    16, 17, 18, 17, 18, 19, // Left face
    20, 21, 22, 21, 22, 23  // Right face
};

void gen_voxel() {
    create_vao(VAO);
    create_vbo(VBO, vertices, GL_ARRAY_BUFFER);
    create_vbo(EBO, indices, GL_ELEMENT_ARRAY_BUFFER);
    vao_attrib(0, 3, 0);
    vao_attrib(1, 2, 3);
    vao_bind();
}

void create_voxel_shader() {
    vshader->create("graphics/shader.vs", "graphics/shader.fs");
}

void destroy_voxel_shader() {
    vshader->destroy();
}

void render_voxel(glm::vec3 position) {
    glBindVertexArray(VAO);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    vshader->set_mat4("model", model);
    vshader->use();
}

// It would be better if this was in another file
void render_view(int width, int height) {
    // View
    glm::mat4 projection = shader_projection(width, height);
    vshader->set_mat4("projection", projection);
    glm::mat4 view = view_transform();
    vshader->set_mat4("view", view);
}

void delete_voxel() {
    delete_vao(VAO);
    delete_vbo(VBO);
    delete_vbo(EBO);
    vshader->destroy_program();
}

void init_voxel_tex() {
    load_tex("res/grass_top.png", textures[0]);
    load_tex("res/grass_bottom.png", textures[1]);
    load_tex("res/grass_side.png", textures[2]);
    load_tex("res/stone.png", textures[3]);
    load_tex("res/reftex.png", textures[4]);
}

// This system is pretty ugly
void voxel_tex(int block_ID, int i) {

    switch (block_ID) {
    case 0:
        if (i == 2)
            bind_tex(textures[0]); // grass_top
        else if (i == 3) 
            bind_tex(textures[1]); // grass_bottom
        else
            bind_tex(textures[2]); // grass_side
        break;
    case 1:
        bind_tex(textures[3]);     // stone
        break;
    case 2:
        bind_tex(textures[1]);     // grass_bottom
        break;
    default:
        bind_tex(textures[4]);     // reftex (test texture)
    }
}

// Coordinate offsets to see if a face is touching another voxel
glm::vec3 face_checks(int index) {
    switch (index) {
    case 0:
        return glm::vec3(0.0f, 0.0f, -1.0f);
        break;
    case 1:
        return glm::vec3(0.0f, 0.0f, 1.0f);
        break;
    case 2:
        return glm::vec3(0.0f, 1.0f, 0.0f);
        break;
    case 3:
        return glm::vec3(0.0f, -1.0f, 0.0f);
        break;
    case 4:
        return glm::vec3(-1.0f, 0.0f, 0.0f);
        break;
    case 5:
        return glm::vec3(1.0f, 0.0f, 0.0f);
        break;
    }
}