#include "magic_carpet.h"

namespace vehicles
{
	double MagicCarpet::getReductonFactor(double distance) const
	{
		if (distance < 1000)
		{
			return 0;
		}
		else if (distance < 5000)
		{
			return 0.03;
		}
		else if (distance < 10000)
		{
			return 0.1;
		}
		else
		{
			return 0.05;
		}
	}
}