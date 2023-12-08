#pragma once

#include <vector>

#include "shape.h"
#include "point.h"


namespace shapes
{
	using namespace point;

	class Parallelepiped : public Shape
	{
	public:
		Parallelepiped(std::vector<point::Point> vertices) : Shape(ShapeType::PARALLELPIPED, std::move(vertices)) {}
		virtual double getArea() const override;
		virtual double getVolume() const override;
		
	private:
		mutable double area = INVALID_VALUE;
		mutable double volume = INVALID_VALUE;
	};
}
