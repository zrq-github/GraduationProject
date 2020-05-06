#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(IMQTMYSQL_LIB)
#  define IMQTMYSQL_EXPORT Q_DECL_EXPORT
# else
#  define IMQTMYSQL_EXPORT Q_DECL_IMPORT
# endif
#else
# define IMQTMYSQL_EXPORT
#endif
