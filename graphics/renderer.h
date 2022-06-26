#pragma once

#ifndef RENDERER_H
#define RENDERER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <math.h>
#include <iostream>
#include "shader.h"
#include "buffers.h"
#include "../world/voxel.h"
#include "../world/world.h"
#include "textures.h"
#include "../utilities/camera.h"

const int chunk_width = 16;
const int chunk_height = 10;
const int chunk_limit = 1000;

// This should have its own file
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

class renderer {
public:
	void init_renderer();
	void draw_renderer(int width, int height);
	void delete_renderer();
	void get_current_chunk();
	void render_world();
	void init_new_chunk();

	chunk*** all_chunks = new chunk**[chunk_limit]();
private:
	int player_x = 0;
	int player_z = 0;
	int chunk_count = 0;
	int last_chunk_x = 0;
	int last_chunk_z = 0;
	int last_index_x = chunk_limit / 2;
	int last_index_z = chunk_limit / 2;
};

#endif
