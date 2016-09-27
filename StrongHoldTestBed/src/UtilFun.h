/*
 * UtilFun.h
 *
 *  Created on: Feb 9, 2016
 *      Author: RoboGym
 */

#ifndef SRC_UTILFUN_H_
#define SRC_UTILFUN_H_
inline float ZeroIfInRangeInclusive(float value, float min, float max) {
	if ((value >= min) && (value <= max))
	{
		return 0.0;
	}

	return value;
}

inline bool InRangeInclusive(float value, float min, float max) {
	return((value >= min) && (value <= max));

}

inline bool DistanceWithinEpsilon(double distance, double epsilon)
{
	return fabs(distance) <= fabs(epsilon);
}

inline double ImposeMinimumOnValue(double value, double minValue)
{
	if (value < minValue)
	{
		value = minValue;
	}

	return value;
}




#endif /* SRC_UTILFUN_H_ */
