#ifndef _LOGGER_H_
#define _LOGGER_H_

// logger defines.

BOOST_LOG_FORMAT_MSG( optimize::cache_string_one_str<> ) 

typedef boost::logging::logger_format_write< > LoggerType;
typedef boost::logging::level::holder FilterType;

BOOST_DECLARE_LOG_FILTER(g_l_filter, FilterType)
BOOST_DECLARE_LOG(g_l, LoggerType)

#define LDBG_ BOOST_LOG_USE_LOG_IF_LEVEL(g_l(), g_l_filter(), debug ) << "[dbg] "
#define LERR_ BOOST_LOG_USE_LOG_IF_LEVEL(g_l(), g_l_filter(), error ) << "[ERR] "
#define LAPP_ BOOST_LOG_USE_LOG_IF_LEVEL(g_l(), g_l_filter(), info )

#define LDBG_L_(l) BOOST_LOG_USE_LOG_IF_LEVEL(l, g_l_filter(), debug ) << "[dbg] "
#define LERR_L_(l) BOOST_LOG_USE_LOG_IF_LEVEL(l, g_l_filter(), error ) << "[ERR] "
#define LAPP_L_(l) BOOST_LOG_USE_LOG_IF_LEVEL(l, g_l_filter(), info )

#define LDBG_L_F_(l, f) BOOST_LOG_USE_LOG_IF_LEVEL(l, f, debug ) << "[dbg] "
#define LERR_L_F_(l, f) BOOST_LOG_USE_LOG_IF_LEVEL(l, f, error ) << "[ERR] "
#define LAPP_L_F_(l, f) BOOST_LOG_USE_LOG_IF_LEVEL(l, f, info )

void init_global_logs();

#endif /* _LOGGER_H_ */
