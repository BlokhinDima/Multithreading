#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

#include "shape.h"
#include "point.h"


namespace shapes
{
	class Circle : public Shape
	{
	public:
		Circle(const point::Point& center, double radius) : Shape(ShapeType::CIRCLE, {center}), radius(radius) {}
		virtual double getArea() const override;
		virtual double getVolume() const override { return 0.0; }
		bool operator==(const Circle& other) const;
		bool operator!=(const Circle& other) const;
		
	private:
		double radius;
		mutable double area = INVALID_VALUE;
	};
}
