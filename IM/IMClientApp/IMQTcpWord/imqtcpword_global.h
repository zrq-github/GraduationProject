#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(IMQTCPWORD_LIB)
#  define IMQTCPWORD_EXPORT Q_DECL_EXPORT
# else
#  define IMQTCPWORD_EXPORT Q_DECL_IMPORT
# endif
#else
# define IMQTCPWORD_EXPORT
#endif
