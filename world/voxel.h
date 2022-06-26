#pragma once

#ifndef VOXEL_H
#define VOXEL_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../graphics/textures.h"
#include "../graphics/shader.h"
#include "../graphics/buffers.h"
#include "../utilities/camera.h"

#include <iostream>

void create_voxel_shader();
void destroy_voxel_shader();
void gen_voxel();
void render_voxel(glm::vec3 position);
void delete_voxel();
void voxel_tex(int block_ID, int i);
void init_voxel_tex();
void render_view(int width, int height);
glm::vec3 face_checks(int index);

#endif