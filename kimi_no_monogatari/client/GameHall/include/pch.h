#ifndef _PCH_H_
#define _PCH_H_

#include "Status.h"

#include <assert.h>

#ifdef _DEBUG
#define ASSERT(x) assert (x);
#else /* _DEBUG */
#define ASSERT(x) ;
#endif /* _DEBUG */

#endif /* _PCH_H_ */
