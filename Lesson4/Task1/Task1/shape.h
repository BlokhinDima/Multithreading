#pragma once

#include <vector>
#include <utility>

#include "point.h"


namespace transformation
{
	template<typename T>
	class Transform;
}

namespace shapes
{
	enum class ShapeType
	{
		LINE,
		RECTANGLE,
		PARALLELPIPED,
		CIRCLE,
		CYLINDER
	};

	constexpr double INVALID_VALUE = -1;

	class Shape
	{
	public:
		Shape(ShapeType type, std::vector<point::Point> vertices) : type(type), vertices(std::move(vertices)) {}
		virtual double getArea() const = 0;
		virtual double getVolume() const = 0;
		ShapeType getType() const { return type; }
		bool operator==(const Shape& other) const;
		bool operator!=(const Shape& other) const;

	private:
		ShapeType type;

	protected:
		std::vector<point::Point> vertices;

		template<typename T>
		friend class transformation::Transform;
		int getSideSizeX() const;
		int getSideSizeY() const;
		int getSideSizeZ() const;
	};

	template<typename T>
	bool is3DShape(const T& shape)
	{
		return shape.getType() == ShapeType::CYLINDER ||
			shape.getType() == ShapeType::PARALLELPIPED;
	}

	template<typename T>
	bool checkIfTransformable(const T& shape)
	{
		return shape.getType() == ShapeType::LINE ||
			shape.getType() == ShapeType::RECTANGLE ||
			shape.getType() == ShapeType::PARALLELPIPED;
	}
}
