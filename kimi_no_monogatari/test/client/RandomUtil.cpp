#include "pch/pch.h"

#include "RandomUtil.h"

using namespace random;

RandomTimer::RandomTimer(RndGen& gen)
:m_dest(0), m_cur(0), r_gen(gen)
{
	
}

void RandomTimer::start(float min, float max)
{
	if (min == max)
	{
		m_dest = min;
	}
	else
	{
		m_dest = random::roll_float(r_gen, min, max);
	}
	m_cur = 0;
	m_min = min;
	m_max = max;
}

void RandomTimer::restart()
{
	start(m_min, m_max);
}

void RandomTimer::update(float interval)
{
	m_cur += interval;
}

