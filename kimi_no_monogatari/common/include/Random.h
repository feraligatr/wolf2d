#ifndef _RANDOM_H_
#define _RANDOM_H_

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/discrete_distribution.hpp>
#include <boost/random/uniform_real_distribution.hpp>

namespace random
{

typedef boost::random::mt19937 RndGen;

extern RndGen g_rndGen;

inline int roll_die(RndGen& gen, int max)
{
	boost::random::uniform_int_distribution<> dist(0, max - 1);
	return dist(gen);
}

inline int roll_die(RndGen& gen, int min, int max)
{
	boost::random::uniform_int_distribution<> dist(min, max - 1);
	return dist(gen);
}

inline float roll_float(RndGen& gen, float min, float max)
{
	boost::random::uniform_real_distribution<> dist(min, max);
	return (float)dist(gen);
}

}

#endif /* _RANDOM_H_ */
