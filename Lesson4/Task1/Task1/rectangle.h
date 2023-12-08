#pragma once

#include "shape.h"
#include "point.h"


namespace shapes
{
	using namespace point;
	
	class Rectangle : public Shape
	{
	public:
		Rectangle(std::vector<point::Point> vertices) 
			: Shape(ShapeType::RECTANGLE, std::move(vertices)) {}
		virtual double getArea() const override;
		virtual double getVolume() const override { return 0.0; }

	private:
		mutable double square = INVALID_VALUE;
	};
}
