#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

#include "shape.h"
#include "point.h"


namespace shapes
{
	class Cylinder : public Shape
	{
	public:
		Cylinder(const point::Point& center, double radius, double height)
			: Shape(ShapeType::CYLINDER, {center}), radius(radius), height(height) {}

		virtual double getArea() const override;
		virtual double getVolume() const override;
		bool operator==(const Cylinder& other) const;
		bool operator!=(const Cylinder& other) const;

	private:
		double radius;
		double height;
		mutable double area = INVALID_VALUE;
		mutable double volume = INVALID_VALUE;
	};
}
