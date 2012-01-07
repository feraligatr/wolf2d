#include "pch/pch.h"

#include <stdio.h>

#include "trFStream.h"

namespace tree
{

FStream::FStream(const std::string& path, OpenMode mode)
:m_fp(NULL)
{
	open(path, mode);
}

FStream::~FStream()
{
	close();
}

bool FStream::open(const std::string& path, OpenMode mode)
{
	if (m_fp)
	{
		ASSERT(false);		// MUST close the file before re-opening it
		fclose(m_fp);
		m_fp = NULL;
	}

	switch (mode)
	{
	case READ:
		m_fp = fopen(path.c_str(), "rb");
		break ;

	case WRITE:
		m_fp = fopen(path.c_str(), "wb");
		break ;

	case READ_WRITE:
		m_fp = fopen(path.c_str(), "r+");
		break ;

	default: // unsupported modes
		ASSERT(false);
		return false;
	}
	
	return m_fp != NULL;
}

size_t FStream::fileLength() const
{
	ASSERT(isValid());

	long cur = ftell(m_fp);
	fseek(m_fp, 0, SEEK_SET);
	long set = ftell(m_fp);
	fseek(m_fp, 0, SEEK_END);
	size_t sz = ftell(m_fp) - set;
	fseek(m_fp, cur - set, SEEK_SET);
	return sz;
}

void FStream::close()
{
	if (m_fp)
	{
		fclose(m_fp);
		m_fp = NULL;
	}
}

bool FStream::isEof() const
{
	return feof(m_fp) != 0;
}

int FStream::read(void *buf, size_t size)
{
	ASSERT(isValid());

	if (buf == NULL && size == 0)
		return true;
	size_t r = fread(buf, 1, size, m_fp);
	ASSERT(r == size); // whether we should assert here or assert in stream operator?
	return r;
}

int FStream::write(const void *buf, size_t size)
{
	ASSERT(isValid());

	if (buf == NULL && size == 0)
		return true;

	size_t r = fwrite(buf, 1, size, m_fp);
	return r;
}

bool FStream::seek(Pos whence, long offset)
{
	ASSERT(isValid());

	if (whence == CURRENT && offset == 0) // must return here
		return true;

	int w;
	switch (whence)
	{
	case BEGIN: w = SEEK_SET; break ;
	case CURRENT: w = SEEK_CUR; break ;
	case END: w = SEEK_END; break ;
	default: ASSERT(false); return false;
	}

	return fseek(m_fp, offset, w) == 0;
}


}
