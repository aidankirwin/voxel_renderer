#include "world.h"

using namespace std;

// All information on noise functions came from www.scratchapixel.com

const int s = 16;
const int s_mask = s - 1;

float noise(glm::vec3 pos) {

	int perm_table[s * 2];

	// Generate 8 "gradient" vectors - random normalized 3D vectors

	glm::vec3 gradients[s];

	// One for each corner of 3D cube of space

	std::mt19937 gen(2016);
	std::uniform_real_distribution<float> dist;
	auto rand = std::bind(dist, gen);

	for (int i = 0; i < s; i++) {

		// To distribute uniformly

		float theta = acos(2 * rand() - 1);
		float phi = 2 * rand() * M_PI;

		float x = cos(phi) * sin(theta);
		float y = sin(phi) * sin(theta);
		float z = cos(theta);
		gradients[i] = glm::vec3(x, y, z);

		perm_table[i] = i;
	}

	std::uniform_int_distribution<unsigned> dist_int;
	auto rand_int = std::bind(dist_int, gen);

	for (int i = 0; i < s; i++) {
		std::swap(perm_table[i], perm_table[rand_int() & s_mask]);
	}
	for (int i = 0; i < s; i++) {
		perm_table[s + i] = perm_table[i];
	}

	int x0 = static_cast<int>(floor(pos.x)) & s_mask;
	int y0 = static_cast<int>(floor(pos.y)) & s_mask;
	int z0 = static_cast<int>(floor(pos.z)) & s_mask;

	int x1 = (x0 + 1) & s_mask;
	int y1 = (y0 + 1) & s_mask;
	int z1 = (z0 + 1) & s_mask;

	float tx = pos.x - floor(pos.x);
	float ty = pos.y - floor(pos.y);
	float tz = pos.z - floor(pos.z);

	float u = fade(tx);
	float v = fade(ty);
	float w = fade(tz);

	const glm::vec3 c000 = gradients[perm_table[perm_table[perm_table[x0] + y0] + z0]];
	const glm::vec3 c100 = gradients[perm_table[perm_table[perm_table[x1] + y0] + z0]];
	const glm::vec3 c010 = gradients[perm_table[perm_table[perm_table[x0] + y1] + z0]];
	const glm::vec3 c110 = gradients[perm_table[perm_table[perm_table[x1] + y1] + z0]];

	const glm::vec3 c001 = gradients[perm_table[perm_table[perm_table[x0] + y0] + z1]];
	const glm::vec3 c101 = gradients[perm_table[perm_table[perm_table[x1] + y0] + z1]];
	const glm::vec3 c011 = gradients[perm_table[perm_table[perm_table[x0] + y1] + z1]];
	const glm::vec3 c111 = gradients[perm_table[perm_table[perm_table[x1] + y1] + z1]];

	// Find direction from each corner to point (x,y,z)

	float xi = tx;
	float yi = ty;
	float zi = tz;
	float xf = tx - 1;
	float yf = ty - 1;
	float zf = tz - 1;

	glm::vec3 p000 = glm::vec3(xi, yi, zi);
	glm::vec3 p100 = glm::vec3(xf, yi, zi);
	glm::vec3 p010 = glm::vec3(xi, yf, zi);
	glm::vec3 p110 = glm::vec3(xf, yf, zi);

	glm::vec3 p001 = glm::vec3(xi, yi, zf);
	glm::vec3 p101 = glm::vec3(xf, yi, zf);
	glm::vec3 p011 = glm::vec3(xi, yf, zf);
	glm::vec3 p111 = glm::vec3(xf, yf, zf);

	// Take the dot product of those vectors with respective gradients, computes 8 random values

	float dot_a1 = glm::dot(c000, p000);
	float dot_a2 = glm::dot(c100, p100);

	float dot_b1 = glm::dot(c010, p010);
	float dot_b2 = glm::dot(c110, p110);

	float dot_c1 = glm::dot(c001, p001);
	float dot_c2 = glm::dot(c101, p101);

	float dot_d1 = glm::dot(c011, p011);
	float dot_d2 = glm::dot(c111, p111);
	
	// Use trilinear interpolation on the values

	float a = dot_a1 * (1 - u) + dot_a2 * u;
	float b = dot_b1 * (1 - u) + dot_b2 * u;
	float c = dot_c1 * (1 - u) + dot_c2 * u;
	float d = dot_d1 * (1 - u) + dot_d2 * u;

	float e = a * (1 - v) + b * v;
	float f = c * (1 - v) + d * v;

	float g = e * (1 - w) + f * w;
	return g;
}

float fade(float t) {
	return t * (3 - 2 * t);
}

