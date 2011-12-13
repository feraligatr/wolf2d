#ifndef _PCH_H_
#define _PCH_H_

#include <vector>
#include <set>
#include <map>
#include <iostream>
#include <queue>
#include <stack>
#include <list>
#include <string>

#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

#define BOOST_LOG_DONOT_USE_WCHAR_T
#include <boost/logging/format_fwd.hpp>
#include <boost/logging/format/named_write.hpp>
#include <boost/logging/format.hpp>
#include <boost/logging/format/formatter/tags.hpp>
#include <boost/logging/logging.hpp>
#include "Logger.h"

#include "common.h"
#include "TypeDefine.h"

#endif /* _PCH_H_ */