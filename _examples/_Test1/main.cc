#include <stdio.h>
#include "GL\glew.h"
#include "GLFW\glfw3.h"
#include "../_include/PastorseWindow.h"
#include "../_include/PastorseGPU.h"
#include "../_include/PastorseInput.h"
#include <iostream>
#include <thread>

struct PastorseEngine{
	PastorseInput input;
	PastorseWindow window;
	PastorseGPU* GPUInstance = nullptr;
}engine;



void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_E && action == GLFW_PRESS)
		printf("hola");
}

int main(int argc, const char* argv[])
{
	engine.GPUInstance = PastorseGPU::getInstance();

	GLchar* vertexSource =
		"#version 330 core\n"
		"layout(location = 0) in vec3 position;\n"
		"layout(location = 1) in vec3 color;\n"
		"layout(location = 2) in vec2 text_coords;\n"
		"out vec3 ourColor;\n"
		"out vec2 textCoords;\n"
		"uniform mat4 model;\n"
		"uniform mat4 view;\n"
		"uniform mat4 projection;\n"
		"void main()\n"
		"{\n"
		"gl_Position = projection * view  * model * vec4(position, 1.0f);\n"
		"ourColor = color;\n"
		"textCoords = text_coords;\n"
		"}\n";

	GLchar* fragmentSource =
		"#version 330 core\n"
		"in vec3 ourColor;\n"
		"in vec2 textCoords;\n"
		"uniform sampler2D texture_;\n"
		"out vec4 color;\n"
		"void main()\n"
		"{\n"
		"color = vec4(ourColor,1.0) * texture2D(texture_,textCoords);\n"
		"}\n";

	// vec4(ourColor,1.0f) * 


	engine.window.init_window(800, 600, "Pastorse Ultra Engine");
	//glfwSetKeyCallback(engine.window.getWindow(), key_callback);
	engine.GPUInstance->init_draw(vertexSource, fragmentSource);
	engine.GPUInstance->upload_texture();
	while (!engine.window.is_closed_window())
	{
		engine.input.key_input(engine.window.getWindow());
		engine.window.pollEvents_window();
		engine.window.change_color_window(0.0f, 0.0f, 0.0f, 1.0f);
		engine.GPUInstance->create_cube(1.0f);
		engine.GPUInstance->use_uniforms();
		engine.GPUInstance->use_program_draw();
		engine.GPUInstance->transform_draw();
		engine.GPUInstance->draw_elements_draw();
		engine.GPUInstance->use_texture();
		engine.window.swapBuffers_window();
	}

	engine.window.close_window();
	engine.GPUInstance->delete_draw();
	exit(EXIT_SUCCESS);
	
}

////////////////////////////////////////////////////

/*void average(int param[], int &result) {
	for (int i = 0; i < 10000; i++){
		result += param[i];
	}

	result = result / 10000;
}

int main(int argc, char* argv[]) {
	int result = 0;
	int my_array[10000];

	for (int i = 0; i < 10000; ++i){
		my_array[i] = i;
	}


	std::vector<std::thread> threads;
	int nr_threads = 5;

	for (int i = 0; i < nr_threads; i++) {
		threads.push_back(std::thread(average, my_array, std::ref(result)));
	}

	for (int i = 0; i < nr_threads; i++){
		threads[i].join();
	}

	std::cout << result << std::endl;


	system("pause");
	return 0;
}*/
