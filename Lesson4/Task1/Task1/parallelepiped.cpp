#include "parallelepiped.h"


namespace shapes
{
	double Parallelepiped::getArea() const
	{
		if (area == INVALID_VALUE)
		{
			const int sideA = getSideSizeX();
			const int sideB = getSideSizeY();
			const int sideC = getSideSizeZ();
			area = 2 * (sideA * sideB + sideA * sideC + sideB * sideC);
		}
		return area;
	}

	double Parallelepiped::getVolume() const
	{
		if (volume == INVALID_VALUE)
		{
			volume = getSideSizeX() * getSideSizeY() * getSideSizeZ();
		}
		return volume;
	}
}