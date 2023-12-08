#pragma once


namespace point
{
	struct Point
	{
		Point(int x, int y, int z) : x(x), y(y), z(z) {}
		Point(int x, int y) : Point(x, y, 0) {}
		Point() : Point(0, 0, 0) {}
		
		int getX() const { return x; }
		int getY() const { return y; }
		int getZ() const { return z; }

		int setX(int x) { x = x; }
		int setY(int y) { y = y; }
		int setZ(int z) { z = z; }

		void shift(int x_coeff, int y_coeff)
		{
			x += x_coeff;
			y += y_coeff;
		}
		void shift(int x_coeff, int y_coeff, int z_coeff)
		{
			shift(x_coeff, y_coeff);
			z += z_coeff;
		}

		void scaleX(double coeff) { x = scaleValue(x, coeff); }
		void scaleY(double coeff) { y = scaleValue(y, coeff); }
		void scaleZ(double coeff) { z = scaleValue(z, coeff); }

		bool operator ==(const Point& other) const
		{
			return x == other.x && y == other.y && z == other.z;
		}
		bool operator !=(const Point& other) const { return !(*this == other); }

	private:
		int x, y, z;

		static int scaleValue(double value, double coeff) { return static_cast<int>(value * coeff); }
	};
}