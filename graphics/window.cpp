#include "window.h"

using namespace std;

const int width = 800;
const int height = 600;

// Initialize GLFW
void window_create() {

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* new_window = glfwCreateWindow(width, height, "voxel_gen", NULL, NULL);

    if (new_window == NULL) {
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        exit(-1);
    }

    glfwMakeContextCurrent(new_window);

    // Callbacks
    glfwSetFramebufferSizeCallback(new_window, framebuffer_size_callback);
    glfwSetCursorPosCallback(new_window, mouse_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        cout << "Failed to initialize GLAD" << endl;
        exit(-1);
    }

    // Set dimensions of window
    glViewport(0, 0, width, height);

    glfwSetInputMode(new_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glEnable(GL_DEPTH_TEST);

    renderer* new_renderer = new renderer();

    new_renderer->init_renderer();

    // Main while loop
    while (!glfwWindowShouldClose(new_window)) {
        process_input(new_window);

        new_renderer->draw_renderer(width, height);

        glfwSwapBuffers(new_window);
        glfwPollEvents();
    }

    new_renderer->delete_renderer();
    glfwDestroyWindow(new_window);
    glfwTerminate();
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xPosIn, double yPosIn) {
    camera_movement_mouse(window, xPosIn, yPosIn);
}

void process_input(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    camera_movement_keys(window, width, height);
}