#include "circle.h"

namespace shapes
{
	double Circle::getArea() const
	{
		if (area == INVALID_VALUE)
		{
			area = M_PI * radius * radius;
		}
		return area;
	}

	bool Circle::operator ==(const Circle& other) const
	{
		if (Shape::operator !=(other))
		{
			return false;
		}
		return radius == other.radius;
	}

	bool Circle::operator !=(const Circle& other) const
	{
		return !(*this == other);
	}
}