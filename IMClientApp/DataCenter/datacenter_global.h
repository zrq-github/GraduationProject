#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(DATACENTER_LIB)
#  define DATACENTER_EXPORT Q_DECL_EXPORT
# else
#  define DATACENTER_EXPORT Q_DECL_IMPORT
# endif
#else
# define DATACENTER_EXPORT
#endif
