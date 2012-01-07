#include "pch/pch.h"

#include "WolfLevel.h"

static void Lvl_RLEWexpand(u16 *source, u16 *dest, 
						long length, unsigned rlewtag )
{
	unsigned value,count,i;
	u16 *end;



//
// expand it
//
	end = dest + (length >> 1);

	do
	{
		value = *source++;
		if( value != rlewtag )
		{
			//
			// uncompressed
			//
			*dest++ = value;
		}
		else
		{
			//
			// compressed string
			//
			count = *source++;
			value = *source++;

			for( i = 1 ; i <= count ; ++i )
			{
				*dest++ = value;
			}
		}

	} while( dest < end );

}

static void Lvl_CarmackExpand( u16 *source, u16 *dest, u16 length )
{
	#define NEARTAG	0xA7
	#define FARTAG	0xA8


	u32	chhigh, offset;
	u16	*copyptr, *outptr;
	u8	*inptr;
	u16 ch, count;

	length /= 2;

	inptr = (u8 *)source;
	outptr = dest;

	while( length )
	{
		ch = *(u16 *)inptr;
		inptr += 2;
		chhigh = ch >> 8;
		if( chhigh == NEARTAG )
		{
			count = ch & 0xff;
			if( ! count )
			{	// have to insert a word containing the tag byte
				ch |= *inptr++;
				*outptr++ = (u16)ch;
				length--;
			}
			else
			{
				offset = *inptr++;
				copyptr = outptr - offset;
				length -= count;
				while( count-- )
				{
					*outptr++ = *copyptr++;
				}
			}
		}
		else if( chhigh == FARTAG )
		{
			count = ch & 0xff;
			if( ! count )
			{				// have to insert a word containing the tag byte
				ch |= *inptr++;
				*outptr++ = ch;
				length--;
			}
			else
			{
				offset = *(u16 *)inptr;
				inptr += 2;
				copyptr = dest + offset;
				length -= count;
				while( count-- )
				{
					*outptr++ = *copyptr++;
				}
			}
		}
		else
		{
			*outptr++ = ch;
			length--;
		}
	}
}

static void readTiles(tree::Stream& s, u16 rle, u16* tiles, u32 length, u32 offset)
{
	char* data = new char[length];
	s.seek(tree::Stream::BEGIN, offset);
	s.read(data, length);

	u16 expanded = *((u16*)data);
	u16* buffer = new u16[expanded >> 1];
	Lvl_CarmackExpand((u16*)data + 1, buffer, expanded);
	Lvl_RLEWexpand(buffer+1, tiles, 64*64*2, rle);

	delete[] data;
	delete[] buffer;
}

#define MAPHEADER_SIZE	49
#define MAP_SIGNATURE	0x21444921

tree::Stream& operator>> (tree::Stream& s, WolfLevel& v)
{
	// s must be valid. dont handle error now.
	u32 signature;
	s >> signature;
	if (signature != MAP_SIGNATURE)
	{
		throw std::exception("signagure error.");
	}

	u16 rle, w, h;
	u32 ceiling, floor;
	u16 mapNameLength, musicNameLength;
	std::string mapName, musicName;
	s >> rle;
	s >> w >> h;
	s >> ceiling >> floor;

	u32 offset[ 3 ];
	u16 length[ 3 ];

	s.read(length, sizeof(length));
	s.read(offset, sizeof(offset));

	s >> mapNameLength >> musicNameLength;

	// TODO: what use?
	float fpartime;
	std::string spartime;
	
	s >> fpartime;
	{
		char buffer[5];
		s.read(buffer, 5);
		spartime.assign(buffer, buffer + 5);
	}

	{
		char* tmp = new char[std::max(mapNameLength, musicNameLength)];
		s.read(tmp, mapNameLength);
		mapName.assign(tmp, tmp + mapNameLength);
		s.read(tmp, musicNameLength);
		musicName.assign(tmp, tmp + musicNameLength);
	}

	{
		v.m_tileWalls = new u16[64 * 64];
		v.m_tileObjects = new u16[64 * 64];
		v.m_tileOthers = new u16[64 * 64];
		readTiles(s, rle, v.m_tileWalls, length[0], offset[0]);
		readTiles(s, rle, v.m_tileObjects, length[1], offset[1]);
		readTiles(s, rle, v.m_tileOthers, length[2], offset[2]);
	}

	v.m_mapName = mapName;
	v.m_musicName = musicName;

	v.m_floorR = (u8)((floor >> 16) & 0xff);
	v.m_floorG = (u8)((floor >> 8) & 0xff);
	v.m_floorB = (u8)(floor & 0xff);

	v.m_width = 64;
	v.m_height = 64;

	return s;
}

WolfLevel* WolfLevel::createLevelFromStream(tree::Stream& s)
{
	WolfLevel* v = new WolfLevel();
	try
	{
		s >> *v;
	}
	catch (std::exception e)
	{
		delete v;
		v = NULL;
		LERR_ << "WolfLevel::createLevelFromStream exception" << e.what();
	}
	return v;
}




