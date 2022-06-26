#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include "graphics/window.h"

using namespace std;

int main()
{
    window_create();
    // TODO: Improve garbage collection, fix buffer object system (maybe use draw lists?).
    return 0;
}