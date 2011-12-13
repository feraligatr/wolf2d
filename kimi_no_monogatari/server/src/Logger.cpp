#include "pch/pch.h"

#include "Logger.h"

using namespace boost::logging;

BOOST_DEFINE_LOG(g_l, LoggerType)
BOOST_DEFINE_LOG_FILTER(g_l_filter, FilterType)

void init_global_logs() {
	// Add formatters and destinations
	// That is, how the message is to be formatted...
	g_l()->writer().add_formatter( formatter::idx() );
	g_l()->writer().add_formatter( formatter::time("$hh:$mm.$ss") );
	g_l()->writer().add_formatter( formatter::append_newline() );

	//        ... and where should it be written to
	g_l()->writer().add_destination( destination::cout() );
	g_l()->turn_cache_off();
}

