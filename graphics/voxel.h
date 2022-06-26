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

void gen_voxel();
void render_voxel(float offset, int blockID);
void delete_voxel();
void voxel_tex(int blockID, int i);

#endif