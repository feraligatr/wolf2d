#ifndef _STATUS_H_
#define _STATUS_H_

typedef enum {
	GSTATUS_OK,
	GSTATUS_ERR,
} GSTATUS;

class GStatus
{
public:
	static inline bool isSuccess(GSTATUS status) 
	{
		return status == GSTATUS_OK;
	}

	static inline bool isError(GSTATUS status)
	{
		return status != GSTATUS_OK;
	}
};

#define RETURN_ERR_IF_NULL(x) \
	{ \
		if (!(x)) return GSTATUS_ERR; \
	}


#define RETURN_IF_ERROR(x) \
	{ \
		GSTATUS ret = (x); \
		if (GStatus::isError(ret)) return x; \
	}

#endif