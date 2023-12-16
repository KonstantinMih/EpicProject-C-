#pragma once

#define pi 3.14159265358979323846

#include <iostream>
#include <cstring>
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

	size_t get_size_x() const{
		return size_x;
	}

	size_t get_size_y() const{
		return size_y;
	}

	char operator()(size_t coord_x, size_t coord_y) const{
		return map[coord_y + coord_x * size_x];
	}

	~Map() {
		delete[] map;
	}

};

bool collision(double x, double y, size_t cell_size_x, size_t cell_size_y, char* map, size_t map_size_x, size_t map_size_y) {
	if (0 <= x && x < cell_size_x * map_size_x && 0 <= y && y < cell_size_y * map_size_y) {
		if (map[int(y) + map_size_x * int(x)] == ' ') {
			return 0;
		}
		else {
			return 1;
		}
	}
	else {
		return 1;
	}
}

class Player {
public:

	double x;
	double y;
	double angle;
	double fov;
	const double speed = 0.1;
	const double rotate_speed = 0.2;

	Player(double x, double y, double angle = pi / 2 , double fov = pi / 3) : x(x), y(y), angle(angle), fov(fov) {}

	void move_forward(size_t cell_size_x, size_t cell_size_y, char* map, size_t map_size_x, size_t map_size_y) {
		
		double delta_x = speed * cos(angle);
		double delta_y = speed * sin(angle);

		if (0 == collision(delta_x + x, delta_y + y, cell_size_x, cell_size_y, map, map_size_x, map_size_y)) {
			x += delta_x;
			y += delta_y;
		}
		else if (0 == collision(delta_x + x, y, cell_size_x, cell_size_y, map, map_size_x, map_size_y)){
			x += delta_x;
		}
		else if (0 == collision(x, y + delta_y, cell_size_x, cell_size_y, map, map_size_x, map_size_y)) {
			y += delta_y;
		}
	}

	void move_back(size_t cell_size_x, size_t cell_size_y, char* map, size_t map_size_x, size_t map_size_y) {

		double delta_x = -speed * cos(angle);
		double delta_y = -speed * sin(angle);

		if (0 == collision(delta_x + x, delta_y + y, cell_size_x, cell_size_y, map, map_size_x, map_size_y)) {
			x += delta_x;
			y += delta_y;
		}
		else if (0 == collision(delta_x + x, y, cell_size_x, cell_size_y, map, map_size_x, map_size_y)) {
			x += delta_x;
		}
		else if (0 == collision(x, y + delta_y, cell_size_x, cell_size_y, map, map_size_x, map_size_y)) {
			y += delta_y;
		}
	}

	void strife_right(size_t cell_size_x, size_t cell_size_y, char* map, size_t map_size_x, size_t map_size_y) {

		double delta_x = -speed * cos(pi / 2 - angle);
		double delta_y = speed * sin(pi / 2 + angle);

		if (0 == collision(delta_x + x, delta_y + y, cell_size_x, cell_size_y, map, map_size_x, map_size_y)) {
			x += delta_x;
			y += delta_y;
		}
		else if (0 == collision(delta_x + x, y, cell_size_x, cell_size_y, map, map_size_x, map_size_y)) {
			x += delta_x;
		}
		else if (0 == collision(x, y + delta_y, cell_size_x, cell_size_y, map, map_size_x, map_size_y)) {
			y += delta_y;
		}
	}

	void strife_left(size_t cell_size_x, size_t cell_size_y, char* map, size_t map_size_x, size_t map_size_y) {

		double delta_x = speed * cos(pi / 2 - angle);
		double delta_y = -speed * sin(pi / 2 + angle);

		if (0 == collision(delta_x + x, delta_y + y, cell_size_x, cell_size_y, map, map_size_x, map_size_y)) {
			x += delta_x;
			y += delta_y;
		}
		else if (0 == collision(delta_x + x, y, cell_size_x, cell_size_y, map, map_size_x, map_size_y)) {
			x += delta_x;
		}
		else if (0 == collision(x, y + delta_y, cell_size_x, cell_size_y, map, map_size_x, map_size_y)) {
			y += delta_y;
		}
	}

	void turn_right() {
		angle += rotate_speed;
	}

	void turn_left() {
		angle -= rotate_speed;
	}

};