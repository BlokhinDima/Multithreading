#include "cylinder.h"


namespace shapes
{
	double Cylinder::getArea() const
	{
		if (area == INVALID_VALUE)
		{
			area = 2.0 * M_PI * radius * (radius + height);
		}
		return area;
	}

	double Cylinder::getVolume() const
	{
		if (volume == INVALID_VALUE)
		{
			volume = M_PI * radius * radius * height;
		}
		return volume;
	}

	bool Cylinder::operator==(const Cylinder& other) const
	{
		if (Shape::operator !=(other))
		{
			return false;
		}
		return radius == other.radius && height == other.height;
	}

	bool Cylinder::operator!=(const Cylinder& other) const
	{
		return !(*this == other);
	}
}