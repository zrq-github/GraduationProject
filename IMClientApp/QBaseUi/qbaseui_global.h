#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(QBASEUI_LIB)
#  define QBASEUI_EXPORT Q_DECL_EXPORT
# else
#  define QBASEUI_EXPORT Q_DECL_IMPORT
# endif
#else
# define QBASEUI_EXPORT
#endif
