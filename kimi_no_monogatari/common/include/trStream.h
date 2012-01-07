#ifndef _TR_STREAM_H_
#define _TR_STREAM_H_

#include "common.h"

namespace tree {

// TODO: add stream hirachy, but for now, only stream is enough.

// TODO only has essential interface, add useful interface when needed.
class Stream
{
public:
	enum Pos {
		BEGIN,
		CURRENT,
		END
	};
	
	virtual ~Stream() { }

	// 
	virtual int read(void *buf, size_t size) = 0;
	virtual int write(const void *buf, size_t size) = 0;
	virtual bool seek(Pos whence, long offset) = 0;

	inline void skip(long off) { seek(CURRENT, off); }

// TODO: add template for all POD type?

	// istream.
	inline Stream& operator << (s8 v) {
		write(&v, sizeof(v));
		return *this;
	}

	inline Stream& operator << (s16 v) {
		write(&v, sizeof(v));
		return *this;
	}

	inline Stream& operator << (s32 v) {
		write(&v, sizeof(v));
		return *this;
	}

	inline Stream& operator << (u8 v) {
		write(&v, sizeof(v));
		return *this;
	}

	inline Stream& operator << (u16 v) {
		write(&v, sizeof(v));
		return *this;
	}

	inline Stream& operator << (u32 v) {
		write(&v, sizeof(v));
		return *this;
	}

	inline Stream& operator << (float v) {
		write(&v, sizeof(v));
		return *this;
	}

	inline Stream& operator << (bool v) {
		write(&v, sizeof(v));
		return *this;
	}

	inline Stream& operator << (const std::string& str) {
		ASSERT(str.size() < 65536);
		u16 size = str.size();
		write(&size, 2);
		if (str.size() > 0)
		{
			write(str.c_str(), size);
		}
		return *this;
	}

	// TODO: for other std containers. add when needed.
	template <typename T>
	inline Stream& operator << (const std::vector<T>& v) {
		ASSERT(str.size() < 65536);
		write((u16)v.size(), 2);
		for (const std::vector<T>::const_iterator iter = v.begin(); iter != v.end(); ++iter)
		{
			*this << *iter;
		}
		return *this;
	}

	// ostream

	inline Stream& operator >> (s8& v) {
		read(&v, sizeof(v));
		return *this;
	}

	inline Stream& operator >> (s16& v) {
		read(&v, sizeof(v));
		return *this;
	}

	inline Stream& operator >> (s32& v) {
		read(&v, sizeof(v));
		return *this;
	}

	inline Stream& operator >> (u8& v) {
		read(&v, sizeof(v));
		return *this;
	}

	inline Stream& operator >> (u16& v) {
		read(&v, sizeof(v));
		return *this;
	}

	inline Stream& operator >> (u32& v) {
		read(&v, sizeof(v));
		return *this;
	}

	inline Stream& operator >> (bool& v) {
		read(&v, sizeof(v));
		return *this;
	}

	inline Stream& operator >> (float& v) {
		read(&v, sizeof(v));
		return *this;
	}

	inline Stream& operator >> (std::string& str)
	{
		u16 size;
		*this >> size;
		if (size == 0)
		{
			str.clear();
		}
		else
		{
			char* content = new char[size];
			read(content, size);
			str.assign(content, content + size);
			delete[] content;
		}
		return *this;
	}

	// TODO: for other std containers. add when needed.
	template <typename T>
	inline Stream& operator >> (std::vector<T>& v) {
		u16 size;
		*this >> size;
		T tmp;
		for (size_t i = 0; i < size; ++i)
		{
			*this >> tmp;
			v.push_back(tmp);
		}
		return *this;
	}

};

}

#endif // _TR_STREAM_H_
