#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(DEFTDATA_LIB)
#  define DEFTDATA_EXPORT Q_DECL_EXPORT
# else
#  define DEFTDATA_EXPORT Q_DECL_IMPORT
# endif
#else
# define DEFTDATA_EXPORT
#endif
