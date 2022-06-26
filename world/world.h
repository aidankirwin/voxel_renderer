#pragma once
#ifndef WORLD_H
#define WORLD_H

# define M_PI           3.14159265358979323846

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <math.h>
#include <cmath>
#include <functional>
#include <random>

#include "chunk.h"
#include "voxel.h"
#include "../utilities/camera.h"

float noise(glm::vec3 pos);
float fade(float t);

#endif
