#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(IMQTCPSERVER_LIB)
#  define IMQTCPSERVER_EXPORT Q_DECL_EXPORT
# else
#  define IMQTCPSERVER_EXPORT Q_DECL_IMPORT
# endif
#else
# define IMQTCPSERVER_EXPORT
#endif
