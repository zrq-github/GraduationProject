#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(CONFIGCENTER_LIB)
#  define CONFIGCENTER_EXPORT Q_DECL_EXPORT
# else
#  define CONFIGCENTER_EXPORT Q_DECL_IMPORT
# endif
#else
# define CONFIGCENTER_EXPORT
#endif
