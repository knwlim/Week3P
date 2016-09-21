#include <GLFW/glfw3.h>
#include <cstring>
#include <stdlib.h>		  // srand, rand
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include <algorithm>
#include "math.h"

const int width = 640;
const int height = 480;

float* pixels = new float[width*height * 3];

void drawPixel(const int& i, const int& j, const float& red, const float& green, const float& blue)
{
	pixels[(i + width* j) * 3 + 0] = red;
	pixels[(i + width* j) * 3 + 1] = green;
	pixels[(i + width* j) * 3 + 2] = blue;
}

void drawthinkPixel(const int& i, const int& j, const float& red, const float& green, const float& blue)
{
	pixels[(i + width* j) * 3 + 0] = red;
	pixels[(i + width* j) * 3 + 3] = red;
	pixels[(i + width* j) * 3 + 6] = red;

	pixels[(i + width* j) * 3 + 1] = green;
	pixels[(i + width* j) * 3 + 4] = green;
	pixels[(i + width* j) * 3 + 7] = green;

	pixels[(i + width* j) * 3 + 2] = blue;
	pixels[(i + width* j) * 3 + 5] = blue;
	pixels[(i + width* j) * 3 + 8] = blue;
};

// scratched from https://courses.engr.illinois.edu/ece390/archive/archive-f2000/mp/mp4/anti.html
// see 'Rasterization' part.
void drawLine(const int& i0, const int& j0, const int& i1, const int& j1, const float& red, const float& green, const float& blue)
{
	for (int i = i0; i <= i1; i++)
	{
		const int j = (j1 - j0)*(i - i0) / (i1 - i0) + j0;

		drawPixel(i, j, red, green, blue);
	}
}

void drawthickLine(const int& i0, const int& j0, const int& i1, const int& j1, const float& red, const float& green, const float& blue)
{
	for (int i = i0; i <= i1; i++)
	{
		const int j = (j1 - j0)*(i - i0) / (i1 - i0) + j0;

		drawthinkPixel(i, j, red, green, blue);
	}
}

bool isInsideCircle(const double x, const double y)
{
	const double x_c = 500;
	const double y_c = 100;
	const double r = 80;

	const double f = (x - x_c)*(x - x_c) + (y - y_c)*(y - y_c) - r * r;

	if ( f < 80 && f > -80) return true;
	else return false;
}



int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glClearColor(1, 1, 1, 1); // while background

							  /* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{


		std::fill_n(pixels, width*height * 3, 1.0f);	// white background


		for (int i = 270; i < 400; i++ )
		drawthinkPixel(i-250, i, 1.0f, 0.0f, 0.0f);
		// thick line


		drawLine(460, 400, 540, 350, 1.0f, 0.0f, 0.0f);
		drawLine(460, 300, 540, 350,  1.0f, 0.0f, 0.0f);
		for (int i = 300; i < 400; i++)
		{
			drawPixel(460, i, 1.0f, 0.0f, 0.0f);
		} // triangle


		drawLine(60, 150, 150, 150, 1.0f, 0.0f, 0.0f);
		drawLine(60, 60, 150, 60, 1.0f, 0.0f, 0.0f);
		drawLine(30, 105, 60, 150, 1.0f, 0.0f, 0.0f);
		drawLine(150, 150, 190, 105, 1.0f, 0.0f, 0.0f);
		drawLine(30, 105, 60, 60, 1.0f, 0.0f, 0.0f);
		drawLine(150, 60, 190, 105, 1.0f, 0.0f, 0.0f);
		// six??



		for (int x = 0; x < 2500; x++)
			for (int y = 0; y < 2000; y++)
			{
				if (isInsideCircle(x, y) == true)
				{
					drawPixel(x, y, 1.0f, 0.0f, 0.0f);
				}
			}
		// circle






		drawLine(240, 400, 350, 400, 1.0f, 0.0f, 0.0f);
		drawLine(240, 300, 350, 300, 1.0f, 0.0f, 0.0f);
		for (int i = 301; i < 400; i++)
		{
			drawPixel(240, i, 1.0f, 0.0f, 0.0f);
		}
		for (int i = 301; i < 400; i++)
		{
			drawPixel(350, i, 1.0f, 0.0f, 0.0f);
		} // rectangle






		for (int i = 270; i < 400; i++)
			for (int j = 30; j < 120; j++)
		{
			drawPixel(i, j, 1.0f, 0.0f, 0.0f);
		} // filled rectangle





		glDrawPixels(width, height, GL_RGB, GL_FLOAT, pixels);

		glfwSwapBuffers(window);
		glfwPollEvents();
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	glfwTerminate();

	delete[] pixels; // or you may reuse pixels array 

	return 0;
}

