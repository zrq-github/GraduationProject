#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(IM_LIB)
#  define IM_EXPORT Q_DECL_EXPORT
# else
#  define IM_EXPORT Q_DECL_IMPORT
# endif
#else
# define IM_EXPORT
#endif
