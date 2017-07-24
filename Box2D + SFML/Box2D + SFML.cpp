#include "stdafx.h"
#include <stdio.h>
#include <cstdlib>
#include "Box2D\Box2D.h"
#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"
#include "Object.h"
#include <algorithm>
#include <cmath>





#define M_PI 3.14159265359


int main(int argc, char** argv)
{

	srand(time(NULL));

	int min_radius = 100;
	int rnd_radius = 100;
	int min_vertices = 4;
	int rnd_vertices = 6;
	float omega = 0.01f;


	while (true) {
		int amount_of_vertices = rand() % rnd_vertices + min_vertices;
		int angle_range = 360 / amount_of_vertices;

		for (int i = 0; i < amount_of_vertices; ++i)
		{
			int length = min_radius + rand() % rnd_radius;
			int angle = rand() % angle_range + i * angle_range;
			float radians = angle * M_PI / 180.f;
			float x = sinf(radians) * length;
			float y = cosf(radians) * length;


			printf("%f\n", x*x + y*y);

			#ifndef NDEBUG

			float xxyy = x*x + y*y;
			float max_length = (min_radius + rnd_radius - 1)*(min_radius + rnd_radius - 1) + omega;

			#endif // !NDEBUG


			assert(xxyy <= max_length);


			printf("vertex = (%f, %f)\n", x, y);
		}
	}


	return 0;
}
