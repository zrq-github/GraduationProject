#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(QTUITOOL_LIB)
#  define QTUITOOL_EXPORT Q_DECL_EXPORT
# else
#  define QTUITOOL_EXPORT Q_DECL_IMPORT
# endif
#else
# define QTUITOOL_EXPORT
#endif
