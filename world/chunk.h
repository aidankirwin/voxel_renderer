#pragma once

/*
#ifndef CHUNK_H
#define CHUNK_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "voxel.h"
#include <iostream>
#include <math.h>

const int chunk_width = 16;
const int chunk_height = 50;

class chunk {
private:
	bool chunk_arr[chunk_width][chunk_height][chunk_width];
	int x_offset;
	int z_offset;
public:
	int get_x();
	int get_z();
	void set_xz(int x, int z);
	void build_chunk();
	void destroy_chunk();
	void gen_chunk();
	bool check_voxel(glm::vec3 pos);
};

#endif*/