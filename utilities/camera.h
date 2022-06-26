#pragma once

#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "../graphics/renderer.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

glm::mat4 view_transform();
glm::mat4 shader_projection(int width, int height);
void time_handling();
void camera_movement_keys(GLFWwindow* window, int width, int height);
void camera_movement_mouse(GLFWwindow* window, double xPosIn, double yPosIn);
glm::vec3 get_pos();

#endif