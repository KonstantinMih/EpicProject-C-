#pragma once

#define pi 3.14159265358979323846

#include <iostream>
#include <cstring>
//#include <math.h>
#include <cmath>

class Map {
private:
	size_t size_x;
	size_t size_y;
	char* map;
public:

	Map(size_t size_x, size_t size_y, char* mep) : size_x(size_x), size_y(size_y) {
		map = new char[size_x * size_y];
		memcpy(map, mep, size_x * size_y);
	}

	char operator()(size_t coord_x, size_t coord_y) {
		return map[coord_y + coord_x * size_x];
	}

	~Map() {
		delete[] map;
	}

};

class Player {
public:

	double x;
	double y;
	double angle;
	double fov;
	const double speed = 0.1;
	const double rotate_speed = 0.2;

	Player(double x, double y, double angle = pi / 2 , double fov = pi / 3) : x(x), y(y), angle(angle), fov(fov) {}

	void move_forward() {
		x += speed * cos(angle);
		y += speed * sin(angle);
	}

	void move_back() {
		x -= speed * cos(angle);
		y -= speed * sin(angle);
	}

	void turn_right() {
		angle += rotate_speed;
	}

	void turn_left() {
		angle -= rotate_speed;
	}

};