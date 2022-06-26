#include "renderer.h"

using namespace std;

void renderer::init_renderer() {

    // Initialize all_chunks as a 2D pointer array to store chunk data
    // The indices of all_chunks map to coordinate system
    for (int i = 0; i < chunk_limit; i++) {
        all_chunks[i] = new chunk*[chunk_limit]();
    }

    create_voxel_shader();
    // Currently only using one set of buffer objects, this is bad
    gen_voxel();
    destroy_voxel_shader();
    init_voxel_tex();
}

void renderer::draw_renderer(int width, int height) {

    time_handling();

    glClearColor(0.1f, 0.3f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    get_current_chunk();
    render_world();

    render_view(width, height);
}

void renderer::delete_renderer() {
    delete_voxel();
    for (int i = 0; i < chunk_limit; i++) {
        for (int j = 0; j < chunk_limit; j++) {
            if(all_chunks[i][j] != 0) delete all_chunks[i][j];
        }
    }

    delete[] all_chunks;
}

void renderer::get_current_chunk() {
    glm::vec3 position = get_pos();
    player_x = static_cast<int>(position.x);
    player_z = static_cast<int>(position.z);

    if (chunk_count == 0) {
        all_chunks[chunk_limit / 2][chunk_limit / 2] = new chunk();
        all_chunks[chunk_limit / 2][chunk_limit / 2]->set_xz(0, 0);
        all_chunks[chunk_limit / 2][chunk_limit / 2]->build_chunk();
        chunk_count++;
    }

    // TODO: Add checks for out of bounds, reorganize
    else if (player_x == (last_chunk_x + chunk_width) && player_z == (last_chunk_z + chunk_width)) {
        last_chunk_x += chunk_width;
        last_chunk_z += chunk_width;
        last_index_x++;
        last_index_z++;
        init_new_chunk();
    }
    else if (player_x == (last_chunk_x + chunk_width) && player_z == (last_chunk_z - 1)) {
        last_chunk_x+= chunk_width;
        last_chunk_z-= chunk_width;
        last_index_x++;
        last_index_z--;
        init_new_chunk();
    }
    else if (player_x == (last_chunk_x - 1) && player_z == (last_chunk_z + chunk_width)) {
        last_chunk_x-= chunk_width;
        last_chunk_z+= chunk_width;
        last_index_x--;
        last_index_z++;
        init_new_chunk();
    }
    else if (player_x == (last_chunk_x - 1) && player_z == (last_chunk_z - 1)) {
        last_chunk_x-= chunk_width;
        last_chunk_z-= chunk_width;
        last_index_x--;
        last_index_z--;
        init_new_chunk();
    }
    else if (player_x == (last_chunk_x + chunk_width)) {
        last_chunk_x+= chunk_width;
        last_index_x++;
        init_new_chunk();
    }
    else if (player_x == (last_chunk_x - 1)) {
        last_chunk_x-= chunk_width;
        last_index_x--;
        init_new_chunk();
    }
    else if (player_z == (last_chunk_z + chunk_width)) {
        last_chunk_z+= chunk_width;
        last_index_z++;
        init_new_chunk();
    }
    else if (player_z == (last_chunk_z - 1)) {
        last_chunk_z-= chunk_width;
        last_index_z--;
        init_new_chunk();
    }
}

void renderer::render_world() {

    all_chunks[last_index_z][last_index_x]->gen_chunk();
    
    // Number of chunks that load out from current chunk
    // Render distance of 2 = 25 total chunks load at a time
    // TODO: Change so that it follows the view
    int render_distance = 2;
    for (int i = -render_distance; i <= render_distance; i++) {
        for (int j = -render_distance; j <= render_distance; j++) {
            if (all_chunks[last_index_z + i][last_index_x + j] == 0) {
                all_chunks[last_index_z + i][last_index_x + j] = new chunk();
                all_chunks[last_index_z + i][last_index_x + j]->set_xz(last_chunk_x + (chunk_width * j), last_chunk_z + (chunk_width * i));
                all_chunks[last_index_z + i][last_index_x + j]->build_chunk();
                chunk_count++;
            }
            all_chunks[last_index_z + i][last_index_x + j]->gen_chunk();

        }
    }
}

void renderer::init_new_chunk() {
    if (all_chunks[last_index_z][last_index_x] == 0) {
        all_chunks[last_index_z][last_index_x] = new chunk();
        all_chunks[last_index_z][last_index_x]->set_xz(last_chunk_x, last_chunk_z);
        all_chunks[last_index_z][last_index_x]->build_chunk();
        chunk_count++;
    }
}