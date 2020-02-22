#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(LOGONPANEL_LIB)
#  define LOGONPANEL_EXPORT Q_DECL_EXPORT
# else
#  define LOGONPANEL_EXPORT Q_DECL_IMPORT
# endif
#else
# define LOGONPANEL_EXPORT
#endif
