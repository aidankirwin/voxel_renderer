#include "../graphics/renderer.h"

void chunk::set_xz(int x, int z) {
	x_offset = x;
	z_offset = z;
}

int chunk::get_x() {
	return x_offset;
}

int chunk::get_z() {
	return z_offset;
}

void chunk::destroy_chunk() {
	// TODO: Create better system for creating/destroying individual voxels
}

void chunk::build_chunk() {
	int layers = 4;
	float max = 0;
	float noise_map[chunk_width][chunk_width];
	for (int x = 0; x < chunk_width; x++) {
		for (int z = 0; z < chunk_width; z++) {

			float fractal = 0;
			float amplitude = 1;
			glm::vec3 pos = glm::vec3((static_cast<float>(x) + x_offset) / 30, (static_cast<float>(z) + z_offset) / 30, 0);

			noise_map[x][z] = noise(pos) + 0.1 * noise(pos * 2.0f);
			int height = static_cast<int>( noise_map[x][z] * chunk_height * 1.3 + chunk_height / 2);
			for (int y = 0; y < chunk_height; y++) {
				if (y < height) chunk_arr[x][y][z] = true;
				else if(y < 3) chunk_arr[x][y][z] = true;
				else chunk_arr[x][y][z] = false;
			}
		}
	}
}

void chunk::gen_chunk() {
	for (int y = 0; y < chunk_height; y++) {
		for (int x = x_offset; x < chunk_width + x_offset; x++) {
			for (int z = z_offset; z < chunk_width + z_offset; z++) {
				if (chunk_arr[x - x_offset][y][z - z_offset]) {
					render_voxel(glm::vec3(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z)));

					
					// Add voxels to chunk
					glm::vec3 pos = glm::vec3(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z));
					for (int i = 0; i < 6; i++) {
						if (!check_voxel(pos + face_checks(i))) {
							if(y == chunk_height - 1) voxel_tex(0, i);
							else if(y == 0) voxel_tex(1, i);
							else if(chunk_arr[x - x_offset][y + 1][z - z_offset] == false) voxel_tex(0, i);
							else voxel_tex(2, i);
							glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(i * 6 * sizeof(unsigned int)));
						}
					}
				}
			}
		}
	}
}

bool chunk::check_voxel(glm::vec3 pos) {
	int x = static_cast<int>(floor(pos.x));
	int y = static_cast<int>(floor(pos.y));
	int z = static_cast<int>(floor(pos.z));

	if (y < 0) return true;
	if (x < x_offset || x > chunk_width - 1 + x_offset || y > chunk_height - 1 || z < z_offset || z > chunk_width - 1 + z_offset)
		return false;

	// Block info is stored in chunk_arr from 0 -> chunk width/height. Need to convert coords to chunk coords
	int x_minus_offset = x - x_offset;
	int z_minus_offset = z - z_offset;

	return chunk_arr[x_minus_offset][y][z_minus_offset];
}