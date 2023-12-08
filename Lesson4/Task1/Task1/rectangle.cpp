#include "rectangle.h"


namespace shapes
{
	double Rectangle::getArea() const
	{
		if (square == INVALID_VALUE)
		{
			square = getSideSizeX() * getSideSizeY();
		}
		return square;
	}
}