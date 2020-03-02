#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(QTCP_LIB)
#  define QTCP_EXPORT Q_DECL_EXPORT
# else
#  define QTCP_EXPORT Q_DECL_IMPORT
# endif
#else
# define QTCP_EXPORT
#endif
