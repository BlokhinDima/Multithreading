#pragma once

#include "shape.h"
#include "point.h"


namespace transformation
{
	using namespace shapes;
	using namespace point;

	template<typename T>
	class Transform
	{
	public:
		Transform(const T& shape)
			: original(shape), transformable(checkIfTransformable(shape)) {}
		
		T shift(int x, int y, int z)
		{
			T shape = original;
			if (isTransformable())
			{
				const int z_coeff = is3DShape(shape) ? z : 0;
				shiftVertices(shape, x, y, z_coeff);
			}
			return shape;
		}

		T scaleX(int x)
		{
			T shape = original;
			if  (isTransformable())
			{
				scaleVerticesByX(shape, x);
			}
			return shape;
		}

		T scaleY(int y)
		{
			T shape = original;
			if (isTransformable())
			{
				scaleVerticesByY(shape, y);
			}
			return shape;
		}

		T scaleZ(int z)
		{
			T shape = original;
			if (isTransformable() && is3DShape(shape))
			{
				scaleVerticesByZ(shape, z);
			}
			return shape;
		}

		T scale(int coeff)
		{
			T shape = original;
			if (isTransformable())
			{
				scaleVerticesByX(shape, coeff);
				scaleVerticesByY(shape, coeff);
				if (is3DShape(shape))
					scaleVerticesByZ(shape, coeff);
			}
			return shape;
		};

	private:
		const T& original;
		bool transformable;

		bool isTransformable() const { return transformable; }

		static void scaleVerticesByX(T& shape, double x)
		{
			for (auto& v : shape.vertices)
				v.scaleX(x);
		}

		static void scaleVerticesByY(T& shape, double y)
		{
			for (auto& v : shape.vertices)
				v.scaleY(y);
		}

		static void scaleVerticesByZ(T& shape, double z)
		{
			for (auto& v : shape.vertices)
				v.scaleZ(z);
		}

		static void shiftVertices(T& shape, int x, int y, int z)
		{
			for (auto& v : shape.vertices)
				v.shift(x, y, z);
		}	
	};
}