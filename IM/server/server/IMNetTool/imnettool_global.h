#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(IMNETTOOL_LIB)
#  define IMNETTOOL_EXPORT Q_DECL_EXPORT
# else
#  define IMNETTOOL_EXPORT Q_DECL_IMPORT
# endif
#else
# define IMNETTOOL_EXPORT
#endif
