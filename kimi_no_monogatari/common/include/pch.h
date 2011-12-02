#ifndef _PCH_H_
#define _PCH_H_

#include "Status.h"

#include <assert.h>

// TODO classify the defines and functions and move into different files.

#ifdef _DEBUG
#define ASSERT(x) assert (x);
#else /* _DEBUG */
#define ASSERT(x) ;
#endif /* _DEBUG */

// define the types just for simplify the typeing. so 
// char, unsigned char in function signature is acceptable.
// any other idea?

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;

typedef signed long long s64;
typedef unsigned long long u64;

#endif /* _PCH_H_ */
