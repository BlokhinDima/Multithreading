#pragma once

#include "shape.h"
#include "point.h"


namespace shapes
{
	class Line : public Shape
	{
	public:
		Line(point::Point start, point::Point end) 
			: Shape(ShapeType::LINE, {start, end}) {}

		virtual double getArea() const override { return 0.0; }
		virtual double getVolume() const override { return 0.0; }
	};
}