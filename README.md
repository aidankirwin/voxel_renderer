# voxel_renderer

The voxel_renderer is based on voxel based video games like Minecraft. It is created entirely in C++ and OpenGL. The terrain is randomly generated using Perlin noise.

![image](https://user-images.githubusercontent.com/105574500/175797872-69100c16-4564-4057-9afc-6e79562fde60.png)
![image](https://user-images.githubusercontent.com/105574500/175797889-f0afd2c6-257f-41ab-b963-318d991dcb8a.png)

I created the textures using www.pixilart.com. 
All information on Perlin noise came from www.scratchapixel.com. All information on OpenGL and the assorted libraries used (GLAD, GLFW, stb_image, GLM) came from www.learnopengl.com. These are amazing sources, and I recommend that anyone who is interested in noise functions and/or graphics programming read them.

If you wish to run this project, you will need to download and configure/link the necessary libraries, specifically glm and GLFW (stb_image and GLAD are included in the repo). To see information about downloading and configuring GLFW: www.learnopengl.com/Getting-started/Creating-a-window (this page also covers downloading GLAD). To see information about downloading and configuring GLM: www.learnopengl.com/Getting-started/Transformations (instructions can be found in the final section, "In practice").

This is a project for testing and educational purposes only.
