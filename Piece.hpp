#pragma once

#include <string>
#include <iostream>

class Piece
{
public:
	Piece(std::string _color, int _power, int _x, int _y, char _shape);
	~Piece() { }

	std::string color;
	int power;
	int x;
	int y;
	int default_x;
	int default_y;
	char shape;
	int movement;
	int state = 1;

	void move();

	void changeFeatures();

};
