#ifndef _RANDOM_UTIL_H_
#define _RANDOM_UTIL_H_

class RandomTimer
{
public:
	RandomTimer(random::RndGen& gen);

	void update(float interval);
	void start(float min, float max);

	void restart();

	float getCurrentValue() const {
		ASSERT(isStarted());
		return m_cur;
	}

	bool isStarted() const {
		return m_dest > 0;
	}

	bool isTimeout() const {
		ASSERT(isStarted());
		return m_cur > m_dest;
	}

	float getDest() const {
		return m_dest;
	}

private:
	random::RndGen& r_gen;
	float m_dest;
	float m_cur;

	float m_min, m_max;
};


#endif /* _RANDOM_UTIL_H_ */
