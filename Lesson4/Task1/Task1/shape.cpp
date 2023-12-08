#include"shape.h"


namespace shapes
{
	bool Shape::operator==(const Shape& other) const
	{
		if (getType() != other.getType())
			return false;

		for (size_t i = 0; i < vertices.size(); ++i)
		{
			if (vertices[i] != other.vertices[i])
				return false;
		}
		return true;
	}

	bool Shape::operator!=(const Shape& other) const
	{
		return !(*this == other);
	}

	int Shape::getSideSizeX() const
	{
		int size = 0;
		for (auto& v1 : vertices)
		{
			for (auto& v2 : vertices)
				size = std::max(size, abs(v1.getX() - v2.getX()));
		}
		return size;
	}

	int Shape::getSideSizeY() const
	{
		int size = 0;
		for (auto& v1 : vertices)
		{
			for (auto& v2 : vertices)
				size = std::max(size, abs(v1.getY() - v2.getY()));
		}
		return size;
	}

	int Shape::getSideSizeZ() const
	{
		int size = 0;
		for (auto& v1 : vertices)
		{
			for (auto& v2 : vertices)
				size = std::max(size, abs(v1.getZ() - v2.getZ()));
		}
		return size;
	}
}