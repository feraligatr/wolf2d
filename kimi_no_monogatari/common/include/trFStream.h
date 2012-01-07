#ifndef TR_F_STREAM_
#define TR_F_STREAM_

#include "trStream.h"

namespace tree
{

class FStream : public Stream
{
public:
public:
	enum OpenMode {
		READ,
		WRITE,
		READ_WRITE
	};
	FStream(const std::string& path, OpenMode = READ);
	virtual ~FStream();

	bool open(const std::string& path, OpenMode mode);
	void close();
	bool isValid() const {
		return m_fp;
	}
	bool isEof() const;

	size_t fileLength() const;

	virtual int read(void *buf, size_t size);
	virtual int write(const void *buf, size_t size);
	virtual bool seek(Pos whence, long offset);


private:
	FILE *m_fp;

};

}

#endif
