#include "Piece.hpp"

Piece::Piece(std::string _color, int _power, int _x, int _y, char _shape)
{
  color = _color;
	power = _power;
	x = _x;
	default_x = _x;
	y = _y;
	default_y = _y;
	shape = _shape;

	if(color == "YELLOW")
  {
		movement = power;
	}

	if(color == "RED")
  {
		movement = -power;
	}
}

void Piece::move()
{
  if ( state == 1 )
  {
    if(color == "YELLOW"){
      y += movement;
    }
	  if(color == "RED"){
      x += movement;
    }
  }
}

void Piece::changeFeatures()
{
  if (state == 1){
		if(color == "YELLOW"){
			if (y == 0){
				movement = power;
				shape = '>';
				default_y = 0;
			}
			if (y == 6){
				movement = -power;
				shape = '<';
				default_y = 6;
			}
		}
		if(color == "RED")
    {
			if (x == 0){
				movement = power;
				shape = 'v';
				default_x = 0;
			}
			if (x == 6){
				movement = -power;
				shape = '^';
				default_x = 6;
			}
		}
	}
}
