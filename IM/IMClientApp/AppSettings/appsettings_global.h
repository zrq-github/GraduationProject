#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(APPSETTINGS_LIB)
#  define APPSETTINGS_EXPORT Q_DECL_EXPORT
# else
#  define APPSETTINGS_EXPORT Q_DECL_IMPORT
# endif
#else
# define APPSETTINGS_EXPORT
#endif
